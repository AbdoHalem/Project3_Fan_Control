/* 
 * File:   EEPROM.h
 * Author: Abdo Halem
 *
 * Created on October 28, 2023, 11:36 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

/* Section: Includes*/
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section: Macro Declarations*/
#define EEPROM_WRITE_OPERATION_FAILED    1
#define EEPROM_WRITE_OPERATION_COMPLETED 0

/* Section: Macro Function Declarations */
#define EEPROM_FLASH_PROGRAM_MEMORY_ACCESS() (EECON1bits.CFGS = 0)
#define CONFIGURATION_REGISTERS_ACCESS()     (EECON1bits.CFGS = 1)

#define EEPROM_MEMORY_ACCESS()        (EECON1bits.EEPGD = 0)
#define FLASH_PROGRAM_MEMORY_ACCESS() (EECON1bits.EEPGD = 1)

#define EEPROM_WRITE_ENABLE()  (EECON1bits.WREN = 1)
#define EEPROM_WRITE_DISABLE() (EECON1bits.WREN = 0)

#define EEPROM_START_WRITE()  (EECON1bits.WR = 1)
#define EEPROM_START_READ()   (EECON1bits.RD = 1)
#define EEPROM_WRITE_STATUS() (EECON1bits.WRERR)

/* Section: Data Type Declarations*/

/* Section: Software Interfaces Declarations*/
Std_Return_Type EEPROM_Write(uint8 data, uint16 memory_address);
Std_Return_Type EEPROM_Read(uint8 *data, uint16 memory_address);

#endif	/* EEPROM_H */

