/* 
 * File:   EEPROM.h
 * Author: Abdo Halem
 *
 * Created on October 28, 2023, 11:36 AM
 */

#include "EEPROM.h"

Std_Return_Type EEPROM_Write(uint8 data, uint16 memory_address){
    Std_Return_Type ret = E_OK;
    /* Read the Interrupt Status "Enabled or Disabled" */
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    /* Update the Address Registers */
    EEADRH = (uint8)((memory_address >> 8) & 0x03);
    EEADR = (uint8)memory_address;
    /* Update the Data Register */
    EEDATA = data;
    /* Select Access data EEPROM memory */
    EEPROM_MEMORY_ACCESS();
    EEPROM_FLASH_PROGRAM_MEMORY_ACCESS();
    /* Allows write cycles to Flash program/data EEPROM */
    EEPROM_WRITE_ENABLE();
    /* Disable Interrupts */
    INTERRUPT_GLOBAL_INTERRUPT_DISABLE();
    /* Write the Required Sequence */
    EECON2 = 0x55;
    EECON2 = 0x0AA;
    /* Initiates a data EEPROM erase/write cycle */
    EEPROM_START_WRITE();
    /* Wait for write to complete */
    while(EECON1bits.WR);
    /* Inhibits write cycles to Flash program/data EEPROM */
    EEPROM_WRITE_DISABLE();
    /* Clear the Interrupt flag */
    PIR2bits.EEIF = 0;
    /* Restore the Interrupt Status "Enabled or Disabled" */
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}

Std_Return_Type EEPROM_Read(uint8 *data, uint16 memory_address){
    Std_Return_Type ret = E_OK;
    if(NULL == data){
        ret = E_NOT_OK;
    }
    else{
        /* Update the Address Registers */
        EEADRH = (uint8)((memory_address >> 8) & 0x03);
        EEADR = (uint8)memory_address;
        /* Select Access data EEPROM memory */
        EEPROM_FLASH_PROGRAM_MEMORY_ACCESS();
        EEPROM_MEMORY_ACCESS();
        /* Initiates a data EEPROM read cycle */
        EEPROM_START_READ();
        NOP(); /* NOPs may be required for latency at high frequencies */
        NOP(); /* NOPs may be required for latency at high frequencies */
        *data = EEDATA;
    }
    return ret;
}