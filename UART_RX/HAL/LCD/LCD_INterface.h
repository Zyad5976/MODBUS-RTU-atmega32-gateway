/*
 * LCD_INterface.h
 *
 * Created: 8/1/2026 2:34:11 AM
 *  Author: Eltawel
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/*
 *@brief		initialize LCD in 4-bit mode
 *@param		None
 *@return	None
*/
void LCD_VoidInit(void);

/*
*@brief		Send Control Command to LCD
*@param		copy_u8command: The command type to be sent
*@return	None
*/
void LCD_VoidSendCommand(u8 copy_u8command);

/*
 *@brief		Sends a single ASCII character to be displayed on the LCD
 *@param		copy_u8data: The character ASCII code to display
 *@return	None
*/
void LCD_VoidSendData(u8 copy_u8data);

/*
 *@brief		Clear all displayed on LCD
 *@param		None
 *@return	None
*/
void LCD_VoidClear(void);

/*
 *@brief		Displays a string on the LCD
 *@param		copy_pu8str: Pointer to the constant character array
 *@return	None
 *@note		Ensure the passed pointer is not NULL before calling
*/
void LCD_VoidSendString(const u8 *copy_pu8str);

/**
 * @brief  Moves the LCD cursor to a specific Row (X) and Column (Y).
 * @param  copy_u8x: Row position (0 for 1st Row, 1 for 2nd Row).
 * @param  copy_u8y: Column position (0 to 15).
 * @return None
 */
void LCD_VoidGotoXY(u8 copy_u8x, u8 copy_u8y);

/**
 * @brief  Stores a custom pattern in CGRAM and draws it at a specific screen position.
 * @param  copy_u8array: Pointer to the 8-byte array representing the custom pattern.
 * @param  copy_u8position: CGRAM pattern location index (0 to 7).
 * @param  copy_u8x: Target Row position (0 or 1).
 * @param  copy_u8y: Target Column position (0 to 15).
 * @return None
 */
void LCD_VoidDrawPosition(u8 *copy_u8array, u8 copy_u8pattern, u8 copy_u8x, u8 copy_u8y);

/**
 * @brief  Converts and displays a signed 32-bit integer number on the screen.
 * @param  copy_u32num: The unsigned integer number to display.
 * @return None
 */
void LCD_VoidSendNum(u32 copy_u32num);


#endif /* LCD_INTERFACE_H_ */