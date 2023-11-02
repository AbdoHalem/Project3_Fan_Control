/* 
 * File:   mcal_interrupt_manager.h
 * Author: Abdo Halem
 *
 * Created on September 17, 2023, 7:19 PM
 */

#include "mcal_interrupt_manager.h"

#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE
void __interrupt() interrupt_manager_high(){
    
}

void __interrupt(low_priority) interrupt_manager_low(){
    
}
#else
void __interrupt() interrupt_manager(){
    /*if((INTERRUPT_ENABLED == PIE1bits.ADIE) && (INTERRUPT_OCCURED == PIR1bits.ADIF)){
        //ADC_ISR();
    }
    if((INTERRUPT_ENABLED == PIE1bits.TMR2IE) && (INTERRUPT_OCCURED == PIR1bits.TMR2IF)){
        TIMER2_ISR();
    }*/
    /*if((INTERRUPT_ENABLED == PIE2bits.EEIE) && (INTERRUPT_OCCURED == PIR2bits.EEIF)){
        EEPROM_ISR();
    }*/
}

#endif