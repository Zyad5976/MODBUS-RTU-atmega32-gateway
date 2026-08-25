/*
 * UART_INterface.h
 *
 * Created: 8/1/2026 6:51:31 PM
 *  Author: Eltawel
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/**
 * @brief  Initializes the UART module.
 * @details Configures Baud Rate (9600 bps @ 16MHz), Frame Format 
 *          (8 Data bits, 1 Stop bit, No Parity), and enables TX & RX circuits.
 * @param  None
 * @return None
 */
void UART_VoidInit(void);

/**
 * @brief  Transmits a single byte via UART.
 * @details Blocks execution until the Data Register Empty (UDRE) flag is set, 
 *          then loads the data into UDR.
 * @param  copy_u8data The 8-bit data/character to be transmitted.
 * @return None
 */
void UART_VoidSendData(u8 copy_u8data);

/**
 * @brief  Receives a single byte via UART.
 * @details Blocks execution until the Receive Complete (RXC) flag is set, 
 *          then reads and returns the byte from UDR.
 * @param  None
 * @return u8 The received 8-bit data/character.
 */
u8 UART_u8ReceiveData(void);

/**
 * @brief  Transmits a null-terminated string via UART.
 * @param  copy_pu8string Pointer to the constant string to be sent.
 * @return None
 */
void UART_VoidSendString(const u8 *copy_pu8string);

/**
 * @brief  Receives a fixed number of bytes into a memory buffer.
 * @details Useful for receiving structured protocol frames like Modbus RTU.
 * @param  copy_pu8buffer Pointer to the buffer array where incoming data will be stored.
 * @param  copy_u8size    The number of bytes expected to be received.
 * @return None
 */
void UART_VoidReceiveDataBuffer(u8 *copy_pu8buffer, u8 copy_u8size);

#endif /* UART_INTERFACE_H_ */