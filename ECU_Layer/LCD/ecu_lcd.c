/* 
 * File:   ecu_lcd.c
 * Author: Abdo Halem
 *
 * Created on August 28, 2023, 10:52 PM
 */

#include "ecu_lcd.h"

static Std_Return_Type lcd_4bit_send_enable(const lcd_4bits_t *lcd);
static Std_Return_Type lcd_4bit_set_cursor(const lcd_4bits_t *lcd, uint8 row, uint8 column);

/**
 * @ref Initialize the lcd pins Rs, En and data pins
 * @param lcd : Pointer to the lcd configuration
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type lcd_4bit_initialize(const lcd_4bits_t *lcd){
    Std_Return_Type ret = E_OK;
    uint8 data_pins_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(lcd->Rs));
        ret = gpio_pin_initialize(&(lcd->En));
        for(data_pins_counter = 0; data_pins_counter < 4; data_pins_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_BUS_MODE_2LINES);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_BUS_MODE_2LINES);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_BUS_MODE_2LINES);
        /* ============================== My initializations ============================== */
        ret = lcd_4bit_send_command(lcd, LCD_CLEAR_DISPLAY);
        ret = lcd_4bit_send_command(lcd, LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd, LCD_4BIT_BUS_MODE_2LINES);
        ret = lcd_4bit_send_command(lcd, 0x80);
    }
    return ret;
}

/**
 * @ref Send command to the lcd by clearing the Rs pin and write the command byte on the data pins
 * @param lcd : Pointer to the lcd configuration
 * @param command : the command byte
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type lcd_4bit_send_command(const lcd_4bits_t *lcd, uint8 command){
    Std_Return_Type ret = E_OK;
    uint8 data_pins_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->Rs), GPIO_LOW);
        for(data_pins_counter = 0; data_pins_counter < 4; data_pins_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[data_pins_counter]), (command >> (data_pins_counter + 4)) & (uint8)0x01);
        }
        ret = lcd_4bit_send_enable(lcd);
        for(data_pins_counter = 0; data_pins_counter < 4; data_pins_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[data_pins_counter]), (command >> data_pins_counter) & (uint8)0x01);
        }
        ret = lcd_4bit_send_enable(lcd);
    }
    return ret;
}

/**
 * @ref Send data to the lcd by setting the Rs pin and write the data byte on the data pins
 * @param lcd : Pointer to the lcd configuration
 * @param command : the data byte
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve
 */
Std_Return_Type lcd_4bit_send_char_data(const lcd_4bits_t *lcd, uint8 data){
    Std_Return_Type ret = E_OK;
    uint8 data_pins_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->Rs), GPIO_HIGH);
        for(data_pins_counter = 0; data_pins_counter < 4; data_pins_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[data_pins_counter]), (data >> (data_pins_counter + 4)) & (uint8)0x01);
        }
        ret = lcd_4bit_send_enable(lcd);
        for(data_pins_counter = 0; data_pins_counter < 4; data_pins_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[data_pins_counter]), (data >> data_pins_counter) & (uint8)0x01);
        }
        ret = lcd_4bit_send_enable(lcd);
    }
    return ret;
}

/**
 * @ref Send data to specific location at the lcd by setting the Rs pin and write the data byte on the data pins
 * @param lcd : Pointer to the lcd configuration
 * @param row : the row index
 * @param column : the column index
 * @param data : the data byte
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve 
 */
Std_Return_Type lcd_4bit_send_char_data_pos(const lcd_4bits_t *lcd, uint8 row, uint8 column, uint8 data){
    Std_Return_Type ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret;
}

/**
 * @ref Send data to the lcd by setting the Rs pin and write the data byte on the data pins
 * @param lcd : Pointer to the lcd configuration
 * @param str : pointer to the string
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve 
 */
Std_Return_Type lcd_4bit_send_string_data(const lcd_4bits_t *lcd, uint8 *str){
    Std_Return_Type ret = E_OK;
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK;
    }
    else{
        while(*str){
            ret = lcd_4bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return ret;
}

/**
 * @ref Send a string to a specific location at the lcd by setting the Rs pin and write the data byte on the data pins
 * @param lcd : Pointer to the lcd configuration
 * @param row : the row index
 * @param column : the column index
 * @param str : pointer to the string
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve  
 */
Std_Return_Type lcd_4bit_send_string_data_pos(const lcd_4bits_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_Return_Type ret = E_OK;
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd, row, column);
        while(*str){
            ret = lcd_4bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return ret;
}

/**
 * @ref Send a user-defined character to the lcd at a specific loction at the lcd
 * @param lcd : Pointer to the lcd configuration
 * @param row : the row index
 * @param column : the column index
 * @param chr : Pointer to the custom character
 * @param mem_location : the specific location at the CGRAM
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve   
 */
Std_Return_Type lcd_4bit_send_custom_char_data(const lcd_4bits_t *lcd, uint8 row, uint8 column,
                                                const uint8 chr[], uint8 mem_location){
    Std_Return_Type ret = E_OK;
    uint8 data_pins_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_send_command(lcd, (LCD_CGRAM_START + mem_location * 8));
        for(data_pins_counter = 0; data_pins_counter < 8; data_pins_counter++){
            ret = lcd_4bit_send_char_data(lcd, chr[data_pins_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_location);
    }
    return ret;
}

/**
 * @ref Convert a 1-byte integer to a string 
 * @param value : The integer value
 * @param str : The string number
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve 
 */
Std_Return_Type lcd_4bit_convert_uint8_to_string(uint8 value, uint8 *str){
    Std_Return_Type ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str, '\0', 4);
        sprintf(str, "%d", value);
    }
    return ret;
}

/**
 * @ref Convert a 2-byte integer to a string 
 * @param value : The integer value
 * @param str : The string number
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve 
 */
Std_Return_Type lcd_4bit_convert_uint16_to_string(uint16 value, uint8 *str){
    Std_Return_Type ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str, '\0', 6);
        sprintf(str, "%d", value);
    }
    return ret;
}

/**
 * @ref Convert a 4-byte integer to a string 
 * @param value : The integer value
 * @param str : The string number
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve 
 */
Std_Return_Type lcd_4bit_convert_uint32_to_string(uint32 value, uint8 *str){
    Std_Return_Type ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str, '\0', 11);
        sprintf(str, "%d", value);
    }
    return ret;
}

/**
 * @ref Send the enable signal to send data to the lcd
 * @param lcd : Pointer to the lcd configuration
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve  
 */
static Std_Return_Type lcd_4bit_send_enable(const lcd_4bits_t *lcd){
    Std_Return_Type ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->En), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->En), GPIO_LOW);
    return ret;
}

/**
 * @ref Put the cursor at a specific location at the lcd
 * @param lcd : Pointer to the lcd configuration
 * @param row : the row index
 * @param column : the column index
 * @return E_OK : The function has done successfully
 *         E_NOT_OK : The function has issue to be solve  
 */
static Std_Return_Type lcd_4bit_set_cursor(const lcd_4bits_t *lcd, uint8 row, uint8 column){
    Std_Return_Type ret = E_OK;
    column--;
    switch(row){
        case ROW1 :
            ret = lcd_4bit_send_command(lcd, (0x80 + column)); break;
        case ROW2 :
            ret = lcd_4bit_send_command(lcd, (0xC0 + column)); break;    
        case ROW3 :
            ret = lcd_4bit_send_command(lcd, (0x94 + column)); break;    
        case ROW4 :
            ret = lcd_4bit_send_command(lcd, (0xD4 + column)); break;    
        default : break;
    }
    return ret;
}