/*
 * TIM0_REG.h
 *
 * Created: 7/31/2026 12:39:21 PM
 *  Author: Eltawel
 */ 


#ifndef TIM0_REG_H_
#define TIM0_REG_H_

#define TCCR0_REG						*((volatile u8 *)0x53)
#define TCNT0_REG						*((volatile u8 *)0x52)
#define OCR0_REG						*((volatile u8 *)0x5C)
#define TIMSK_REG						*((volatile u8 *)0x59)
#define TIFR_REG						*((volatile u8 *)0x58)

/* TCCR0_REG Bits  */

	/* 1- Force Output Compare */
		#define FOC0_BIT			7
	
	/* 2- Waveform Generation Mode */
		#define WGM00_BIT			6
		#define WGM01_BIT			3
	
	/* 3- Compare Match Output Mode */
		#define COM01_BIT			5
		#define COM00_BIT			4
		
	/* 4- Select Prescaler */
		#define CS02_BIT			2
		#define CS01_BIT			1
		#define CS00_BIT			0
		
/* TIMSK_REG Bits  */

	/* 1- Output Compare Match Interrupt Enable */
		#define OCIE0_BIT			1
		
/* TIFR_REG Bits  */

	/* 1- Output Compare Flag */
		#define OCF0_BIT			1


#endif /* TIM0_REG_H_ */