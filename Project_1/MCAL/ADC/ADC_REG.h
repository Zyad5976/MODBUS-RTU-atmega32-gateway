/*
 * ADC_REG.h
 *
 * Created: 8/2/2026 2:14:28 AM
 *  Author: Eltawel
 */ 


#ifndef ADC_REG_H_
#define ADC_REG_H_

#define ADMUX_REG				*((volatile u8 *)0x27)

#define ADCSRA_REG				*((volatile u8 *)0x26)

#define ADCH_REG                *((volatile u8 *)0x25)

#define ADCHL_REG				*((volatile u16 *)0x24)		/* ADCL + ADCH */

#define ADCL_REG				*((volatile u8 *)0x24)

#define SFIOR_REG				*((volatile u8 *)0x50)


/* ADMUX_REG Bits */
#define REFS1_BIT               7
#define REFS0_BIT               6
#define ADLAR_BIT               5
#define MUX4_BIT                4
#define MUX3_BIT                3
#define MUX2_BIT                2
#define MUX1_BIT                1
#define MUX0_BIT                0

/* ADCSRA_REG Bits */
#define ADEN_BIT                7
#define ADSC_BIT                6
#define ADATE_BIT               5
#define ADIF_BIT                4
#define ADIE_BIT                3
#define ADPS2_BIT               2
#define ADPS1_BIT               1
#define ADPS0_BIT               0

#endif /* ADC_REG_H_ */