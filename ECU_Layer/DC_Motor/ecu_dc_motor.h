/* 
 * File:   ecu_dc_motor.h
 * Author: Abdo Halem
 *
 * Created on August 25, 2023, 11:46 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Section: Includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations*/


/* Section: Macro Function Declarations*/


/* Section: Data Type Declarations*/

typedef struct{
    pin_config_t pin1;
    pin_config_t pin2;
}dc_motor_t;

/* Section: Software Interfaces Declarations*/
Std_Return_Type dc_motor_initialize(const dc_motor_t *motor);
Std_Return_Type dc_motor_turn_right(const dc_motor_t *motor);
Std_Return_Type dc_motor_turn_left(const dc_motor_t *motor);
Std_Return_Type dc_motor_stop(const dc_motor_t *motor);

#endif	/* ECU_DC_MOTOR_H */

