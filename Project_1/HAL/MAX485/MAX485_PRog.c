/*
 * MAX485_PRog.c
 *
 * Created: 8/2/2026 3:53:36 PM
 *  Author: Eltawel
 */ 
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_INterface.h"
#include "../../MCAL/UART/UART_INterface.h"
#include "MAX485_INterface.h"
#include "MAX485_CFG.h"

void MAX485_VoidInit(void)
{
	DIO_CFG_t Loc_MAX = {
		.PORT = MAX485_PORT,
		.PIN = MAX485_ENABLE,
		.DIR = DIO_OUTPUT,
		.VAL = DIO_LOW
	};
	
	DIO_voidSetPinDir(&Loc_MAX);
	DIO_voidSetPinVal(&Loc_MAX);
	
}

void MAX485_VoidSendByte(u8 copy_u8data)
{
	DIO_CFG_t Loc_MAX; 
	
	Loc_MAX.PORT = MAX485_PORT;
	Loc_MAX.PIN = MAX485_ENABLE;
	Loc_MAX.DIR = DIO_OUTPUT;
	
	Loc_MAX.VAL = DIO_HIGH;
	
	DIO_voidSetPinVal(&Loc_MAX);
	
	UART_VoidSendData(copy_u8data);
	
	Loc_MAX.VAL = DIO_LOW;
	DIO_voidSetPinVal(&Loc_MAX);
}

void MAX485_VoidReceiveData(u8 *copy_pu8data)
{
	DIO_CFG_t Loc_MAX = {
		.PORT = MAX485_PORT,
		.PIN = MAX485_ENABLE,
		.DIR = DIO_OUTPUT,
		.VAL = DIO_LOW
	};
	
	DIO_voidSetPinVal(&Loc_MAX);
	
	*copy_pu8data = UART_u8ReceiveData();	
}