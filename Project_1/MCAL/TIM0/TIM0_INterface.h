/*
 * TIM0_INterface.h
 *
 * Created: 7/31/2026 12:39:36 PM
 *  Author: Eltawel
 */ 


#ifndef TIM0_INTERFACE_H_
#define TIM0_INTERFACE_H_

typedef enum{
	NORMAL = 0,
	PWM_PHASECORRECT,
	CTC,
	FAST_PWM
}TIM0_WGM_t;

typedef enum{
	TIM0_NO_CLK_SOURCE = 0,
	TIM0_NO_PRESCALING,
	TIM0_CLK_8,
	TIM0_CLK_64,
	TIM0_CLK_256,
	TIM0_CLK_1024
}TIM0_PRESCALER_t;

typedef enum{
	OC0_DISCONNECTED = 0,
	TOGGLE_OC0,
	CLEAR_OC0,
	SET_OC0
}TIM0_COM_NON_PWM_t;


/**
*@brief		Initializes Timer0 in CTC Mode with Prescaler 64 for 1ms timing tick
*@param		None
*@return	None
*/
void TIM0_VoidInit(void);

/**
*@brief		Generates a synchronous (blocking) delay in milliseconds using Timer0 CTC Mode
*@param		copy_u32delayms: Desired delay time in milliseconds
*@return	None
*/
void TIM0_VoidDelayMs(u32 copy_u32delayms);

#endif /* TIM0_INTERFACE_H_ */