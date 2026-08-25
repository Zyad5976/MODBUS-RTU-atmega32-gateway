/*
 * MAX485_INterface.h
 *
 * Created: 8/2/2026 3:53:20 PM
 *  Author: Eltawel
 */ 


#ifndef MAX485_INTERFACE_H_
#define MAX485_INTERFACE_H_

/**
 * @brief  Initializes MAX485 Hardware & Underlying UART Peripheral
 * @param  None
 * @return None
 */
void MAX485_VoidInit(void);

/**
 * @brief  Sends a single byte over RS485 network
 * @param copy_u8Data Byte to be sent over RS485
 * @return None
 */
void MAX485_VoidSendByte(u8 copy_u8data);

/**
 * @brief  Receives a single byte over RS485 network (Blocking).
 * @param copy_pu8Data Pointer to store the received byte.
 * @return None
 */
void MAX485_VoidReceiveData(u8 *copy_pu8data);

#endif /* MAX485_INTERFACE_H_ */