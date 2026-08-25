/*
 * MODEBUS_INterface.h
 *
 * Created: 8/3/2026 11:25:43 AM
 *  Author: Eltawel
 */ 


#ifndef MODBUS_INTERFACE_H_
#define MODBUS_INTERFACE_H_

/**
 * @brief  Initializes the Modbus RTU engine and required communication hardware
 * @param  None
 * @return None
 */
void MODBUS_voidInit(void);

/**
 * @brief  Modbus Periodic Task / Handler
 *         Listens for incoming frames, validates CRC & Address, 
 *         and executes the requested function code (Relay / ADC)
 * @param  None
 * @return None
 */
void MODBUS_voidTask(void);

#endif /* MODEBUS_INTERFACE_H_ */