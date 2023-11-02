/* 
 * File:   application.c
 * Author: Abdo Halem
 *
 * Created on October 13, 2023, 10:40 PM
 */

#include "application.h"

inline void Auto_Control();
inline void Sensor_Processing();
inline void Speed_Control();

uint16 adc1_result = 0;
uint8 control_mode = 0;
uint8 speed_select = 0;
uint8 motor_speed = 0;     uint8 motor_speed_text[3];
uint16 lm_temperature = 0; uint8 lm_temperature_text[3];

int main(){
    Std_Return_Type ret = E_OK;
    ret = ECU_Initialize();
    Sensor_Processing();
    while(1){
        ret = EEPROM_Read(&control_mode, CONTROL_MODE_ADDRESS);
        if(0 == control_mode){
            /* Interfacing Text */
            ret &= lcd_4bit_send_command(&lcd, LCD_CLEAR_DISPLAY);
            Sensor_Processing();
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW1, 1, (uint8*)"Temperature: ");
            ret &= lcd_4bit_send_string_data(&lcd, lm_temperature_text);
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW2, 1, (uint8*)"Fan Speed: ");
            ret &= lcd_4bit_convert_uint8_to_string((uint8)motor_speed, (uint8*)motor_speed_text);
            ret &= lcd_4bit_send_string_data(&lcd, motor_speed_text);
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW3, 1, (uint8*)"1 => Auto Control");
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW4, 1, (uint8*)"2 => Manual Control");
            while(0 == control_mode){
                Sensor_Processing();
                ret &= lcd_4bit_send_string_data_pos(&lcd, ROW1, 14, lm_temperature_text);
                ret &= keypad_get_button(&keypad, &control_mode);
                ret &= keypad_get_button(&keypad, &control_mode);
                ret &= keypad_get_button(&keypad, &control_mode);
                ret &= keypad_get_button(&keypad, &control_mode);
            }
        }
        
        if('1' == control_mode){
            ret &= EEPROM_Write(control_mode, CONTROL_MODE_ADDRESS);
            ret &= lcd_4bit_send_command(&lcd, LCD_CLEAR_DISPLAY);
            Sensor_Processing();
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW1, 3, (uint8*)" Auto Controlled");
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW2, 1, (uint8*)"Temperature: ");
            ret &= lcd_4bit_send_string_data(&lcd, lm_temperature_text);
            Auto_Control();
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW4, 1, (uint8*)"0 => main menu");
            while('0' != control_mode){
                Sensor_Processing();
                ret &= lcd_4bit_send_string_data_pos(&lcd, ROW2, 14, lm_temperature_text);
                Auto_Control();
                ret &= keypad_get_button(&keypad, &control_mode);
                ret &= keypad_get_button(&keypad, &control_mode);
                ret &= keypad_get_button(&keypad, &control_mode);
                ret &= keypad_get_button(&keypad, &control_mode);
            }
            ret &= EEPROM_Write(0, CONTROL_MODE_ADDRESS);
        }
        else if('2' == control_mode){
            ret &= EEPROM_Write(control_mode, CONTROL_MODE_ADDRESS);
            ret &= lcd_4bit_send_command(&lcd, LCD_CLEAR_DISPLAY);
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW1, 1, (uint8*)"1 => Low");
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW2, 1, (uint8*)"2 => Medium");
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW3, 1, (uint8*)"3 => High");
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW4, 1, (uint8*)"4 => Turn off");
            speed_select = 0;
            while(0 == speed_select){
                ret &= keypad_get_button(&keypad, &speed_select);
            }
            Speed_Control();
        }
        else{
            ret &= lcd_4bit_send_command(&lcd, LCD_CLEAR_DISPLAY);
            ret &= lcd_4bit_send_string_data_pos(&lcd, ROW1, 5, (uint8*)"Invalid Mode!");
            __delay_ms(700);
            ret &= EEPROM_Write(0, CONTROL_MODE_ADDRESS);
        }
    }
    
    return (EXIT_SUCCESS);
}

inline void Sensor_Processing(){
    Std_Return_Type ret = E_OK;
    ret &= ADC_Get_ConversionBlocking(&adc_1, ADC_CHANNEL_AN0, &adc1_result);
    lm_temperature = (uint16)(adc1_result * 4.883f);
    lm_temperature /= 10;
    ret &= lcd_4bit_convert_uint8_to_string((uint8)lm_temperature, lm_temperature_text);
}

inline void Auto_Control(){
    Std_Return_Type ret = E_OK;
    ret &= CCP1_PWM_Start();
    if(lm_temperature < 18){
        ret &= CCP1_PWM_Set_Duty(0);
        ret &= led_turn_off(&led1);
        ret &= led_turn_off(&led2);
        ret &= led_turn_off(&led3);
        motor_speed = 0;
        ret &= lcd_4bit_send_string_data_pos(&lcd, ROW3, 1, (uint8*)"Fan Speed: 0");
    }
    else if((lm_temperature >= 18) && (lm_temperature < 25)){
        ret &= CCP1_PWM_Set_Duty(80);
        ret &= led_turn_on(&led1);
        ret &= led_turn_off(&led2);
        ret &= led_turn_off(&led3);
        motor_speed = 1;
        ret &= lcd_4bit_send_string_data_pos(&lcd, ROW3, 1, (uint8*)"Fan Speed: 1");
    }
    else if((lm_temperature >= 25) && (lm_temperature < 35)){
        ret &= CCP1_PWM_Set_Duty(90);
        ret &= led_turn_on(&led2);
        ret &= led_turn_off(&led1);
        ret &= led_turn_off(&led3);
        motor_speed = 2;
        ret &= lcd_4bit_send_string_data_pos(&lcd, ROW3, 1, (uint8*)"Fan Speed: 2");
    }
    else if(lm_temperature >= 35){
        ret &= CCP1_PWM_Set_Duty(100);
        ret &= led_turn_on(&led3);
        ret &= led_turn_off(&led1);
        ret &= led_turn_off(&led2);
        motor_speed = 3;
        ret &= lcd_4bit_send_string_data_pos(&lcd, ROW3, 1, (uint8*)"Fan Speed: 3");
    }
}

inline void Speed_Control(){
    Std_Return_Type ret = E_OK;
    ret &= CCP1_PWM_Start();
    
    if('1' == speed_select){
        motor_speed = 1;
        ret &= CCP1_PWM_Set_Duty(80);
        ret &= led_turn_on(&led1);
        ret &= led_turn_off(&led2); ret &= led_turn_off(&led3);
    }
    else if('2' == speed_select){
        motor_speed = 2;
        ret &= CCP1_PWM_Set_Duty(90);
        ret &= led_turn_on(&led2);
        ret &= led_turn_off(&led1); ret &= led_turn_off(&led3);
    }
    else if('3' == speed_select){
        motor_speed = 3;
        ret &= CCP1_PWM_Set_Duty(100);
        ret &= led_turn_on(&led3);
        ret &= led_turn_off(&led1); ret &= led_turn_off(&led2);
    }
    else if('4' == speed_select){
        motor_speed = 0;
        ret &= CCP1_PWM_Set_Duty(0);
        ret &= led_turn_off(&led1); ret &= led_turn_off(&led2); ret &= led_turn_off(&led3);
    }
    else if('0' == speed_select){
        ret &= EEPROM_Write(0, CONTROL_MODE_ADDRESS);
    }
    else{
        speed_select = 0;
    }
}