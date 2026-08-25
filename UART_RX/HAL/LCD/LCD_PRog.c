/*
 * LCD_PRog.c
 *
 * Created: 8/1/2026 2:35:01 AM
 *  Author: Eltawel
 */ 
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_INterface.h"
#include "../../MCAL/TIM0/TIM0_INterface.h"
#include "LCD_Configuration.h"
#include "LCD_INterface.h"

#define NUMBER_OF_LCD_PINS				4

static void LCD_VoidHalfSendData(u8 copy_u8Hdata)
{
	u8 Loc_LCD_PINS[NUMBER_OF_LCD_PINS] = {LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN};
	u8 Loc_counter = 0;
	
	DIO_CFG_t Loc_StructPinCFG;
	Loc_StructPinCFG.PORT = LCD_DPORT;
		
	for(Loc_counter = 0; Loc_counter < NUMBER_OF_LCD_PINS; Loc_counter++)
	{
		Loc_StructPinCFG.PIN = Loc_LCD_PINS[Loc_counter];
		
		Loc_StructPinCFG.VAL = (copy_u8Hdata >> Loc_counter) & 0x01;
		
		DIO_voidSetPinVal(&Loc_StructPinCFG);
	}
}

void LCD_VoidSendEnablePulse()
{	
	DIO_CFG_t Loc_LCD_SendEnablePulse;
	Loc_LCD_SendEnablePulse.PORT = LCD_CPORT;
	Loc_LCD_SendEnablePulse.PIN = LCD_E_PIN;
	
	Loc_LCD_SendEnablePulse.VAL = DIO_HIGH;
	DIO_voidSetPinVal(&Loc_LCD_SendEnablePulse);
	
	TIM0_VoidDelayMs(2);
	
	Loc_LCD_SendEnablePulse.VAL = DIO_LOW;
	DIO_voidSetPinVal(&Loc_LCD_SendEnablePulse);
	
	TIM0_VoidDelayMs(2);
}

void LCD_VoidInit(void)
{
	/* 1- Directions of LCD_CPORT & LCD_DPORT */
		DIO_VoidSetPortDir(LCD_CPORT, 0x03);
		DIO_VoidSetPortDir(LCD_DPORT, 0xF0);
		
	/* 2- Wait More Then 30ms */
		TIM0_VoidDelayMs(40);
		
	/* 3- Send Commands */
		/* 1- Function Set */
			LCD_VoidHalfSendData(0x02);
			LCD_VoidSendEnablePulse();
			
			LCD_VoidHalfSendData(0x02);
			LCD_VoidSendEnablePulse();
			
			LCD_VoidHalfSendData(0x08);
			LCD_VoidSendEnablePulse();
			
		/* 2- Display Control */
			LCD_VoidSendCommand(0x0C);
			
		/* 3- CLear Control */
			LCD_VoidClear();
}

void LCD_VoidSendCommand(u8 copy_u8command)
{
	DIO_CFG_t Loc_LCD_SendCommand;
	Loc_LCD_SendCommand.PORT = LCD_CPORT;
	Loc_LCD_SendCommand.PIN = LCD_RS_PIN;
	Loc_LCD_SendCommand.VAL = DIO_LOW;
	
	DIO_voidSetPinVal(&Loc_LCD_SendCommand);
	
	LCD_VoidHalfSendData(copy_u8command >> 4);
	LCD_VoidSendEnablePulse();
	
	LCD_VoidHalfSendData(copy_u8command);
	LCD_VoidSendEnablePulse();
}

void LCD_VoidSendData(u8 copy_u8data)
{
	DIO_CFG_t Loc_LCD_SendCommand;
	Loc_LCD_SendCommand.PORT = LCD_CPORT;
	Loc_LCD_SendCommand.PIN = LCD_RS_PIN;
	Loc_LCD_SendCommand.VAL = DIO_HIGH;
	
	DIO_voidSetPinVal(&Loc_LCD_SendCommand);
	
	LCD_VoidHalfSendData(copy_u8data >> 4);
	LCD_VoidSendEnablePulse();
	
	LCD_VoidHalfSendData(copy_u8data);
	LCD_VoidSendEnablePulse();
}

void LCD_VoidClear(void)
{
	LCD_VoidSendCommand(0x01);
	TIM0_VoidDelayMs(2);
}

void LCD_VoidSendString(const u8 *copy_pu8str)
{
	u8 Loc_Counter = 0;
	
	while(copy_pu8str[Loc_Counter] != nul)
	{
		LCD_VoidSendData(copy_pu8str[Loc_Counter]);
		Loc_Counter++;
	}
}


void LCD_VoidGotoXY(u8 copy_u8x, u8 copy_u8y)
{
	u8 Loc_u8DDRAMAdress = (copy_u8x + (copy_u8y * 0x40));
	
	SET_BIT(Loc_u8DDRAMAdress, 7);
	
	LCD_VoidSendCommand(Loc_u8DDRAMAdress);
}

void LCD_VoidDrawPosition(u8 *copy_u8array, u8 copy_u8pattern, u8 copy_u8x, u8 copy_u8y)
{
	u8 Loc_CGRAMAdress = copy_u8pattern * 8;
	u8 Loc_counter = 0;
	
	CLEAR_BIT(Loc_CGRAMAdress, 7);
	SET_BIT(Loc_CGRAMAdress, 6);
	
	LCD_VoidSendCommand(Loc_CGRAMAdress);
	
	for(Loc_counter = 0; Loc_counter < 8; Loc_counter++)
	{
		LCD_VoidSendData(copy_u8array[Loc_counter]);
	}
	
	LCD_VoidGotoXY(copy_u8x, copy_u8y);
	LCD_VoidSendData(copy_u8pattern);
}

void LCD_VoidSendNum(u32 copy_u32num)
{
	s8 Loc_Counter = 0;
	u8 Loc_Arr[10];
	
	if(copy_u32num == 0)
	{
		LCD_VoidSendData('0');
		return;
	}
	
	for(Loc_Counter = 0; copy_u32num != 0; Loc_Counter++)
	{
		Loc_Arr[Loc_Counter] = copy_u32num % 10 + 48;
		copy_u32num /= 10;
	}
	Loc_Counter--;
	while(Loc_Counter >= 0)
	{
		LCD_VoidSendData(Loc_Arr[Loc_Counter]);
		Loc_Counter--;
	}
}
