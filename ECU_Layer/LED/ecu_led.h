/* 
 * File:   ecu_led.h
 * Author: Abdo Halem
 *
 * Created on August 28, 2023, 12:25 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section: Includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations*/


/* Section: Macro Function Declarations*/


/* Section: Data Type Declarations*/

typedef struct{
    pin_config_t led_config;
}led_t;

/* Section: Software Interfaces Declarations*/
Std_Return_Type led_initialize(const led_t *led);
Std_Return_Type led_turn_on(const led_t *led);
Std_Return_Type led_turn_off(const led_t *led);
Std_Return_Type led_toggle(const led_t *led);

#endif	/* ECU_LED_H */

