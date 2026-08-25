/*
 * RELAY_PRog.c
 *
 * Created: 8/2/2026 5:37:10 PM
 *  Author: Eltawel
 */ 
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_INterface.h"
#include "RELAY_INterface.h"
#include "RELAY_CFG.h"

void RELAY_VoidInit(void)
{
	DIO_CFG_t Loc_Relay = {
		.PORT = RELAY_PORT,
		.PIN = RELAY_PIN,
		.DIR = DIO_OUTPUT,
		.VAL = DIO_LOW
	};
	
	DIO_voidSetPinDir(&Loc_Relay);
	DIO_voidSetPinVal(&Loc_Relay);
}

void RELAY_VoidTurnON(void)
{
	DIO_CFG_t Loc_Relay = {
		.PORT = RELAY_PORT,
		.PIN = RELAY_PIN,
		.VAL = DIO_HIGH
	};
	
	DIO_voidSetPinVal(&Loc_Relay);
}

void RELAY_VoidTurnOFF(void)
{
	DIO_CFG_t Loc_Relay = {
		.PORT = RELAY_PORT,
		.PIN = RELAY_PIN,
		.VAL = DIO_LOW
	};
	
	DIO_voidSetPinVal(&Loc_Relay);
}