#ifndef __SCT_FSM_H__
#define __SCT_FSM_H__

/* Generated by fzmparser version 1.14 --- DO NOT EDIT! */

#include "sct_user.h"

extern void sct_fsm_init(void);

/* Output assignments (and their defaults if specified) */
#define SCT_OUTPUT_JUMP_SIGNAL (6)
#define SCT_OUTPUTPRELOAD_JUMP_SIGNAL (0)
#define SCT_OUTPUT_CTOUT0 (2)
#define SCT_OUTPUTPRELOAD_CTOUT0 (1)
#define SCT_OUTPUT_CTOUT1 (3)
#define SCT_OUTPUTPRELOAD_CTOUT1 (1)
#define SCT_OUTPUT_CTOUT2 (4)
#define SCT_OUTPUTPRELOAD_CTOUT2 (1)
#define SCT_OUTPUT_CTOUT3 (5)
#define SCT_OUTPUTPRELOAD_CTOUT3 (1)


/* Match register reload macro definitions */
#define reload_toggleTimeout(value) LPC_SCT->MATCHREL_L[0] = value;
#define reload_jumpTimeout(value) LPC_SCT->MATCHREL_H[0] = value;

#endif






