/*
 * LCD_Configuration.h
 *
 * Created: 8/1/2026 2:34:32 AM
 *  Author: Eltawel
 */ 


#ifndef LCD_CONFIGURATION_H_
#define LCD_CONFIGURATION_H_

/* LCD Control Port */
#define LCD_CPORT				DIO_PORTB

/* LCD Control Pins */
#define LCD_RS_PIN				DIO_PIN1
#define LCD_E_PIN				DIO_PIN0

/* LCD Data Port */
#define LCD_DPORT				DIO_PORTA

/* LCD Data Pins */
#define LCD_D4_PIN				DIO_PIN4
#define LCD_D5_PIN				DIO_PIN5
#define LCD_D6_PIN				DIO_PIN6
#define LCD_D7_PIN				DIO_PIN7

#endif /* LCD_CONFIGURATION_H_ */