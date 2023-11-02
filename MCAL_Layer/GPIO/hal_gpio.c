/* 
 * File:   hal_gpio.c
 * Author: Abdo Halem
 *
 * Created on September 10, 2023, 6:03 PM
 */

#include "hal_gpio.h"

volatile uint8 *TRIS_Registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *LAT_Registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8 *PORT_Registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/* ============== PIN Configurations ================*/
/**
 * @ref Initializing the pin by initializing its direction and logic
 * @param _pin_config : Pointer to the pin confguration of type pin_config_t
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_pin_initialize(const pin_config_t *_pin_config){
    Std_Return_Type ret = E_OK;
    if(NULL == _pin_config){
        ret = E_NOT_OK;
    }
    else{
        ret &= gpio_pin_direction_initialize(_pin_config);
        ret &= gpio_pin_write_logic(_pin_config ,_pin_config->logic);
    }
    return ret;
}

/**
 * @ref Initialize the direction of the pin to be INPUT or OUTPUT
 * @param _pin_config : Pointer to the pin confguration of type pin_config_t
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_pin_direction_initialize(const pin_config_t *_pin_config){
    Std_Return_Type ret = E_OK;
    if(NULL == _pin_config){
        ret = E_NOT_OK;
    }
    else{
        switch(_pin_config->direction){
            case GPIO_DIRECTION_OUTPUT :
                CLEAR_BIT(*TRIS_Registers[_pin_config->port], _pin_config->pin); break;
            case GPIO_DIRECTION_INPUT :
                SET_BIT(*TRIS_Registers[_pin_config->port], _pin_config->pin); break;
            default :
                ret = E_NOT_OK; break;
        } 
    }
    return ret;
}

/**
 * @ref Read the direction of the pin
 * @param _pin_config : Pointer to the pin confguration of type pin_config_t
 * @param direc_status : Pointer to the location that the direction_status will be returned to it
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direc_status){
    Std_Return_Type ret = E_OK;
    if(NULL == _pin_config){
        ret = E_NOT_OK;
    }
    else{
        *direc_status = READ_BIT(*TRIS_Registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}

/**
 * @ref Write a HIGH or LOW logic on the selected pin
 * @param _pin_config : Pointer to the pin confguration of type pin_config_t
 * @param logic : The logic that will be written
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic){
    Std_Return_Type ret = E_OK;
    if(NULL == _pin_config){
        ret = E_NOT_OK;
    }
    else{
        switch(logic){
            case GPIO_LOW :
                CLEAR_BIT(*LAT_Registers[_pin_config->port], _pin_config->pin); break;
            case GPIO_HIGH :
                SET_BIT(*LAT_Registers[_pin_config->port], _pin_config->pin); break;
            default :
                ret = E_NOT_OK; break;
        }
    }
    return ret;
}

/**
 * @ref Read the logic written on the pin
 * @param _pin_config : Pointer to the pin confguration of type pin_config_t
 * @param logic : Pointer to the location that the logic value will be stored in it
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic){
    Std_Return_Type ret = E_OK;
    if(NULL == _pin_config){
        ret = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*PORT_Registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}

/**
 * @ref  Toggle the logic on the selected pin
 * @param _pin_config : Pointer to the pin confguration of type pin_config_t
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_pin_toggle_logic(const pin_config_t *_pin_config){
    Std_Return_Type ret = E_OK;
    if(NULL == _pin_config){
        ret = E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*LAT_Registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}

/* ============== PORT Configurations ================*/
/**
 * @ref : Initializing the port by initializing its direction and logic
 * @param port : The index of the port (port_index_t)
 * @param direction : The direction of the port
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_port_initialize(port_index_t port, uint8 direction, uint8 logic){
    Std_Return_Type ret = E_OK;
    ret &= gpio_port_direction_initialize(port, direction);
    ret &= gpio_port_write_logic(port, logic);
    return ret;
}

/**
 * @ref Initialize the direction of whole PORT
 * @param port : The index of the port of type (port_index_t)
 * @param direction The direction of the port
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_port_direction_initialize(port_index_t port, uint8 direction){
    Std_Return_Type ret = E_OK;
    if((port >= PORTS_MAX_NUMBER) || (direction > 0xFF)){
        ret = E_NOT_OK;
    }
    else{
        *TRIS_Registers[port] = (uint8)direction;
    }
    return ret;    
}

/**
 * Return the direction of the port
 * @param port : The index of the port of type (port_index_t)
 * @param direc_status : Pointer to the location at which the direction will be stored 
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_port_get_direction_status(port_index_t port, uint8 *direc_status){
    Std_Return_Type ret = E_OK;
    if(NULL == direc_status){
        ret = E_NOT_OK;
    }
    else{
        *direc_status = *TRIS_Registers[port];
    }
    return ret;
}

/**
 * @ref Write a logic on the selected port
 * @param port : The index of the port of type (port_index_t)
 * @param logic : the value of the locic
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_port_write_logic(port_index_t port, uint8 logic){
    Std_Return_Type ret = E_OK;
    if((port >= PORTS_MAX_NUMBER) || (logic > 255)){
        ret = E_NOT_OK;
    }
    else{
        *LAT_Registers[port] = logic;
    }
    return ret;
}

/**
 * Read the logic on the whole port
 * @param port : The index of the port of type (port_index_t)
 * @param logic : Pointer to the location at which the logic will be stored
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_port_read_logic(port_index_t port, uint8 *logic){
    Std_Return_Type ret = E_OK;
    if(NULL == logic){
        ret = E_NOT_OK;
    }
    else{
        *logic = *PORT_Registers[port];
    }
    return ret;
}

/**
 * Toggle the logic on the whole port
 * @param port : The index of the port of type (port_index_t)
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type gpio_port_toggle_logic(port_index_t port){
    Std_Return_Type ret = E_OK;
    *LAT_Registers[port] ^= 0xFF; 
    return ret;
}
