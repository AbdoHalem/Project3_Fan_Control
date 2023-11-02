/* 
 * File:   mcal_interrupt_config.h
 * Author: Abdo Halem
 *
 * Created on September 17, 2023, 4:17 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section: Includes*/
#include "mcal_interrupt_gen.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations*/
#define INTERRUPT_OCCURED     1
#define INTERRUPT_NOT_OCCURED 0

#define INTERRUPT_ENABLED  1
#define INTERRUPT_DISABLED 0

#define INTERRUPT_PRIORITY_ENABLED_CFG  1
#define INTERRUPT_PRIORITY_DISABLED_CFG 0

/* Section: Macro Function Declarations*/
#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_PRIORITY_ENABLE()   (RCONbits.IPEN = 1)
#define INTERRUPT_PRIORITY_DISABLED() (RCONbits.IPEN = 0)
/*Enables and disables all high priority interrupts*/
#define INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE()  (INTCONbits.GIEH = 1)
#define INTERRUPT_GLOBAL_INTERRUPT_HIGH_DISABLE() (INTCONbits.GIEH = 0)
/* Enables and disables all low priority interrupts*/
#define INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE()   (INTCONbits.GIEL = 1)
#define INTERRUPT_GLOBAL_INTERRUPT_LOW_DISABLE()  (INTCONbits.GIEL = 0)
#else
/* Enables all unmasked interrupts */
#define INTERRUPT_GLOBAL_INTERRUPT_ENABLE()  (INTCONbits.GIE = 1)
#define INTERRUPT_GLOBAL_INTERRUPT_DISABLE() (INTCONbits.GIE = 0)
/* Enables all unmasked peripheral interrupts */
#define INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE() (INTCONbits.PEIE = 1)
#define INTERRUPT_PEIRPHERAL_INTERRUPT_DISABLE() (INTCONbits.PEIE = 0)
#endif

/* Section: Data Type Declarations*/
typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority_t;

/* Section: Software Interfaces Declarations*/



#endif	/* MCAL_INTERRUPT_CONFIG_H */

