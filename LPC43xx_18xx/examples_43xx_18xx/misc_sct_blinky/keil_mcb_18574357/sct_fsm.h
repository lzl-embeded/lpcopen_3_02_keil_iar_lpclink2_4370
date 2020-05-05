#ifndef __SCT_FSM_H__
#define __SCT_FSM_H__

/* Generated by fzmparser version 1.14 --- DO NOT EDIT! */

#include "sct_user.h"

extern void sct_fsm_init(void);

/* Input assignments */
#define SCT_INPUT_DOWN (4)
#define SCT_INPUT_RESET (3)

/* Output assignments (and their defaults if specified) */
#define SCT_OUTPUT_LED1 (14)
#define SCT_OUTPUTPRELOAD_LED1 (0)
#define SCT_OUTPUT_LED2 (10)
#define SCT_OUTPUTPRELOAD_LED2 (0)
#define SCT_OUTPUT_LED3 (13)
#define SCT_OUTPUTPRELOAD_LED3 (0)
#define SCT_OUTPUT_LED4 (11)
#define SCT_OUTPUTPRELOAD_LED4 (0)


/* Match register reload macro definitions */
#define reload_maxcount(value) LPC_SCT->MATCHREL_L[0] = value;

#endif






