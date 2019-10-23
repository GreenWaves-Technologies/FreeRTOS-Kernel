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

#include "FreeRTOS.h"
#include "system_gap8.h"

/* Scheduler utilities. */

/* Critical section management. */
void vPortEnter_Critical( void );
void vPortExit_Critical( void );
uint32_t uPortSet_Interrupt_Mask_From_ISR( void );
void vPortClear_Interrupt_Mask_From_ISR( uint32_t irqSet );

/* Variables. */
volatile uint32_t ulCriticalNesting = 0ul;

/*-----------------------------------------------------------*/
/* Setup timer to enable Systick interruptions. */
void vPortSetupTimerInterrupt( void )
{
    /* Compared value. */
    /* SysTick->CMP_LO = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1ul; */
    system_setup_systick((uint32_t) configTICK_RATE_HZ);
}
/*-----------------------------------------------------------*/

void vPortEnter_Critical( void )
{
    portDISABLE_INTERRUPTS();
    /* Increment nesting value everytime a critical section is entered. */
    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

void vPortExit_Critical( void )
{
    /* Decrement nesting value everytime a critical section is exit. */
    if( ulCriticalNesting > 0 )
    {
	ulCriticalNesting--;
	if( ulCriticalNesting == 0 )
	{
	    /* If no more in any critical sections, enable interruptions. */
	    portENABLE_INTERRUPTS();
	}
    }
}
/*-----------------------------------------------------------*/

uint32_t uPortSet_Interrupt_Mask_From_ISR( void )
{
    /* No nested IRQ, so IRQ are either enabled or disabled.  */
    return __disable_irq();
}
/*-----------------------------------------------------------*/

void vPortClear_Interrupt_Mask_From_ISR( uint32_t irqSet )
{
    __restore_irq(irqSet);
    /* No nested IRQ, so IRQ are either enabled or disabled.  */
}
/*-----------------------------------------------------------*/
