
/* Generated by fzmparser version 1.14 --- DO NOT EDIT! */

/* Uses following resources: */
/* [12 events, 5+0 states, 2 inputs, 4 outputs, 1 match regs, 0 capture regs] */

#include "chip.h"
#include "sct_fsm.h"


void sct_fsm_init (void)
{

/* MATCH/CAPTURE registers */
LPC_SCT->REGMODE_L = 0x0000;         /* L: 1x MATCH, 0x CAPTURE, 15 unused */
LPC_SCT->REGMODE_H = 0x0000;             /* H: 0x MATCH, 0x CAPTURE, 16 unused */
LPC_SCT->MATCH_L[0] = speed;
LPC_SCT->MATCHREL_L[0] = speed;

/* OUTPUT registers */
LPC_SCT->OUT[14].SET = 0x00000210;        /* LED1 */
LPC_SCT->OUT[14].CLR = 0x00000844;
LPC_SCT->OUT[10].SET = 0x00000024;        /* LED2 */
LPC_SCT->OUT[10].CLR = 0x00000818;
LPC_SCT->OUT[13].SET = 0x00000108;        /* LED3 */
LPC_SCT->OUT[13].CLR = 0x000008A0;
LPC_SCT->OUT[11].SET = 0x00000480;        /* LED4 */
LPC_SCT->OUT[11].CLR = 0x00000902;
  /* Unused outputs must not be affected by any event */
LPC_SCT->OUT[0].SET = 0;
LPC_SCT->OUT[0].CLR = 0;
LPC_SCT->OUT[1].SET = 0;
LPC_SCT->OUT[1].CLR = 0;
LPC_SCT->OUT[2].SET = 0;
LPC_SCT->OUT[2].CLR = 0;
LPC_SCT->OUT[3].SET = 0;
LPC_SCT->OUT[3].CLR = 0;
LPC_SCT->OUT[4].SET = 0;
LPC_SCT->OUT[4].CLR = 0;
LPC_SCT->OUT[5].SET = 0;
LPC_SCT->OUT[5].CLR = 0;
LPC_SCT->OUT[6].SET = 0;
LPC_SCT->OUT[6].CLR = 0;
LPC_SCT->OUT[7].SET = 0;
LPC_SCT->OUT[7].CLR = 0;
LPC_SCT->OUT[8].SET = 0;
LPC_SCT->OUT[8].CLR = 0;
LPC_SCT->OUT[9].SET = 0;
LPC_SCT->OUT[9].CLR = 0;
LPC_SCT->OUT[12].SET = 0;
LPC_SCT->OUT[12].CLR = 0;
LPC_SCT->OUT[15].SET = 0;
LPC_SCT->OUT[15].CLR = 0;
LPC_SCT->OUTPUT = (LPC_SCT->OUTPUT & ~0x00006C00) | 0x00000000;

/* Conflict resolution register */

/* EVENT registers */
LPC_SCT->EVENT[1].CTRL = 0x00007100;     /* L: --> state L_ENTRY */
LPC_SCT->EVENT[1].STATE = 0x00000008;
LPC_SCT->EVENT[11].CTRL = 0x00006CC0;     /* L: --> state L_ENTRY */
LPC_SCT->EVENT[11].STATE = 0xFFFFFFFF;
LPC_SCT->EVENT[2].CTRL = 0x00017100;     /* L: --> state LED2on */
LPC_SCT->EVENT[2].STATE = 0x00000002;
LPC_SCT->EVENT[3].CTRL = 0x00027100;     /* L: --> state LED3on */
LPC_SCT->EVENT[3].STATE = 0x00000004;
LPC_SCT->EVENT[0].CTRL = 0x00001000;     /* L: */
LPC_SCT->EVENT[0].STATE = 0xFFFFFFFF;
LPC_SCT->EVENT[4].CTRL = 0x0000FD00;     /* L: --> state LED1on */
LPC_SCT->EVENT[4].STATE = 0x00000004;
LPC_SCT->EVENT[5].CTRL = 0x00017D00;     /* L: --> state LED2on */
LPC_SCT->EVENT[5].STATE = 0x00000010;
LPC_SCT->EVENT[6].CTRL = 0x00007D00;     /* L: --> state L_ENTRY */
LPC_SCT->EVENT[6].STATE = 0x00000002;
LPC_SCT->EVENT[7].CTRL = 0x0001F100;     /* L: --> state LED4on */
LPC_SCT->EVENT[7].STATE = 0x00000010;
LPC_SCT->EVENT[8].CTRL = 0x00027D00;     /* L: --> state LED3on */
LPC_SCT->EVENT[8].STATE = 0x00000008;
LPC_SCT->EVENT[9].CTRL = 0x0000F100;     /* L: --> state LED1on */
LPC_SCT->EVENT[9].STATE = 0x00000001;
LPC_SCT->EVENT[10].CTRL = 0x0001FD00;     /* L: --> state LED4on */
LPC_SCT->EVENT[10].STATE = 0x00000001;
  /* Unused events must not have any effect */
LPC_SCT->EVENT[12].STATE = 0;
LPC_SCT->EVENT[13].STATE = 0;
LPC_SCT->EVENT[14].STATE = 0;
LPC_SCT->EVENT[15].STATE = 0;

/* STATE registers */
LPC_SCT->STATE_L = 0;
LPC_SCT->STATE_H = 0; /* implicit value */

/* state names assignment: */
  /* State L 0: L_ENTRY */
  /* State L 1: LED1on */
  /* State L 2: LED2on */
  /* State L 3: LED4on */
  /* State L 4: LED3on */

/* CORE registers */
LPC_SCT->START_L = 0x0000;
LPC_SCT->STOP_L =  0x0000;
LPC_SCT->HALT_L =  0x0000;
LPC_SCT->LIMIT_L = 0x0001;
LPC_SCT->START_H = 0x0000;
LPC_SCT->STOP_H =  0x0000;
LPC_SCT->HALT_H =  0x0000;
LPC_SCT->LIMIT_H = 0x0000;
LPC_SCT->EVEN =    0x00000000;
LPC_SCT->DMA0REQUEST = 0x00000000;
LPC_SCT->DMA1REQUEST = 0x00000000;

}






