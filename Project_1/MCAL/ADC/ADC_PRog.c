/*
 * ADC_PRog.c
 *
 * Created: 8/2/2026 2:15:02 AM
 *  Author: Eltawel
 */ 
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_INterface.h"
#include "ADC_INterface.h"
#include "ADC_REG.h"

void ADC_VoidInit(void)
{
	/* 1- voltage reference selection */
		SET_BIT(ADMUX_REG, REFS0_BIT);
		CLEAR_BIT(ADMUX_REG, REFS1_BIT);
		
	/* 2- ADC Presacler */
		ADCSRA_REG &= 0xF8;
		ADCSRA_REG |= (1 << ADPS0_BIT) | (1 << ADPS1_BIT) | (1 << ADPS2_BIT);
	
	/* 3- ADC Enable */
		SET_BIT(ADCSRA_REG, ADEN_BIT);
}

u16 ADC_u16GetChannelReading(ADC_Channel_t copy_tChannel)
{
	/* 1- Select ADC Channel */
		ADMUX_REG &= 0xE0;
		ADMUX_REG |= copy_tChannel;
		
	/* 2- Start Conversion */
		SET_BIT(ADCSRA_REG, ADSC_BIT);
		while(GET_BIT(ADCSRA_REG, ADIF_BIT) == 0);
		
	/* 3- clear Flag*/
		SET_BIT(ADCSRA_REG, ADIF_BIT);
		
	/* 4- Return conversion result*/
		return ADCHL_REG;
}