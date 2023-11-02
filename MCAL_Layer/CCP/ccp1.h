/* 
 * File:   ccp1.h
 * Author: Abdo Halem
 *
 * Created on October 27, 2023, 8:56 PM
 */

#ifndef CCP1_H
#define	CCP1_H

/* Section: Includes*/
#include "ccp_config.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section: Macro Declarations*/
#define CCP_MODULE_DISABLED               ((uint8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE   ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE    ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE    ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE   ((uint8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW      ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH     ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH  ((uint8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT        ((uint8)0x0B)
#define CCP_PWM_MODE                      ((uint8)0x0C)

#define CCP1_TIMER2_POSTSCALER_DIV_BY_1  1
#define CCP1_TIMER2_POSTSCALER_DIV_BY_2  2
#define CCP1_TIMER2_POSTSCALER_DIV_BY_3  3
#define CCP1_TIMER2_POSTSCALER_DIV_BY_4  4
#define CCP1_TIMER2_POSTSCALER_DIV_BY_5  5
#define CCP1_TIMER2_POSTSCALER_DIV_BY_6  6
#define CCP1_TIMER2_POSTSCALER_DIV_BY_7  7
#define CCP1_TIMER2_POSTSCALER_DIV_BY_8  8
#define CCP1_TIMER2_POSTSCALER_DIV_BY_9  9
#define CCP1_TIMER2_POSTSCALER_DIV_BY_10 10
#define CCP1_TIMER2_POSTSCALER_DIV_BY_11 11
#define CCP1_TIMER2_POSTSCALER_DIV_BY_12 12
#define CCP1_TIMER2_POSTSCALER_DIV_BY_13 13
#define CCP1_TIMER2_POSTSCALER_DIV_BY_14 14
#define CCP1_TIMER2_POSTSCALER_DIV_BY_15 15
#define CCP1_TIMER2_POSTSCALER_DIV_BY_16 16

#define CCP1_TIMER2_PRESCALER_DIV_BY_1  1
#define CCP1_TIMER2_PRESCALER_DIV_BY_4  4
#define CCP1_TIMER2_PRESCALER_DIV_BY_16 16

/* Section: Macro Function Declarations*/
#define CCP1_SET_MODE(Mode)    (CCP1CONbits.CCP1M = Mode)

/* Section: Data Type Declarations*/
typedef enum{
    CCP1_CAPTURE_MODE_SELECTED = 0,
    CCP1_COMPARE_MODE_SELECTED,
    CCP1_PWM_MODE_SELECTED
}ccp1_mode_t;

typedef union{
    struct{
        uint8 ccpr1_low;
        uint8 ccpr1_high;
    };
    struct{
        uint16 ccpr1_16Bit;
    };
}CCP1_REG_t;

typedef struct{
    ccp1_mode_t ccp_mode;      /* CCP main mode */
    pin_config_t ccp_pin;      /* CCP Pin I/O configurations */
#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED)
    uint32 PWM_Frequency;      /* CCP PWM mode frequency */
    uint8 timer2_postscaler_value : 4;
    uint8 timer2_prescaler_value : 2;
#endif
#if CCP1_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
    void (* CCP1_InterruptHandler)(void);   /* Call back used for all CCP1 Modes */
#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t CCP_priority;   /* Configure the CCP1 mode interrupt */
#endif
#endif
}ccp1_t;

/* Section: Software Interfaces Declarations*/
Std_Return_Type CCP1_Init(const ccp1_t *ccp_obj);
Std_Return_Type CCP1_DeInit(const ccp1_t *ccp_obj);

#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED)
Std_Return_Type CCP1_PWM_Set_Duty(const uint8 duty_cycle);
Std_Return_Type CCP1_PWM_Start();
Std_Return_Type CCP1_PWM_Stop();
#endif

#endif	/* CCP1_H */

