/*
 * UART_PRog.c
 *
 * Created: 8/1/2026 6:52:24 PM
 *  Author: Eltawel
 */ 
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "UART_INterface.h"
#include "UART_REG.h"

void UART_VoidInit(void)
{	
	/* 1- Select Boud Rate */
		UBRRL_REG = 103;
		
	/* 2- RX & TX Enable */
		SET_BIT(UCSRB_REG, RX_ENABLE_BIT);
		SET_BIT(UCSRB_REG, TX_ENABLE_BIT);
		
	/* 3- Register Select & Character Size Select */
		UCSRC_REG = (1 << REGISTER_SELECT_BIT) | (1 << USCZ1_BIT) | (1 << USCZ0_BIT);
}

void UART_VoidSendData(u8 copy_u8data)
{	
	while(GET_BIT(UCSRA_REG, UDRE_BIT) == 0);
	
	UDR_REG = copy_u8data;
}

u8 UART_u8ReceiveData(void)
{
	while(GET_BIT(UCSRA_REG, RXCOMPLETE_BIT) == 0);
	
	return UDR_REG;
}

void UART_VoidSendString(const u8 *copy_pu8string)
{	
	if(copy_pu8string != NUL)
	{
		while(*copy_pu8string != nul)
		{
			UART_VoidSendData(*copy_pu8string);
			copy_pu8string++;
		}
	}
}

void UART_VoidReceiveDataBuffer(u8 *copy_pu8buffer, u8 copy_u8size)
{
	u8 Loc_counter = 0;
	
	if(copy_pu8buffer != NUL)
	{
		for(Loc_counter = 0; Loc_counter < copy_u8size; Loc_counter++)
		{
			*copy_pu8buffer = UART_u8ReceiveData();
			copy_pu8buffer++;
		}
	}
}