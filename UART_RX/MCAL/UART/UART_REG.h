/*
 * UART_REG.h
 *
 * Created: 8/1/2026 6:51:15 PM
 *  Author: Eltawel
 */ 


#ifndef UART_REG_H_
#define UART_REG_H_

#define UDR_REG				*((volatile u8 *)0x2C)

#define UCSRA_REG			*((volatile u8 *)0x2B)

#define UCSRB_REG			*((volatile u8 *)0x2A)

#define UCSRC_REG			*((volatile u8 *)0x40)

#define UBRRL_REG			*((volatile u8 *)0x29)


/* UCSRA_REG Bits */
#define RXCOMPLETE_BIT				7
#define TXCOMPLETE_BIT				6
#define UDRE_BIT					5

/* UCSRB_REG Bits */
#define RX_ENABLE_BIT				4
#define TX_ENABLE_BIT				3

/* UCSRC_REG Bits */
#define REGISTER_SELECT_BIT			7
#define MODESELECT_BIT				6
#define STOP_BIT					3
#define USCZ1_BIT					2
#define USCZ0_BIT					1

#endif /* UART_REG_H_ */