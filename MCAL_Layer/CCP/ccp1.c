/* 
 * File:   ccp1.h
 * Author: Abdo Halem
 *
 * Created on October 27, 2023, 8:56 PM
 */

#include "ccp1.h"

#if CCP1_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
    static void (*CCP1_InterruptHandler)(void) = NULL;
#endif
    
static void CCP1_PWM_Mode_Config(const ccp1_t *ccp_obj);
static void CCP1_Interrupt_Config(const ccp1_t *_ccp_obj);

Std_Return_Type CCP1_Init(const ccp1_t *ccp_obj){
    Std_Return_Type ret = E_OK;
    if(NULL == ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        CCP1_SET_MODE(CCP_MODULE_DISABLED);
#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED
        /* CCP Module PWM Mode Initialization */
        if(CCP1_PWM_MODE_SELECTED == ccp_obj->ccp_mode){
            CCP1_PWM_Mode_Config(ccp_obj);
        }
#endif
        /* PIN Configurations */
        ret = gpio_pin_initialize(&(ccp_obj->ccp_pin));
        /* Interrupt Configurations for CCP1 Modules */
        CCP1_Interrupt_Config(ccp_obj);
    }
    return ret;
}

Std_Return_Type CCP1_DeInit(const ccp1_t *ccp_obj){
    Std_Return_Type ret = E_OK;
    if(NULL == ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        CCP1_SET_MODE(CCP_MODULE_DISABLED);
#if CCP1_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}

#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED)
Std_Return_Type CCP1_PWM_Set_Duty(const uint8 duty_cycle){
    Std_Return_Type ret = E_OK;
    uint16 duty_temp = 0;
    duty_temp = (uint16)(4 * (PR2 + 1) * (duty_cycle / 100.0));
    CCP1CONbits.DC1B = (uint8)(duty_temp & 0x0003); 
    CCPR1L = (uint8)(duty_temp >> 2);
    return ret;
}

Std_Return_Type CCP1_PWM_Start(){
    Std_Return_Type ret = E_OK;
    CCP1_SET_MODE(CCP_PWM_MODE);
    return ret;
}

Std_Return_Type CCP1_PWM_Stop(){
    Std_Return_Type ret = E_OK;
    CCP1_SET_MODE(CCP_MODULE_DISABLED);
    return ret;
}

static void CCP1_PWM_Mode_Config(const ccp1_t *ccp_obj){
    CCP1_SET_MODE(CCP_PWM_MODE);
    /* PWM Frequency Initialization */
    PR2 = (uint8)((_XTAL_FREQ / (ccp_obj->PWM_Frequency * 4.0 * ccp_obj->timer2_prescaler_value * 
                   ccp_obj->timer2_postscaler_value)) - 1);
}

#endif

static void CCP1_Interrupt_Config(const ccp1_t *_ccp_obj){
/* CCP1 Interrupt Configurations */ 
#if CCP1_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
    CCP1_INTERRUPT_ENABLE();
    CCP1_INTERRUPT_FLAG_CLEAR();
    CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
/* Interrupt Priority Configurations */
#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE 
    INTERRUPT_PriorityLevelsEnable();
    if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->CCP1_priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        CCP1_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP1_priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        CCP1_LowPrioritySet();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
    INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif          
#endif    
         
}
