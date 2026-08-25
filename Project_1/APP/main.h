/*
 * main.h
 *
 * Created: 7/30/2026 10:17:53 AM
 *  Author: Eltawel
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <util/delay.h>

#include "../Lib/STD_TYPES.h"
#include "../Lib/BIT_MATH.h"
#include "../Lib/VECTOR_TABLE.h"
#include "../MCAL/DIO/DIO_INterface.h"
#include "../HAL/LED/LED_INterface.h"
#include "../HAL/BTN/BTN_INterface.h"
#include "../MCAL/TIM0/TIM0_INterface.h"
#include "../HAL/LCD/LCD_Configuration.h"
#include "../HAL/LCD/LCD_INterface.h"
#include "../MCAL/UART/UART_INterface.h"
#include "../MCAL/UART/UART_REG.h"
#include "../MCAL/ADC/ADC_INterface.h"
#include "../MCAL/ADC/ADC_REG.h"
#include "../HAL/MAX485/MAX485_INterface.h"
#include "../HAL/MAX485/MAX485_CFG.h"
#include "../HAL/Relay/RELAY_INterface.h"
#include "../HAL/Relay/RELAY_CFG.h"
#include "../MODBUS/MODBUS_INterface.h"
#include "../MODBUS/MODBUS_CFG.h"

#endif /* MAIN_H_ */