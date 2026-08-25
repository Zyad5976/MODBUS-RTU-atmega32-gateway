/*
 * BTN_PRog.c
 *
 * Created: 7/31/2026 11:07:49 AM
 *  Author: Eltawel
 */ 
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_INterface.h"
#include "BTN_INterface.h"

BTN_STATE_t BTN_eState(DIO_PORT_t copy_eport, DIO_PIN_t copy_epin, BTN_TYPE_t copy_etype)
{
	BTN_STATE_t Loc_estate = Is_Released;
	
	DIO_CFG_t Loc_BTN = {
		.PORT = copy_eport,
		.PIN = copy_epin,
		.DIR = DIO_INPUT
	};
	
	DIO_voidSetPinDir(&Loc_BTN);
	
	if(copy_etype == PULL_UP)
	{
		if(DIO_eReadPinVal(&Loc_BTN) == DIO_LOW)
		{
			while(DIO_eReadPinVal(&Loc_BTN) == DIO_LOW);
			Loc_estate = Is_Pressed;
		}
	}
	
	else if(copy_etype == PULL_DOWN)
	{
		if(DIO_eReadPinVal(&Loc_BTN) == DIO_HIGH)
		{
			while(DIO_eReadPinVal(&Loc_BTN) == DIO_HIGH);
			Loc_estate = Is_Pressed;
		}
	}
	
	return Loc_estate;
	
}