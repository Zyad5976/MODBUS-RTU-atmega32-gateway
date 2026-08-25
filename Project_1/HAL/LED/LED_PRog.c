/*
 * LED_PRog.c
 *
 * Created: 7/30/2026 7:14:42 PM
 *  Author: Eltawel
 */ 
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_INterface.h"
#include "LED_INterface.h"

void LED_VoidON(DIO_PORT_t copy_eport, DIO_PIN_t copy_epin)
{
	DIO_CFG_t Loc_LED = {
		.PORT = copy_eport,
		.PIN = copy_epin,
		.DIR = DIO_OUTPUT,
		.VAL = DIO_HIGH
	};
	
	DIO_voidSetPinDir(&Loc_LED);
	DIO_voidSetPinVal(&Loc_LED);
}

void LED_VoidOFF(DIO_PORT_t copy_eport, DIO_PIN_t copy_epin)
{
	DIO_CFG_t Loc_LED = {
		.PORT = copy_eport,
		.PIN = copy_epin,
		.DIR = DIO_OUTPUT,
		.VAL = DIO_LOW
	};
	
	DIO_voidSetPinDir(&Loc_LED);
	DIO_voidSetPinVal(&Loc_LED);
}

void LED_VoidToggle(DIO_PORT_t copy_eport, DIO_PIN_t copy_epin)
{
	DIO_CFG_t Loc_LED = {
		.PORT = copy_eport,
		.PIN = copy_epin,
		.DIR = DIO_OUTPUT
	};
	
	DIO_voidSetPinDir(&Loc_LED);
	DIO_voidTogglePin(&Loc_LED);
}