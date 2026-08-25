/*
 * LED_INterface.h
 *
 * Created: 7/30/2026 7:14:30 PM
 *  Author: Eltawel
 */ 


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/*
*@brief	Make LED ON
*@param	copy_eport: elias from Enum DIO_PORT_t that contain Port(A, B, C, D) to Select the Port
*@param	copy_epin:  elias from Enum DIO_PIN_t that contain Pins(0, 1, 2, ..., 7) to Select the Pins
*@return	none
*/
void LED_VoidON(DIO_PORT_t copy_eport, DIO_PIN_t copy_epin);

/*
*@brief	Make LED OFF
*@param	copy_eport: elias from Enum DIO_PORT_t that contain Port(A, B, C, D) to Select the Port
*@param	copy_epin:  elias from Enum DIO_PIN_t that contain Pins(0, 1, 2, ..., 7) to Select the Pins
*@return	none
*/
void LED_VoidOFF(DIO_PORT_t copy_eport, DIO_PIN_t copy_epin);

/*
*@brief	Make LED Toggle
*@param	copy_eport: elias from Enum DIO_PORT_t that contain Port(A, B, C, D) to Select the Port
*@param	copy_epin:  elias from Enum DIO_PIN_t that contain Pins(0, 1, 2, ..., 7) to Select the Pins
*@return	none
*/
void LED_VoidToggle(DIO_PORT_t copy_eport, DIO_PIN_t copy_epin);


#endif /* LED_INTERFACE_H_ */