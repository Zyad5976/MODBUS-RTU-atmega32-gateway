/*
 * DIO_REG.h
 *
 * Created: 7/30/2026 2:13:30 PM
 *  Author: Eltawel
 */ 


#ifndef DIO_REG_H_
#define DIO_REG_H_

/* PORTA */
#define PORTA_REG					*((volatile u8 *)0x3B)
#define DDRA_REG					*((volatile u8 *)0x3A)
#define PINA_REG					*((volatile u8 *)0x39)

/* PORTB */
#define PORTB_REG					*((volatile u8 *)0x38)
#define DDRB_REG					*((volatile u8 *)0x37)
#define PINB_REG					*((volatile u8 *)0x36)

/* PORTC */
#define PORTC_REG					*((volatile u8 *)0x35)
#define DDRC_REG					*((volatile u8 *)0x34)
#define PINC_REG					*((volatile u8 *)0x33)

/* PORTD */
#define PORTD_REG					*((volatile u8 *)0x32)
#define DDRD_REG					*((volatile u8 *)0x31)
#define PIND_REG					*((volatile u8 *)0x30)


#endif /* DIO_REG_H_ */