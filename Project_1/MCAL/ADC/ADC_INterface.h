/*
 * ADC_INterface.h
 *
 * Created: 8/2/2026 2:14:47 AM
 *  Author: Eltawel
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/* ADC Channels Enum */
typedef enum
{
    ADC0 = 0,
    ADC1,
    ADC2,
    ADC3,
    ADC4,
    ADC5,
    ADC6,
    ADC7
} ADC_Channel_t;

/* ADC Prescaler Options Enum */
typedef enum
{
    ADC_PRESCALER_2 = 1,
    ADC_PRESCALER_4,
    ADC_PRESCALER_8,
    ADC_PRESCALER_16,
    ADC_PRESCALER_32,
    ADC_PRESCALER_64,
    ADC_PRESCALER_128
} ADC_Prescaler_t;


/**
 * @brief  Initializes the Analog-to-Digital Converter (ADC) peripheral
 * @param  None
 * @return None
 * @note   Must be called before calling ADC_u16GetChannelReading()
 */
void ADC_VoidInit(void);

/**
 * @brief  Reads the converted digital value from a specific ADC channel
 * @param  copy_tChannel Selects the ADC channel (ADC_CHANNEL0 to ADC_CHANNEL7)
 * @return u16 Returns a 10-bit digital value ranging from 0 to 1023
 */
u16 ADC_u16GetChannelReading(ADC_Channel_t copy_tChannel);

#endif /* ADC_INTERFACE_H_ */