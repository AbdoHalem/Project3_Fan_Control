/* 
 * File:   initializations.h
 * Author: Abdo Halem
 *
 * Created on September 1, 2023, 3:11 PM
 */

#ifndef INITIALIZATIONS_H
#define	INITIALIZATIONS_H

/* Section: Includes*/
#include "ECU_Layer/LED/ecu_led.h"
#include "MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "MCAL_Layer/TIMER2/Timer2.h"
#include "MCAL_Layer/ADC/hal_ADC.h"
#include "MCAL_Layer/CCP/ccp1.h"
#include "MCAL_Layer/EEPROM/EEPROM.h"
#include "ECU_Layer/DC_Motor/ecu_dc_motor.h"
#include "ECU_Layer/Keypad/ecu_keypad.h"
#include "ECU_Layer/LCD/ecu_lcd.h"

/* Section: Macro Declarations*/


/* Section: Macro Function Declarations*/


/* Section: Data Type Declarations*/
extern lcd_4bits_t lcd;
extern keypad_t keypad;
extern dc_motor_t motor1;
extern led_t led1;
extern led_t led2;
extern led_t led3;
extern adc_config_t adc_1;
extern timer2_t timer2_obj;
extern ccp1_t ccp1_obj;

/* Section: Software Interfaces Declarations*/
Std_Return_Type ECU_Initialize();

#endif	/* INITIALIZATIONS_H */

