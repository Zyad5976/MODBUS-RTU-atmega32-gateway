/*
 * DIO_INterface.h
 *
 * Created: 7/30/2026 2:13:45 PM
 *  Author: Eltawel
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/* DIO DIRECTION */
typedef enum{
	DIO_INPUT = 0,
	DIO_OUTPUT
}DIO_DIR_t;

/* DIO VALUE */
typedef enum{
	DIO_LOW = 0,
	DIO_HIGH
}DIO_VAL_t;

/* DIO PORTS */
typedef enum{
	DIO_PORTA = 0,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD
}DIO_PORT_t;

/* DIO PINS */
typedef enum{
	DIO_PIN0 = 0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
}DIO_PIN_t;

/* DIO CFG */
typedef struct{
	DIO_PORT_t PORT;
	DIO_PIN_t PIN;
	DIO_DIR_t DIR;
	DIO_VAL_t VAL;
}DIO_CFG_t;

/* PIN FUNSTIONS */

/**
*@brief		Select the direction(Input, Output) for a specific GPIO Pin
*@param		obj_1: Pointer to the DIO Configuration Structure Containig Port, Pin, Dir and Val
*@return	None
*@note		Ensure the pointer not equal NULL before calling
*/
void DIO_voidSetPinDir(const DIO_CFG_t *obj_1);

/**
*@brief		Select the Value(Low, High) for a specific GPIO Pin
*@param		obj_1: Pointer to the DIO Configuration Structure Containig Port, Pin, Dir and Val
*@return	None
*@note		Ensure the pointer not equal NULL before calling
*/
void DIO_voidSetPinVal(const DIO_CFG_t *obj_1);

/**
*@brief		Toggle the Value(Low, High) for a specific GPIO Pin
*@param		obj_1: Pointer to the DIO Configuration Structure Containig Port, Pin, Dir and Val
*@return	None
*@note		Ensure the pointer not equal NULL before calling
*/
void DIO_voidTogglePin(const DIO_CFG_t *obj_1);

/**
*@brief		Read the Value(Low, High) for a specific GPIO Pin
*@param		obj_1: Pointer to the DIO Configuration Structure Containig Port, Pin, Dir and Val
*@return	DIO_VAL_t: is a Enum that containig Low, High
*@note		Ensure the pointer not equal NULL before calling
*/
DIO_VAL_t DIO_eReadPinVal(const DIO_CFG_t *obj_1);

/* PORT FUNCTIONS */

/**
*@brief		Select the Direction(Input, Output) for a specific GPIO Port
*@param		copy_eport: Target GPIO Port(PORT_A, PORT_B, PORT_C, PORT_D)
*@param		copy_u8dir: 8-bit value to be written on the port
*@return	None
*/
void DIO_VoidSetPortDir(DIO_PORT_t copy_eport, u8 copy_u8dir);

/**
*@brief		Select the Value(Low, High) for a specific GPIO Port
*@param		copy_eport: Target GPIO Port(PORT_A, PORT_B, PORT_C, PORT_D)
*@param		copy_u8dir: 8-bit direction value
*@return	None
*/
void DIO_VoidSetPortVal(DIO_PORT_t copy_eport, u8 copy_u8val);

#endif /* DIO_INTERFACE_H_ */