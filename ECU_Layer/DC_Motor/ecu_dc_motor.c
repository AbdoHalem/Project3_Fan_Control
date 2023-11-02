/* 
 * File:   ecu_dc_motor.c
 * Author: Abdo Halem
 *
 * Created on August 25, 2023, 11:46 PM
 */
#include "ecu_dc_motor.h"

/**
 * @ref Initializing the motor by initializing its 2 pins direction and logic
 * @param motor : Pointer to the motor of type (dc_motor_t)
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type dc_motor_initialize(const dc_motor_t *motor){
    Std_Return_Type ret = E_OK;
    if(NULL == motor){
        ret = E_NOT_OK;
    }
    else{
        /* Initialize the motor_pins to be output */
        ret = gpio_pin_initialize(&(motor->pin1));
        ret = gpio_pin_initialize(&(motor->pin2));
    }
    return ret;
}

/**
 * @ref Turning the the motor right by write HIGH on pin1 and LOW on pin2
 * @param motor : Pointer to the motor of type (dc_motor_t)
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type dc_motor_turn_right(const dc_motor_t *motor){
    Std_Return_Type ret = E_OK;
    if(NULL == motor){
        ret = E_NOT_OK;
    }
    else{
        /* Initialize the motor_pins to be output */
        ret = gpio_pin_write_logic(&(motor->pin1), GPIO_HIGH);
        ret = gpio_pin_write_logic(&(motor->pin2), GPIO_LOW);
    }
    return ret;
}

/**
 * @ref Turning the the motor right by write HIGH on pin2 and LOW on pin1
 * @param motor : Pointer to the motor of type (dc_motor_t)
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type dc_motor_turn_left(const dc_motor_t *motor){
    Std_Return_Type ret = E_OK;
    if(NULL == motor){
        ret = E_NOT_OK;
    }
    else{
        /* Initialize the motor_pins to be output */
        ret = gpio_pin_write_logic(&(motor->pin2), GPIO_HIGH);
        ret = gpio_pin_write_logic(&(motor->pin1), GPIO_LOW);
    }
    return ret;
}

/**
 * @ref Turning the the motor right by write LOW on pin1 and on pin2
 * @param motor : Pointer to the motor of type (dc_motor_t)
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type dc_motor_stop(const dc_motor_t *motor){
    Std_Return_Type ret = E_OK;
    if(NULL == motor){
        ret = E_NOT_OK;
    }
    else{
        /* Initialize the motor_pins to be output */
        ret = gpio_pin_write_logic(&(motor->pin1), GPIO_LOW);
        ret = gpio_pin_write_logic(&(motor->pin2), GPIO_LOW);
    }
    return ret;
}
