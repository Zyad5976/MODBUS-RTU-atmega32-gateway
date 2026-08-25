/*
 * DIO_PRog.c
 *
 * Created: 7/30/2026 2:14:01 PM
 *  Author: Eltawel
 */ 

#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "DIO_INterface.h"
#include "DIO_REG.h"

/* PIN FUNSTIONS */
void DIO_voidSetPinDir(const DIO_CFG_t *obj_1)
{
	if(obj_1 != NUL)
	{
		switch(obj_1->PORT)
		{
			case DIO_PORTA:
				if(obj_1->DIR == DIO_OUTPUT)
				{
					SET_BIT(DDRA_REG, obj_1->PIN);
				}
				else if(obj_1->DIR == DIO_INPUT)
				{
					CLEAR_BIT(DDRA_REG, obj_1->PIN);
				}
				break;
			case DIO_PORTB:
				if(obj_1->DIR == DIO_OUTPUT)
				{
					SET_BIT(DDRB_REG, obj_1->PIN);
				}
				else if(obj_1->DIR == DIO_INPUT)
				{
					CLEAR_BIT(DDRB_REG, obj_1->PIN);
				}
				break;
			case DIO_PORTC:
				if(obj_1->DIR == DIO_OUTPUT)
				{
					SET_BIT(DDRC_REG, obj_1->PIN);
				}
				else if(obj_1->DIR == DIO_INPUT)
				{
					CLEAR_BIT(DDRC_REG, obj_1->PIN);
				}
				break;
			case DIO_PORTD:
			if(obj_1->DIR == DIO_OUTPUT)
			{
				SET_BIT(DDRD_REG, obj_1->PIN);
			}
			else if(obj_1->DIR == DIO_INPUT)
			{
				CLEAR_BIT(DDRD_REG, obj_1->PIN);
			}
			break;
		}
	}
	else
	{
		/* Pointer is NULL: Do Nothing */	
	}
}
void DIO_voidSetPinVal(const DIO_CFG_t *obj_1)
{
	if(obj_1 != NUL)
	{
		switch(obj_1->PORT)
		{
			case DIO_PORTA:
				if(obj_1->VAL == DIO_HIGH)
				{
					SET_BIT(PORTA_REG, obj_1->PIN);
				}
				else if(obj_1->VAL == DIO_LOW)
				{
					CLEAR_BIT(PORTA_REG, obj_1->PIN);
				}
				break;
			case DIO_PORTB:
				if(obj_1->VAL == DIO_HIGH)
				{
					SET_BIT(PORTB_REG, obj_1->PIN);
				}
				else if(obj_1->VAL == DIO_LOW)
				{
					CLEAR_BIT(PORTB_REG, obj_1->PIN);
				}
				break;
			case DIO_PORTC:
				if(obj_1->VAL == DIO_HIGH)
				{
					SET_BIT(PORTC_REG, obj_1->PIN);
				}
				else if(obj_1->VAL == DIO_LOW)
				{
					CLEAR_BIT(PORTC_REG, obj_1->PIN);
				}
				break;
			case DIO_PORTD:
				if(obj_1->VAL == DIO_HIGH)
				{
					SET_BIT(PORTD_REG, obj_1->PIN);
				}
				else if(obj_1->VAL == DIO_LOW)
				{
					CLEAR_BIT(PORTD_REG, obj_1->PIN);
				}
				break;
		}
	}
	else
	{
		/* Pointer is NULL: Do Nothing */	
	}
}
void DIO_voidTogglePin(const DIO_CFG_t *obj_1)
{
	if(obj_1 != NUL)
	{
		switch(obj_1->PORT)
		{
			case DIO_PORTA:
				TOGGLE_BIT(PORTA_REG, obj_1->PIN);
				break;
			case DIO_PORTB:
				TOGGLE_BIT(PORTB_REG, obj_1->PIN);
				break;
			case DIO_PORTC:
				TOGGLE_BIT(PORTC_REG, obj_1->PIN);
				break;
			case DIO_PORTD:
				TOGGLE_BIT(PORTD_REG, obj_1->PIN);
				break;
		}
	}
	else
	{
		/* Pointer is NULL: Do Nothing */	
	}
}
DIO_VAL_t DIO_eReadPinVal(const DIO_CFG_t *obj_1)
{
	DIO_VAL_t Loc_val = 0;
	
	if(obj_1 != NUL)
	{
		switch(obj_1->PORT)
		{
			case DIO_PORTA: Loc_val = GET_BIT(PINA_REG, obj_1->PIN); break;
			case DIO_PORTB: Loc_val = GET_BIT(PINB_REG, obj_1->PIN); break;
			case DIO_PORTC: Loc_val = GET_BIT(PINC_REG, obj_1->PIN); break;
			case DIO_PORTD: Loc_val = GET_BIT(PIND_REG, obj_1->PIN); break;
		}
	}
	else
	{
		/* Pointer is NULL: Do Nothing */
	}
	
	return Loc_val;
}

/* PORT FUNCTIONS */
void DIO_VoidSetPortDir(DIO_PORT_t copy_eport, u8 copy_u8dir)
{
	switch(copy_eport)
	{
		case DIO_PORTA: DDRA_REG = copy_u8dir; break;
		case DIO_PORTB: DDRB_REG = copy_u8dir; break;
		case DIO_PORTC: DDRC_REG = copy_u8dir; break;
		case DIO_PORTD: DDRD_REG = copy_u8dir; break;
	}
}
void DIO_VoidSetPortVal(DIO_PORT_t copy_eport, u8 copy_u8val)
{
	switch(copy_eport)
	{
		case DIO_PORTA: PORTA_REG = copy_u8val; break;
		case DIO_PORTB: PORTB_REG = copy_u8val; break;
		case DIO_PORTC: PORTC_REG = copy_u8val; break;
		case DIO_PORTD: PORTD_REG = copy_u8val; break;
	}	
}