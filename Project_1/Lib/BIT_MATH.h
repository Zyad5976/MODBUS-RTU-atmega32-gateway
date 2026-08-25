/*
 * BIT_MATH.h
 *
 * Created: 7/30/2026 10:18:58 AM
 *  Author: Eltawel
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define BIT_MASK							1

#define SET_BIT(REG,BIT)					((REG) |= (BIT_MASK << (BIT)))
#define CLEAR_BIT(REG,BIT)					((REG) &= ~(BIT_MASK << (BIT)))
#define TOGGLE_BIT(REG,BIT)					((REG) ^= (BIT_MASK << (BIT)))
#define GET_BIT(REG,BIT)					(((REG) >> (BIT)) & BIT_MASK)

#endif /* BIT_MATH_H_ */