/*
 * BTN_INterface.h
 *
 * Created: 7/31/2026 11:07:32 AM
 *  Author: Eltawel
 */ 


#ifndef BTN_INTERFACE_H_
#define BTN_INTERFACE_H_

typedef enum{
	PULL_UP = 0,
	PULL_DOWN
}BTN_TYPE_t;

typedef enum{
	Is_Released = 0,
	Is_Pressed
}BTN_STATE_t;

/*
*@brief	Read the current State of Button (Pressed, Released)
*@param	copy_eport: elias from Enum DIO_PORT_t that contain Port(A, B, C, D) to Select the Port
*@param	copy_epin:  elias from Enum DIO_PIN_t that contain Pins(0, 1, 2, ..., 7) to Select the Pins
*@return	BTN_STATE_t: (Is_Released or Is_Pressed)
*/
BTN_STATE_t BTN_eState(DIO_PORT_t copy_eport, DIO_PIN_t copy_epin, BTN_TYPE_t copy_etype);

#endif /* BTN_INTERFACE_H_ */