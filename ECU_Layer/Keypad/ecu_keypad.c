/* 
 * File:   ecu_keypad.c
 * Author: Abdo Halem
 *
 * Created on August 31, 2023, 1:06 PM
 */

#include "ecu_keypad.h"

static const uint8 keypad_elements[KEYPAD_ROWS][KEYPAD_COLUMNS] = {'7', '8', '9', '/',
                                                                   '4', '5', '6', '*',
                                                                   '1', '2', '3', '-',
                                                                   'c', '0', '=', '+'};

Std_Return_Type keypad_initialize(const keypad_t *keypad){
    Std_Return_Type ret = E_OK;
    uint8 pins_counter = 0;
    if(NULL == keypad){
        ret = E_NOT_OK;
    }
    else{
        for(pins_counter = 0; pins_counter < KEYPAD_ROWS; pins_counter++){
            ret = gpio_pin_initialize(&(keypad->rows[pins_counter]));
        }
        for(pins_counter = 0; pins_counter < KEYPAD_COLUMNS; pins_counter++){
            ret = gpio_pin_direction_initialize(&(keypad->columns[pins_counter]));
        }
    }
    return ret;
}

Std_Return_Type keypad_get_button(const keypad_t *keypad, uint8 *value){
    Std_Return_Type ret = E_OK;
    Std_Return_Type status = KEY_NOT_PRESSED;
    uint8 pins_counter = 0, rows_counter = 0, columns_counter = 0;
    logic_t logic = 0;
    if((NULL == keypad) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        for(pins_counter = 0; pins_counter < KEYPAD_ROWS; pins_counter++){
            ret = gpio_pin_write_logic(&(keypad->rows[pins_counter]), GPIO_HIGH);
            
            ret = gpio_pin_read_logic(&(keypad->columns[0]), &logic);
            if(GPIO_HIGH == logic){
                *value = keypad_elements[pins_counter][0];
                status = KEY_PRESSED;
                break;
            }
            
            ret = gpio_pin_read_logic(&(keypad->columns[1]), &logic);
            if(GPIO_HIGH == logic){
                *value = keypad_elements[pins_counter][1];
                status = KEY_PRESSED;
                break;
            }
            
            ret = gpio_pin_read_logic(&(keypad->columns[2]), &logic);
            if(GPIO_HIGH == logic){
                *value = keypad_elements[pins_counter][2];
                status = KEY_PRESSED;
                break;
            }
            
            ret = gpio_pin_read_logic(&(keypad->columns[3]), &logic);
            if(GPIO_HIGH == logic){
                *value = keypad_elements[pins_counter][3];
                status = KEY_PRESSED;
                break;
            }
            ret = gpio_pin_write_logic(&(keypad->rows[pins_counter]), GPIO_LOW);
        }
        ret = gpio_pin_write_logic(&(keypad->rows[pins_counter]), GPIO_LOW);
    }
    if(KEY_PRESSED == status){
        __delay_ms(100);
    }
    //__delay_ms(100);
    return ret;
}
