/* 
 * File:   ecu_led.c
 * Author: Abdo Halem
 *
 * Created on August 28, 2023, 12:25 AM
 */

#include "ecu_led.h"
/**
 * @ref Initialize the led pin to be output and turned off
 * @param led : Pointer to led configuration (led_t)
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type led_initialize(const led_t *led){
    Std_Return_Type ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        /* Initialize the led_pin to be output */
        ret = gpio_pin_initialize(&(led->led_config));
    }
    return ret;
}

/**
 * @ref Turn ON the led
 * @param led : Pointer to led configuration (led_t)
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type led_turn_on(const led_t *led){
    Std_Return_Type ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(led->led_config), GPIO_HIGH);
    }
    return ret;
}

/**
 * @ref Turn OFF the led
 * @param led : Pointer to led configuration (led_t)
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type led_turn_off(const led_t *led){
    Std_Return_Type ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(led->led_config), GPIO_LOW);
    }
    return ret;
}

/**
 * @ref Toggle the status of the led
 * @param led : Pointer to led configuration (led_t)
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type led_toggle(const led_t *led){
    Std_Return_Type ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_toggle_logic(&(led->led_config));
    }
    return ret;
}
