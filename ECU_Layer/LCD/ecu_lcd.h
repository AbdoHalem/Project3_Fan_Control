/* 
 * File:   ecu_lcd.h
 * Author: Abdo Halem
 *
 * Created on August 28, 2023, 10:52 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/* Section: Includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations*/
#define LCD_CLEAR_DISPLAY              0x01
#define LCD_RETURN_HOME                0x02
#define LCD_ENTRY_MODE_DEC_SHIFT_OFF   0x04
#define LCD_ENTRY_MODE_DEC_SHIFT_ON    0x05
#define LCD_ENTRY_MODE_INC_SHIFT_OFF   0x06
#define LCD_ENTRY_MODE_INC_SHIFT_ON    0x07
#define LCD_CURSOR_OFF_DISPLAY_OFF     0x08
#define LCD_CURSOR_OFF_DISPLAY_ON      0x0C
#define LCD_CURSOR_ON_BLINKING_OFF     0x0E
#define LCD_CURSOR_ON_BLINKING_ON      0x0F
#define LCD_CURSOR_MOVE_SHIFT_LEFT     0x10
#define LCD_CURSOR_MOVE_SHIFT_RIGHT    0x14
#define LCD_DISPLAY_SHIFT_LEFT         0x18
#define LCD_DISPLAY_SHIFT_RIGHT        0x1C

#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F
#define LCD_DISPLAY_OFF_CURSOR_OFF              0x08

#define LCD_8BIT_BUS_MODE_2LINES         0x38
#define LCD_4BIT_BUS_MODE_2LINES         0x28

#define LCD_DDRAM_START                0x80
#define LCD_CGRAM_START                0x40

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4


/* Section: Macro Function Declarations*/


/* Section: Data Type Declarations*/
typedef struct{
    pin_config_t Rs;
    pin_config_t En;
    pin_config_t lcd_data[4];
}lcd_4bits_t;

/* Section: Software Interfaces Declarations*/
Std_Return_Type lcd_4bit_initialize(const lcd_4bits_t *lcd);
Std_Return_Type lcd_4bit_send_command(const lcd_4bits_t *lcd, uint8 command);
Std_Return_Type lcd_4bit_send_char_data(const lcd_4bits_t *lcd, uint8 data);
Std_Return_Type lcd_4bit_send_char_data_pos(const lcd_4bits_t *lcd, uint8 row, uint8 column, uint8 data);
Std_Return_Type lcd_4bit_send_custom_char_data(const lcd_4bits_t *lcd, uint8 row, uint8 column,
                                                const uint8 chr[], uint8 mem_location);
Std_Return_Type lcd_4bit_send_string_data(const lcd_4bits_t *lcd, uint8 *str);
Std_Return_Type lcd_4bit_send_string_data_pos(const lcd_4bits_t *lcd, uint8 row, uint8 column, uint8 *str);

Std_Return_Type lcd_4bit_convert_uint8_to_string(uint8 value, uint8 *str);
Std_Return_Type lcd_4bit_convert_uint16_to_string(uint16 value, uint8 *str);
Std_Return_Type lcd_4bit_convert_uint32_to_string(uint32 value, uint8 *str);

#endif	/* ECU_LCD_H */

