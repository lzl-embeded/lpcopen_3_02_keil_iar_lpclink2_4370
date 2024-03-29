;/***********************************************************************
; * @brief: LPC18xx/43xx M0 startup code
; *
; * @note
; * Copyright(C) NXP Semiconductors, 2012
; * All rights reserved.
; *
; * @par
; * Software that is described herein is for illustrative purposes only
; * which provides customers with programming information regarding the
; * LPC products.  This software is supplied "AS IS" without any warranties of
; * any kind, and NXP Semiconductors and its licensor disclaim any and
; * all warranties, express or implied, including all implied warranties of
; * merchantability, fitness for a particular purpose and non-infringement of
; * intellectual property rights.  NXP Semiconductors assumes no responsibility
; * or liability for the use of the software, conveys no license or rights under any
; * patent, copyright, mask work right, or any other intellectual property rights in
; * or to any products. NXP Semiconductors reserves the right to make changes
; * in the software without notification. NXP Semiconductors also makes no
; * representation or warranty that such application will be suitable for the
; * specified use without further testing or modification.
; *
; * @par
; * Permission to use, copy, modify, and distribute this software and its
; * documentation is hereby granted, under NXP Semiconductors' and its
; * licensor's relevant copyrights in the software, without fee, provided that it
; * is used in conjunction with NXP Semiconductors microcontrollers.  This
; * copyright, permission, and disclaimer notice must appear in all copies of
; * this code.
; */

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000800

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00006000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
				IMPORT  __M0Signature

Sign_Value		EQU		0x5A5A5A5A
M0_Image_Magic  EQU     0xAA55DEAD

__Vectors       DCD     __initial_sp              	; 0 Top of Stack
                DCD     Reset_Handler             	; 1 Reset Handler
                DCD     NMI_Handler               	; 2 NMI Handler
                DCD     HardFault_Handler         	; 3 Hard Fault Handler
                DCD     MemManage_Handler         	; 4 MPU Fault Handler
                DCD     BusFault_Handler          	; 5 Bus Fault Handler
                DCD     UsageFault_Handler        	; 6 Usage Fault Handler
                DCD     Sign_Value                	; 7 Reserved
                DCD     M0_Image_Magic           	; 8 Reserved
                DCD     __M0Signature           	; 9 Reserved
                DCD     UnHandled_Vector          	; 10 Reserved
                DCD     SVC_Handler               	; 11 SVCall Handler
                DCD     DebugMon_Handler          	; 12 Debug Monitor Handler
                DCD     UnHandled_Vector          	; 13 Reserved
                DCD     PendSV_Handler            	; 14 PendSV Handler
                DCD     SysTick_Handler           	; 15 SysTick Handler

                ; External Interrupts
				DCD		RTC_IRQHandler				; 16 RTC
				DCD		M4_IRQHandler			; 17 M0/M4 IRQ handler (LPC43XX ONLY)
				DCD		DMA_IRQHandler				; 18 General Purpose DMA
				DCD		UnHandled_Vector			; 19 Reserved
				DCD		FLASHEEPROM_IRQHandler		; 20 ORed flash bank A, flash bank B, EEPROM interrupts
				DCD		ETH_IRQHandler				; 21 Ethernet
				DCD		SDIO_IRQHandler				; 22 SD/MMC
				DCD		LCD_IRQHandler				; 23 LCD
				DCD		USB0_IRQHandler				; 24 USB0
				DCD		USB1_IRQHandler				; 25 USB1
				DCD		SCT_IRQHandler				; 26 State Configurable Timer
				DCD		RIT_IRQHandler				; 27 Ored Repetitive Interrupt Timer, WWDT
				DCD		TIMER0_IRQHandler			; 28 Timer0
				DCD		GINT1_IRQHandler			; 29 GINT1
				DCD		GPIO4_IRQHandler			; 30 GPIO4
				DCD		TIMER3_IRQHandler			; 31 Timer3
				DCD		MCPWM_IRQHandler			; 32 Motor Control PWM
				DCD		ADC0_IRQHandler				; 33 A/D Converter 0
				DCD		I2C0_IRQHandler				; 34 ORed I2C0, I2C1
				DCD		SGPIO_IRQHandler			; 35 SGPIO (LPC43XX ONLY)
				DCD		SPI_IRQHandler				; 36 ORed SPI, DAC (LPC43XX ONLY)
				DCD		ADC1_IRQHandler				; 37 A/D Converter 1
				DCD		SSP0_IRQHandler				; 38 ORed SSP0, SSP1
				DCD		EVRT_IRQHandler				; 39 Event Router
				DCD		UART0_IRQHandler			; 40 UART0
				DCD		UART1_IRQHandler			; 41 UART1
				DCD		UART2_IRQHandler			; 42 ORed UART2, C_CAN1
				DCD		UART3_IRQHandler			; 43 UART3
				DCD		I2S0_IRQHandler				; 44 ORed I2S0, I2S1, QEI 
				DCD		CAN0_IRQHandler				; 45 C_CAN0
				DCD		UnHandled_Vector			; 46 M0s
				DCD		UnHandled_Vector			; 47 M0s

;                IF      :LNOT::DEF:NO_CRP
;                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
;CRP_Key         DCD     0xFFFFFFFF
;                ENDIF

                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
				; System initialization is handled by M4
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP
UnHandled_Vector	PROC
                EXPORT  UnHandled_Vector          [WEAK]
                B       .
                ENDP

Default_Handler PROC

				EXPORT RTC_IRQHandler	    	[WEAK]
                EXPORT M4_IRQHandler	    [WEAK]
				EXPORT DMA_IRQHandler		    [WEAK]
                EXPORT FLASHEEPROM_IRQHandler	[WEAK]
				EXPORT ETH_IRQHandler	    	[WEAK]
				EXPORT SDIO_IRQHandler	    	[WEAK]
				EXPORT LCD_IRQHandler	    	[WEAK]
				EXPORT USB0_IRQHandler	    	[WEAK]
				EXPORT USB1_IRQHandler	    	[WEAK]
				EXPORT SCT_IRQHandler	    	[WEAK]
				EXPORT RIT_IRQHandler	    	[WEAK]
				EXPORT TIMER0_IRQHandler    	[WEAK]
				EXPORT GINT1_IRQHandler	        [WEAK]
				EXPORT GPIO4_IRQHandler     	[WEAK]
				EXPORT TIMER3_IRQHandler    	[WEAK]
				EXPORT MCPWM_IRQHandler	    	[WEAK]
				EXPORT ADC0_IRQHandler	    	[WEAK]
				EXPORT I2C0_IRQHandler	    	[WEAK]
				EXPORT SGPIO_IRQHandler     	[WEAK]
                EXPORT SPI_IRQHandler	    	[WEAK]
				EXPORT ADC1_IRQHandler		    [WEAK]
				EXPORT SSP0_IRQHandler	    	[WEAK]
				EXPORT EVRT_IRQHandler		    [WEAK]
				EXPORT UART0_IRQHandler	    	[WEAK]
				EXPORT UART1_IRQHandler	    	[WEAK]
				EXPORT UART2_IRQHandler	    	[WEAK]
				EXPORT UART3_IRQHandler	    	[WEAK]
				EXPORT I2S0_IRQHandler	    	[WEAK]
				EXPORT CAN0_IRQHandler	    	[WEAK]

RTC_IRQHandler
M4_IRQHandler
DMA_IRQHandler
FLASHEEPROM_IRQHandler
ETH_IRQHandler
SDIO_IRQHandler
LCD_IRQHandler
USB0_IRQHandler
USB1_IRQHandler
SCT_IRQHandler
RIT_IRQHandler
TIMER0_IRQHandler
GINT1_IRQHandler
GPIO4_IRQHandler
TIMER3_IRQHandler
MCPWM_IRQHandler
ADC0_IRQHandler
I2C0_IRQHandler
SGPIO_IRQHandler
SPI_IRQHandler
ADC1_IRQHandler
SSP0_IRQHandler
EVRT_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
I2S0_IRQHandler
CAN0_IRQHandler
                B       .

                ENDP

                ALIGN

; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF

				END
				






