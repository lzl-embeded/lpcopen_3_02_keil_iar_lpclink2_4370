/*
 * @brief	lwIP Filesystem implementation module
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "board.h"
#include "ff.h"
#include "fs_mem.h"
#include "lwip_fs.h"
#include "app_dualcore_cfg.h"
#include "ipc_example.h"

#include "httpd_structs.h"

/**
 * @ingroup EXAMPLES_DUALCORE_LWIP_FS
 * @{
 */

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Default html file */
const static char http_index_html[] =
	"<html><head><title>Congrats!</title></head>"
	"<body><h1>Welcome to our lwIP HTTP server!</h1>"
	"<p>This is a small test page, served by httpd of "
	"lwip.</p></body></html>";

static FATFS *Fatfs;	/* File system object */

/* Internal File descriptor structure */
struct file_ds {
	uint8_t scratch[SECTOR_SZ];
	FIL fi;
	struct fs_file fs;
	int fi_valid;
};

/*****************************************************************************
 * Private functions
 ****************************************************************************/
/**
 * Generate the relevant HTTP headers for the given filename and write
 * them into the supplied buffer.
 */
static int
get_http_headers(const char *fName, char *buff)
{
	unsigned int iLoop;
	const char *pszExt = NULL;
	const char *hdrs[4];

	/* Ensure that we initialize the loop counter. */
	iLoop = 0;

	/* In all cases, the second header we send is the server identification
	   so set it here. */
	hdrs[1] = g_psHTTPHeaderStrings[HTTP_HDR_SERVER];

	/* Is this a normal file or the special case we use to send back the
	   default "404: Page not found" response? */
	if (( fName == NULL) || ( *fName == 0) ) {
		hdrs[0] = g_psHTTPHeaderStrings[HTTP_HDR_NOT_FOUND];
		hdrs[2] = g_psHTTPHeaderStrings[DEFAULT_404_HTML];
		goto end_fn;
	}
	/* We are dealing with a particular filename. Look for one other
	    special case.  We assume that any filename with "404" in it must be
	    indicative of a 404 server error whereas all other files require
	    the 200 OK header. */
	if (strstr(fName, "404")) {
		iLoop = HTTP_HDR_NOT_FOUND;
	}
	else if (strstr(fName, "400")) {
		iLoop = HTTP_HDR_BAD_REQUEST;
	}
	else if (strstr(fName, "501")) {
		iLoop = HTTP_HDR_NOT_IMPL;
	}
	else {
		iLoop = HTTP_HDR_OK;
	}
	hdrs[0] = g_psHTTPHeaderStrings[iLoop];

	/* Get a pointer to the file extension.  We find this by looking for the
	     last occurrence of "." in the filename passed. */
	pszExt = strrchr(fName, '.');

	/* Does the FileName passed have any file extension?  If not, we assume it
	     is a special-case URL used for control state notification and we do
	     not send any HTTP headers with the response. */
	if (pszExt == NULL) {
		return 0;
	}

	pszExt++;
	/* Now determine the content type and add the relevant header for that. */
	for (iLoop = 0; (iLoop < NUM_HTTP_HEADERS); iLoop++)
		/* Have we found a matching extension? */
		if (!strcmp(g_psHTTPHeaders[iLoop].extension, pszExt)) {
			hdrs[2] =
				g_psHTTPHeaderStrings[g_psHTTPHeaders[iLoop].headerIndex];
			break;
		}

	/* Did we find a matching extension? */
	if (iLoop == NUM_HTTP_HEADERS) {
		/* No - use the default, plain text file type. */
		hdrs[2] = g_psHTTPHeaderStrings[HTTP_HDR_DEFAULT_TYPE];
	}

end_fn:
	iLoop = strlen(hdrs[0]);
	strcpy(buff, hdrs[0]);
	strcat(buff, hdrs[1]);
	strcat(buff, hdrs[2]);
	return strlen(buff);
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Read http header information into a string */
int GetHTTP_Header(const char *fName, char *buff)
{
	return get_http_headers(fName, buff);
}

/* Opens the default index html file */
struct fs_file *fs_open_default(void) {
	int hlen;
	struct file_ds *fds;
	struct fs_file *fs;

	fds = malloc(sizeof(*fds));
	if (fds == NULL) {
		DEBUGSTR("Malloc Failure, Out of Memory!\r\n");
		return NULL;
	}
	memset(fds, 0, sizeof(*fds));
	fs = &fds->fs;
	fs->pextension = (void *) fds;	/* Store this for later use */
	hlen = get_http_headers("default.htm", (char *) fds->scratch);
	fs->data = (const char *) fds->scratch;
	memcpy((void *) &fs->data[hlen], (void *) http_index_html, sizeof(http_index_html) - 1);
	fs->len = hlen + sizeof(http_index_html) - 1;
	fs->index = fs->len;
	fs->http_header_included = 1;
	return fs;
}

/* File open function */
struct fs_file *fs_open(const char *name) {
	FRESULT res;
	int hlen;
	struct file_ds *fds;
	struct fs_file *fs;

	if (!ipcex_getGblVal(SHGBL_USBDISKADDR))
		return NULL;

	if (!Fatfs) {
		/* One time allocation not to be freed! */
		Fatfs = malloc(sizeof(*Fatfs));
		if (Fatfs == NULL) return NULL;
		f_mount(0, Fatfs); /* Never fails */
	}

	/* Allocate file descriptor */
	fds = malloc(sizeof(*fds));
	if (fds == NULL) {
		DEBUGSTR("Malloc Failure, Out of Memory!\r\n");
		return NULL;
	}

	res = f_open(&fds->fi, name, FA_READ);
	if (res) {
		LWIP_DEBUGF(HTTPD_DEBUG, ("DFS: OPEN: File %s does not exist\r\n", name));
		free(fds);
		return NULL;
	}

	fs = &fds->fs;
	fds->fi_valid = 1;
	fs->pextension = (void *) fds;	/* Store this for later use */
	hlen = get_http_headers(name, (char *) fds->scratch);
	fs->data = (const char *) fds->scratch;
	fs->index = hlen;
	fs->len = f_size(&fds->fi) + hlen;
	fs->http_header_included = 1;
	return fs;
}

/* File close function */
void fs_close(struct fs_file *file)
{
	struct file_ds *fds;

	if(file == NULL)
		return;

	fds = (struct file_ds *) file->pextension;
	if (fds->fi_valid)
		f_close(&fds->fi);
 	free(fds);
}

/* File read function */
int fs_read(struct fs_file *file, char *buffer, int count)
{
	uint32_t i = 0;
	struct file_ds *fds = (struct file_ds *) file->pextension;
	if (f_read(&fds->fi, (uint8_t *) buffer, count, &i))
		return 0; /* Error in reading file */
	file->index += i;
	return i;
}

/* Number of bytes left in the file */
int fs_bytes_left(struct fs_file *file)
{
	return file->len - file->index;
}

/* Fat file system information function */
void FATFS_GetBufferInfo(uint8_t **buffer, uint32_t *size)
{
	*buffer = (uint8_t *) ipcex_getGblVal(SHGBL_USBDISKADDR);
	*size = (uint32_t) RAMDISK_SIZE;
}

#ifdef LWIP_DEBUG
/* Assert print function */
void assert_printf(char *msg, int line, char *file)
{
	DEBUGOUT("ASSERT: %s at %s:%d\r\n", msg, file, line);
}

/* LWIP str err function */
const char *lwip_strerr(err_t eno)
{
	return "";
}

#endif






