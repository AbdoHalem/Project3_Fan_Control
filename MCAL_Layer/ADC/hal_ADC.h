/* 
 * File:   hal_ADC.h
 * Author: Abdo Halem
 *
 * Created on October 13, 2023, 11:26 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Section: Includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* Section: Macro Declarations*/
#define ADC_AN0_ANALOG_FUNCTIONALITY   0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY   0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY   0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY   0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY   0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY   0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY   0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY   0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY   0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY   0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY  0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY  0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY  0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY   0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY  0x0F

#define ADC_CONVERSION_COMPLETED  0
#define ADC_CONVERSION_INPROGRESS 1

#define ADC_VDD_VREF      0
#define ADC_EXTERNAL_VREF 1

/* Section: Macro Function Declarations */
#define ADC_MODULE_ENABLE()  (ADCON0bits.ADON = 1)
#define ADC_MODULE_DISABLE() (ADCON0bits.ADON = 0)

#define ADC_START_CONVERSION()  (ADCON0bits.GO_nDONE = 1)
#define ADC_END_CONVERSION()    (ADCON0bits.GO_nDONE = 0)
#define ADC_CONVERSION_STATUS() (ADCON0bits.GO_nDONE)

#define ADC_VREF_BY_VDD()             do{ADCON1bits.VCFG0 = 0;\
                                        ADCON1bits.VCFG1 = 0;\
                                        }while(0)
#define ADC_VREF_BY_EXTERNAL_SOURCE() do{ADCON1bits.VCFG0 = 1;\
                                        ADCON1bits.VCFG1 = 1;\
                                        }while(0)

#define ADC_RESULT_RIGHT_JUSTIFICATION() (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_JUSTIFICATION()  (ADCON2bits.ADFM = 0)

#define ADC_ANALOG_FUNCTIONALITY(VALUE)    (ADCON1bits.PCFG = VALUE)
#define ADC_ACQUISITION_TIME_SELECT(VALUE) (ADCON2bits.ACQT = VALUE)
#define ADC_CONVERSION_CLOCK_SELECT(VALUE) (ADCON2bits.ADCS = VALUE)
#define ADC_SELECT_CHANNEL(CHANNEL)        (ADCON0bits.CHS = CHANNEL)

/* Section: Data Type Declarations*/
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
}adc_channel_select_t;

typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_acquisition_time_t;

typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}adc_conversion_clock_t;

typedef struct{
#if ADC_INTERRUPT_ENABLED == INTERRUPT_FEATURE_ENABLE
    void (*ADC_InterruptHandler)(void);
#if INERRUPT_PRIORITY_ENABLED == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t adc_priority;
#endif
#endif
    adc_channel_select_t adc_channel;
    adc_acquisition_time_t acquisition_time;
    adc_conversion_clock_t conversion_clock;
    uint8 voltage_reference : 1;
    uint8  : 7;
}adc_config_t;

/* Section: Software Interfaces Declarations*/
Std_Return_Type ADC_Init(const adc_config_t *_adc);
Std_Return_Type ADC_DeInit(const adc_config_t *_adc);
Std_Return_Type ADC_Select_Channel(adc_channel_select_t channel);
Std_Return_Type ADC_Start_Conversion(const adc_config_t *_adc);
Std_Return_Type ADC_Get_Conversion_Status(const adc_config_t *_adc, uint8 *conversion_status);
Std_Return_Type ADC_Get_Conversion_Result(const adc_config_t *_adc, uint16 *conversion_result);
Std_Return_Type ADC_Get_ConversionBlocking(const adc_config_t *_adc, adc_channel_select_t channel, uint16 *conversion_result);

#endif	/* HAL_ADC_H */

