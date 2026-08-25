/*
 * RELAY_INterface.h
 *
 * Created: 8/2/2026 5:36:46 PM
 *  Author: Eltawel
 */ 


#ifndef RELAY_INTERFACE_H_
#define RELAY_INTERFACE_H_

/**
 * @brief  Initializes the Relay control pin as output and ensures initial state is OFF
 * @param  None
 * @return None
 */
void RELAY_VoidInit(void);

/**
 * @brief  Activates the Relay (Outputs HIGH to the relay control pin)
 * @param  None
 * @return None
 */
void RELAY_VoidTurnON(void);

/**
 * @brief  Deactivates the Relay (Outputs LOW to the relay control pin)
 * @param  None
 * @return None
 */
void RELAY_VoidTurnOFF(void);

#endif /* RELAY_INTERFACE_H_ */