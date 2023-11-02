/* 
 * File:   hal_ADC.c
 * Author: Abdo Halem
 *
 * Created on October 13, 2023, 11:26 PM
 */

#include "hal_ADC.h"
static inline void ADC_Input_Channel_Configuration(adc_channel_select_t channel);
static inline void ADC_Voltage_Reference(const adc_config_t *_adc);

#if ADC_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
static void (* ADC_DefaultInterruptHandler)(void) = NULL;
#endif

Std_Return_Type ADC_Init(const adc_config_t *_adc){
    Std_Return_Type ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        /* Disable ADC_MODULE */
        ADC_MODULE_DISABLE();
        /* Configure the acquisition time */
        ADC_ACQUISITION_TIME_SELECT(_adc->acquisition_time);
        /* Configure the conversion clock */
        ADC_CONVERSION_CLOCK_SELECT(_adc->conversion_clock);
        /* Configure the default channel */
        ADC_SELECT_CHANNEL(_adc->adc_channel);
        ADC_Input_Channel_Configuration(_adc->adc_channel);
        /* Configure the interrupt */
#if ADC_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
        ADC_DefaultInterruptHandler = _adc->ADC_InterruptHandler;
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_FLAG_CLEAR();
#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
        /* Configure result format */
        ADC_RESULT_RIGHT_JUSTIFICATION();
        /* Configure voltage reference */
        ADC_Voltage_Reference(_adc);
        /* Enable ADC_MODULE */
        ADC_MODULE_ENABLE();
    }
    return ret;
}

Std_Return_Type ADC_DeInit(const adc_config_t *_adc){
    Std_Return_Type ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        /* Disable ADC_MODULE */
        ADC_MODULE_DISABLE();
        /* Disable the interrupt */
#if ADC_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}

Std_Return_Type ADC_Select_Channel(adc_channel_select_t channel){
    Std_Return_Type ret = E_OK;
    ADC_SELECT_CHANNEL(channel);
    ADC_Input_Channel_Configuration(channel);
    return ret;
}

Std_Return_Type ADC_Start_Conversion(const adc_config_t *_adc){
    Std_Return_Type ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        while(ADC_CONVERSION_INPROGRESS == ADC_CONVERSION_STATUS());
        ADC_START_CONVERSION();
    }
    return ret;
}

Std_Return_Type ADC_Get_Conversion_Status(const adc_config_t *_adc, uint8 *conversion_status){
    Std_Return_Type ret = E_OK;
    if((NULL == _adc) || (NULL == conversion_status)){
        ret = E_NOT_OK;
    }
    else{
        *conversion_status = ADC_CONVERSION_STATUS();
    }
    return ret;
}

Std_Return_Type ADC_Get_Conversion_Result(const adc_config_t *_adc, uint16 *conversion_result){
    Std_Return_Type ret = E_OK;
    if((NULL == _adc) || (NULL == conversion_result)){
        ret = E_NOT_OK;
    }
    else{
        *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
    }
    return ret;
}

Std_Return_Type ADC_Get_ConversionBlocking(const adc_config_t *_adc, adc_channel_select_t channel, uint16 *conversion_result){
    Std_Return_Type ret = E_OK;
    if((NULL == _adc) || (NULL == conversion_result)){
        ret = E_NOT_OK;
    }
    else{
        ret &= ADC_Select_Channel(channel);
        ret &= ADC_Start_Conversion(_adc);
        while(ADC_CONVERSION_INPROGRESS == ADC_CONVERSION_STATUS());
        ret &= ADC_Get_Conversion_Result(_adc, conversion_result);
    }
    return ret;
}

/*void ADC_ISR(){
    ADC_INTERRUPT_FLAG_CLEAR();
    if(ADC_DefaultInterruptHandler){
        ADC_DefaultInterruptHandler();
    }
    else{}
}*/

static inline void ADC_Input_Channel_Configuration(adc_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA, _TRISA_RA0_POSN); break;
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA, _TRISA_RA1_POSN); break;
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA, _TRISA_RA2_POSN); break;
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA, _TRISA_RA3_POSN); break;
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA, _TRISA_RA5_POSN); break;
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE, _TRISE_RE0_POSN); break;
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE, _TRISE_RE1_POSN); break;
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE, _TRISE_RE2_POSN); break;
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB, _TRISB_RB2_POSN); break;
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB, _TRISB_RB3_POSN); break;
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, _TRISB_RB1_POSN); break;
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB, _TRISB_RB4_POSN); break;
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB, _TRISB_RB0_POSN); break;
        default : break;
    }
}

static inline void ADC_Voltage_Reference(const adc_config_t *_adc){
    switch(_adc->voltage_reference){
        case ADC_VDD_VREF : ADC_VREF_BY_VDD(); break;
        case ADC_EXTERNAL_VREF : ADC_VREF_BY_EXTERNAL_SOURCE(); break;
        default : ADC_VREF_BY_VDD(); break;
    }
}