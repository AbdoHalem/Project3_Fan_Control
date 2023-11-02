/* 
 * File:   mcal_internal_interrupt.h
 * Author: Abdo Halem
 *
 * Created on September 17, 2023, 3:44 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section: Includes*/
#include "mcal_interrupt_config.h"

/* Section: Macro Declarations*/


/* Section: Macro Function Declarations*/
/* =============================== TIMER0 Start =============================== */
//#if TIMER0_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
/* Enable, Disable the Timer0 interrupt and clear the interrupt flag */
/*#define TIMER0_INTERRUPT_ENABLE()     (INTCONbits.TMR0IE = 1)
#define TIMER0_INTERRUPT_DISABLE()    (INTCONbits.TMR0IE = 0)
#define TIMER0_INTERRUPT_FLAG_CLEAR() (INTCONbits.TMR0IF = 0)

#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_HIGH_PRIORITY_SET() (INTCON2bits.TMR0IP = 1)
#define TIMER0_INTERRUPT_LOW_PRIORITY_SET()  (INTCON2bits.TMR0IP = 0)
#endif
#endif*/
/* =============================== TIMER0 End =============================== */

/* =============================== ADC Start =============================== */
#if ADC_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
/* Enable, Disable the ADC interrupt and clear the interrupt flag */
#define ADC_INTERRUPT_ENABLE()     (PIE1bits.ADIE = 1)
#define ADC_INTERRUPT_DISABLE()    (PIE1bits.ADIE = 0)
#define ADC_INTERRUPT_FLAG_CLEAR() (PIR1bits.ADIF = 0)

#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_HIGH_PRIORITY_SET() (IPR1bits.ADIP = 1)
#define ADC_INTERRUPT_LOW_PRIORITY_SET()  (IPR1bits.ADIP = 0)
#endif
#endif
/* =============================== ADC End =============================== */

/* =============================== TIMER2 Start =============================== */
#if TIMER2_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
/* Enable, Disable the Timer2 interrupt and clear the interrupt flag */
#define TIMER2_INTERRUPT_ENABLE()     (PIE1bits.TMR2IE = 1)
#define TIMER2_INTERRUPT_DISABLE()    (PIE1bits.TMR2IE = 0)
#define TIMER2_INTERRUPT_FLAG_CLEAR() (PIR1bits.TMR2IF = 0)

#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_HIGH_PRIORITY_SET() (IPR1bits.TMR2IP = 1)
#define TIMER2_INTERRUPT_LOW_PRIORITY_SET()  (IPR1bits.TMR2IP = 0)
#endif
#endif
/* =============================== TIMER2 End =============================== */

/* =============================== CCP1 Start =============================== */
#if CCP1_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
/* Enable, Disable the CCP1 interrupt and clear the interrupt flag */
#define CCP1_INTERRUPT_ENABLE()     (PIE1bits.CCP1IE = 1)
#define CCP1_INTERRUPT_DISABLE()    (PIE1bits.CCP1IE = 0)
#define CCP1_INTERRUPT_FLAG_CLEAR() (PIR1bits.CCP1IF = 0)

#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUPT_HIGH_PRIORITY_SET() (IPR1bits.CCP1IP = 1)
#define CCP1_INTERRUPT_LOW_PRIORITY_SET()  (IPR1bits.CCP1IP = 0)
#endif
#endif
/* =============================== CCP1 End =============================== */

/* =============================== EEPROM Start =============================== */
#if EEPROM_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
/* Enable, Disable the EEPROM interrupt and clear the interrupt flag */
#define EEPROM_INTERRUPT_ENABLE()     (PIE2bits.EEIE = 1)
#define EEPROM_INTERRUPT_DISABLE()    (PIE2bits.EEIE = 0)
#define EEPROM_INTERRUPT_FLAG_CLEAR() (PIR2bits.EEIF = 0)

#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE
#define EEPROM_INTERRUPT_HIGH_PRIORITY_SET() (IPR2bits.EEIP = 1)
#define EEPROM_INTERRUPT_LOW_PRIORITY_SET()  (IPR2bits.EEIP = 0)
#endif
#endif
/* =============================== EEPROM End =============================== */

/* Section: Data Type Declarations*/


/* Section: Software Interfaces Declarations*/


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

