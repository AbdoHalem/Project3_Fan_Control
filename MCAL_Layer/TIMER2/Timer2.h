/* 
 * File:   Timer2.h
 * Author: Abdo Halem
 *
 * Created on October 27, 2023, 6:01 PM
 */

#ifndef TIMER2_H
#define	TIMER2_H

/* Section: Includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* Section: Macro Declarations*/
#define TIMER2_POSTSCALER_DIV_BY_1  0
#define TIMER2_POSTSCALER_DIV_BY_2  1
#define TIMER2_POSTSCALER_DIV_BY_3  2
#define TIMER2_POSTSCALER_DIV_BY_4  3
#define TIMER2_POSTSCALER_DIV_BY_5  4
#define TIMER2_POSTSCALER_DIV_BY_6  5
#define TIMER2_POSTSCALER_DIV_BY_7  6
#define TIMER2_POSTSCALER_DIV_BY_8  7
#define TIMER2_POSTSCALER_DIV_BY_9  8
#define TIMER2_POSTSCALER_DIV_BY_10 9
#define TIMER2_POSTSCALER_DIV_BY_11 10
#define TIMER2_POSTSCALER_DIV_BY_12 11
#define TIMER2_POSTSCALER_DIV_BY_13 12
#define TIMER2_POSTSCALER_DIV_BY_14 13
#define TIMER2_POSTSCALER_DIV_BY_15 14
#define TIMER2_POSTSCALER_DIV_BY_16 15

#define TIMER2_PRESCALER_DIV_BY_1  0
#define TIMER2_PRESCALER_DIV_BY_4  1
#define TIMER2_PRESCALER_DIV_BY_16 2

/* Section: Macro Function Declarations */
#define TIMER2_ENABLE() (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE() (T2CONbits.TMR2ON = 0)

#define TIMER2_SET_POSTSCALER(postscaler_value) (T2CONbits.TOUTPS = postscaler_value)
#define TIMER2_SET_PRESCALER(prescaler_value)   (T2CONbits.TOUTPS = prescaler_value)

/* Section: Data Type Declarations*/
typedef struct{
#if TIMER2_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
    void (*Timer2_Interrupt_Handler)(void);
#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t priority;
#endif
#endif
    uint8 timer2_preload_value;
    uint8 postscaler_value : 4;
    uint8 prescaler_value : 2;
    uint8  : 2;
}timer2_t;

/* Section: Software Interfaces Declarations*/
Std_Return_Type Timer2_Init(const timer2_t *timer2);
Std_Return_Type Timer2_DeInit(const timer2_t *timer2);
Std_Return_Type Timer2_Write_Value(const timer2_t *timer2, uint8 value);
Std_Return_Type Timer2_Read_Value(const timer2_t *timer2, uint8 *value);

#endif	/* TIMER2_H */

