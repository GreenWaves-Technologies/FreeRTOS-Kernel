/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and t

 o permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef __FREERTOS_RISC_V_MACRO_EXTENSIONS_H__
#define __FREERTOS_RISC_V_MACRO_EXTENSIONS_H__

/*-----------------------------------------------------------*/

/* Scheduler utilities. */
extern void vTaskSwitchContext( void );
#define portYIELD() __asm volatile( "ecall" );
#define portEND_SWITCHING_ISR( xSwitchRequired ) if( xSwitchRequired ) vTaskSwitchContext()
#define portYIELD_FROM_ISR( x ) portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
extern void vTaskEnterCritical( void );
extern void vTaskExitCritical( void );

#define portSET_INTERRUPT_MASK_FROM_ISR() 0
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedStatusValue )  ( void ) uxSavedStatusValue
#define portDISABLE_INTERRUPTS()	                         __asm volatile( "csrc mstatus, 8" )
#define portENABLE_INTERRUPTS()		                         __asm volatile( "csrs mstatus, 8" )
#define portENTER_CRITICAL()                                     vTaskEnterCritical()
#define portEXIT_CRITICAL()                                      vTaskExitCritical()
/*-----------------------------------------------------------*/

#endif  /* __FREERTOS_RISC_V_MACRO_EXTENSIONS_H__ */
