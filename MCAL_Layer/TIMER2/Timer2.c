/* 
 * File:   Timer2.h
 * Author: Abdo Halem
 *
 * Created on October 27, 2023, 6:01 PM
 */

#include "Timer2.h"
#if TIMER2_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
    static void (* TMR2_InterruptHandler)(void) = NULL;
#endif
    
uint8 timer2_preload_value;

Std_Return_Type Timer2_Init(const timer2_t *timer2){
    Std_Return_Type ret = E_OK;
    if(NULL == timer2){
        ret = E_NOT_OK;
    }
    else{
        TIMER2_DISABLE();
        TIMER2_SET_POSTSCALER(timer2->postscaler_value);
        TIMER2_SET_PRESCALER(timer2->prescaler_value);
        TMR2 = timer2->timer2_preload_value;
        /* Interrupt configuration */
#if TIMER2_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_FLAG_CLEAR();
        TMR2_InterruptHandler = timer2->Timer2_Interrupt_Handler;
        /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        Interrupt_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER1_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER1_LowPrioritySet();
        }
        else{/* Nothing */}
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
        TIMER2_ENABLE();
    }
    return ret;
}

Std_Return_Type Timer2_DeInit(const timer2_t *timer2){
    Std_Return_Type ret = E_OK;
    if(NULL == timer2){
        ret = E_NOT_OK;
    }
    else{
        TIMER2_DISABLE();
#if TIMER2_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}

Std_Return_Type Timer2_Write_Value(const timer2_t *timer2, uint8 value){
    Std_Return_Type ret = E_OK;
    if(NULL == timer2){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = value;
    }
    return ret;
}

Std_Return_Type Timer2_Read_Value(const timer2_t *timer2, uint8 *value){
    Std_Return_Type ret = E_OK;
    if((NULL == timer2) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        *value = TMR2;
    }
    return ret;
}

/*void TIMER2_ISR(){
    TIMER2_INTERRUPT_FLAG_CLEAR();
    TMR2 = timer2_preload_value;
    if(TMR2_InterruptHandler){
        TMR2_InterruptHandler();
    }
}*/