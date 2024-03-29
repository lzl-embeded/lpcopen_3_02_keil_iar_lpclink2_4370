/*
 * @brief SDMMC Chan FATFS simple abstraction layer (for RAM disk)
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
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

#include <string.h>
#include "diskio.h"
#include "fs_mem.h"
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Disk Status */
static volatile DSTATUS Stat = STA_NOINIT;
static uint8_t *buff_ptr;
static uint32_t buff_sz;

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize Disk Drive */
DSTATUS disk_initialize(BYTE drv)
{

	if (drv) {
		return STA_NOINIT;				/* Supports only single drive */
	}

	if (Stat != STA_NOINIT) {
		return Stat;					/* Mem variables already set */

	}

	/* Reset */
	Stat = STA_NOINIT;

	FATFS_GetBufferInfo(&buff_ptr, &buff_sz);

	/* Check if we got a valid, atleast 4K sized buffer */
	if (!buff_ptr || buff_sz < 4096) {
		return Stat;
	}

	Stat &= ~STA_NOINIT;
	return Stat;

}


/* Read Sector(s) */
DRESULT disk_read(BYTE drv, BYTE *buff, DWORD sector, BYTE count)
{
	if (drv || !count) {
		return RES_PARERR;
	}
	if (Stat & STA_NOINIT) {
		return RES_NOTRDY;
	}

	memcpy(buff, buff_ptr + (sector * SECTOR_SZ), SECTOR_SZ * count);

	return RES_OK;
}

/* Get Disk Status */
DSTATUS disk_status(BYTE drv)
{
	if (drv) {
		return STA_NOINIT;	/* Supports only single drive */

	}
	return Stat;
}

/* Write Sector(s) */
DRESULT disk_write(BYTE drv, const BYTE *buff, DWORD sector, BYTE count)
{

	if (drv || !count) {
		return RES_PARERR;
	}
	if (Stat & STA_NOINIT) {
		return RES_NOTRDY;
	}

	memcpy(buff_ptr + (sector * SECTOR_SZ), buff, SECTOR_SZ * count);
	return RES_OK;
}

/* Disk Drive miscellaneous Functions */
DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void *buff)
{
	DRESULT res;

	if (drv) {
		return RES_PARERR;
	}
	if (Stat & STA_NOINIT) {
		return RES_NOTRDY;
	}

	res = RES_ERROR;

	switch (ctrl) {
	case CTRL_SYNC:	/* Make sure that no pending write process */
		res = RES_OK;
		break;

	case GET_SECTOR_COUNT:	/* Get number of sectors on the disk (DWORD) */
		*(DWORD *) buff = buff_sz / SECTOR_SZ;
		res = RES_OK;
		break;

	case GET_SECTOR_SIZE:	/* Get R/W sector size (WORD) */
		*(WORD *) buff = SECTOR_SZ;	// 512;
		res = RES_OK;
		break;

	case GET_BLOCK_SIZE:/* Get erase block size in unit of sector (DWORD) */
		*(DWORD *) buff = SECTOR_SZ;	// FIXED:
		res = RES_OK;
		break;

	default:
		res = RES_PARERR;
		break;
	}

	return res;
}






