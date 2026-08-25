/*
 * Project_1.c
 *
 * Created: 7/30/2026 10:07:38 AM
 * Author : Eltawel
 */ 

/************************************************************************/
/*	                              UART_RX                               */
/************************************************************************/

#include "main.h"


int main(void)
{
	u8 loc_u8ReceivedData = 0;
	
	UART_VoidInit();
	TIM0_VoidInit();
	LCD_VoidInit();
	
    while (1) 
    {
		loc_u8ReceivedData = UART_u8ReceiveData();
		
		if(loc_u8ReceivedData == 'A')
		{
			LED_VoidON(DIO_PORTC, DIO_PIN0);
			
			LCD_VoidGotoXY(0,0);
			LCD_VoidSendString((const u8 *)"receive data....");
			LCD_VoidGotoXY(1,1);
			LCD_VoidSendData('A');
		}
		else
		{
			LED_VoidOFF(DIO_PORTC, DIO_PIN0);
		}
    }
}

