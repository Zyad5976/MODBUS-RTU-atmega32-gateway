/*
 * TIM0_PRog.c
 *
 * Created: 7/31/2026 12:39:47 PM
 *  Author: Eltawel
 */ 
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "TIM0_INterface.h"
#include "TIM0_REG.h"

void TIM0_VoidInit(void)
{
	/* 1- Waveform Generation Mode ==> CTC Mode */
		CLEAR_BIT(TCCR0_REG, WGM00_BIT);
		SET_BIT(TCCR0_REG, WGM01_BIT);
		
	/* 2- Compare Output Mode ==> OC0 disconnected */
		CLEAR_BIT(TCCR0_REG, COM00_BIT);
		CLEAR_BIT(TCCR0_REG, COM01_BIT);
		
	/* OCR0 Val */
		OCR0_REG = 250;
		
	/* 3- Set Prescaler */
		TCCR0_REG = (TCCR0_REG & 0xF8) | TIM0_CLK_64;
}

void TIM0_VoidDelayMs(u32 copy_u32delayms)
{
	u32 Loc_Counter = 0;
	
	for(Loc_Counter = 0; Loc_Counter < copy_u32delayms; Loc_Counter++)
	{
		while(GET_BIT(TIFR_REG, OCF0_BIT) == 0);
		
		SET_BIT(TIFR_REG, OCF0_BIT);
	}
}