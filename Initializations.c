/* 
 * File:   initializations.c
 * Author: Abdo Halem
 *
 * Created on September 1, 2023, 3:11 PM
 */
#include "Initializations.h"

lcd_4bits_t lcd = {
    .Rs.port = PORTC_INDEX, .Rs.pin = PIN0,
    .Rs.direction = GPIO_DIRECTION_OUTPUT, .Rs.logic = GPIO_LOW,
    .En.port = PORTC_INDEX, .En.pin = PIN1,
    .En.direction = GPIO_DIRECTION_OUTPUT, .En.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX, .lcd_data[0].pin = PIN4,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX, .lcd_data[1].pin = PIN5,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX, .lcd_data[2].pin = PIN6,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX, .lcd_data[3].pin = PIN7,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[3].logic = GPIO_LOW,
};

keypad_t keypad = {
    .rows[0].port = PORTD_INDEX, .rows[0].pin = PIN0,
    .rows[0].direction = GPIO_DIRECTION_OUTPUT, .rows[0].logic = GPIO_LOW,
    .rows[1].port = PORTD_INDEX, .rows[1].pin = PIN1,
    .rows[1].direction = GPIO_DIRECTION_OUTPUT, .rows[1].logic = GPIO_LOW,
    .rows[2].port = PORTD_INDEX, .rows[2].pin = PIN2,
    .rows[2].direction = GPIO_DIRECTION_OUTPUT, .rows[2].logic = GPIO_LOW,
    .rows[3].port = PORTD_INDEX, .rows[3].pin = PIN3,
    .rows[3].direction = GPIO_DIRECTION_OUTPUT, .rows[3].logic = GPIO_LOW,
    .columns[0].port = PORTD_INDEX, .columns[0].pin = PIN4,
    .columns[0].direction = GPIO_DIRECTION_INPUT, .columns[0].logic = GPIO_LOW,
    .columns[1].port = PORTD_INDEX, .columns[1].pin = PIN5,
    .columns[1].direction = GPIO_DIRECTION_INPUT, .columns[1].logic = GPIO_LOW,
    .columns[2].port = PORTD_INDEX, .columns[2].pin = PIN6,
    .columns[2].direction = GPIO_DIRECTION_INPUT, .columns[2].logic = GPIO_LOW,
    .columns[3].port = PORTD_INDEX, .columns[3].pin = PIN7,
    .columns[3].direction = GPIO_DIRECTION_INPUT, .columns[3].logic = GPIO_LOW,
};

dc_motor_t motor1 = {
    .pin1.port = PORTC_INDEX, .pin1.pin = PIN2,
    .pin1.direction = GPIO_DIRECTION_OUTPUT, .pin1.logic = GPIO_LOW,
    .pin2.port = PORTC_INDEX, .pin2.pin = PIN3,
    .pin2.direction = GPIO_DIRECTION_OUTPUT, .pin2.logic = GPIO_LOW,
};

led_t led1 = {
    .led_config.port = PORTA_INDEX, .led_config.pin = PIN1,
    .led_config.direction = GPIO_DIRECTION_OUTPUT, .led_config.logic = GPIO_LOW
};

led_t led2 = {
    .led_config.port = PORTA_INDEX, .led_config.pin = PIN2,
    .led_config.direction = GPIO_DIRECTION_OUTPUT, .led_config.logic = GPIO_LOW
};

led_t led3 = {
    .led_config.port = PORTA_INDEX, .led_config.pin = PIN3,
    .led_config.direction = GPIO_DIRECTION_OUTPUT, .led_config.logic = GPIO_LOW
};

adc_config_t adc_1 = {
#if CCP1_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
    .ADC_InterruptHandler = NULL,
#endif
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .voltage_reference = ADC_VDD_VREF,
};

timer2_t timer2_obj = {
#if TIMER2_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
    .Timer2_Interrupt_Handler = NULL,
#endif
    .postscaler_value = TIMER2_POSTSCALER_DIV_BY_1,
    .prescaler_value = TIMER2_PRESCALER_DIV_BY_1,
    .timer2_preload_value = 0
};

ccp1_t ccp1_obj = {
#if CCP1_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
    .CCP1_InterruptHandler = NULL,
#endif
    .ccp_mode = CCP1_PWM_MODE_SELECTED,
    .PWM_Frequency = (uint32)80000,
    .ccp_pin.port = PORTC_INDEX,
    .ccp_pin.pin = PIN2,
    .ccp_pin.direction = GPIO_DIRECTION_OUTPUT,

    .timer2_postscaler_value = 1,
    .timer2_prescaler_value = 1
};

Std_Return_Type ECU_Initialize(){
    Std_Return_Type ret = E_OK;
    ret &= lcd_4bit_initialize(&lcd);
    ret &= keypad_initialize(&keypad);
    ret &= dc_motor_initialize(&motor1);
    ret &= led_initialize(&led1);
    ret &= led_initialize(&led2);
    ret &= led_initialize(&led3);
    ret &= ADC_Init(&adc_1);
    ret &= Timer2_Init(&timer2_obj);
    ret &= CCP1_Init(&ccp1_obj);
    return ret;
}