/*
 * Project_1.c
 *
 * Created: 7/30/2026 10:07:38 AM
 * Author : Eltawel
 */ 

#include "main.h"

static u8 Loc_MotorState = 0;

#if MODBUS_MODE == MODBUS_HOLDING_REG_MODE
    u8 Loc_TempThreshold = 35;
#endif

int main(void)
{
    u16 loc_AdcVal = 0;
    u16 loc_Temp = 0;
    
    TIM0_VoidInit();
    ADC_VoidInit();
    LCD_VoidInit();
    UART_VoidInit();
    MODBUS_voidInit();
    
    LCD_VoidGotoXY(0, 0);
    LCD_VoidSendString((const u8*)"Modbus Gateway");
    LCD_VoidGotoXY(1, 1);
    LCD_VoidSendString((const u8*)"System Ready...");
    TIM0_VoidDelayMs(1000);
    LCD_VoidClear();
    
    while (1) 
    {
        u8 loc_u8Key = 0;

        loc_AdcVal = ADC_u16GetChannelReading(ADC2);
        loc_Temp = (u16)(((u32)loc_AdcVal * 500) / 1024);
        
        LCD_VoidGotoXY(0, 0);
        LCD_VoidSendString((const u8*)"Temp: ");
        LCD_VoidSendNum(loc_Temp);
        LCD_VoidSendString((const u8*)" C    ");
        
#if MODBUS_MODE == MODBUS_INPUT_REG_MODE
        if (loc_Temp >= 35)
#elif MODBUS_MODE == MODBUS_HOLDING_REG_MODE
        if (loc_Temp >= Loc_TempThreshold)
#endif
        {
            RELAY_VoidTurnON();
            if (Loc_MotorState == 0)
            {
                Loc_MotorState = 1;
                LCD_VoidGotoXY(1, 5);
                LCD_VoidSendString((const u8*)"Motor: RUNNING");
            }
        }
        else
        {
            RELAY_VoidTurnOFF();
            if (Loc_MotorState == 1)
            {
                Loc_MotorState = 0;
                LCD_VoidGotoXY(1, 5);
                LCD_VoidSendString((const u8*)"Motor: STOPPED");
            }
        }

        if (UART_u8ReceiveNoBlock(&loc_u8Key) == 1)
        {
#if MODBUS_MODE == MODBUS_INPUT_REG_MODE

            UART_VoidSendData(0x01);             // Slave ID
            UART_VoidSendData(0x04);             // Function Code 0x04
            UART_VoidSendData(0x02);             // Byte Count
            UART_VoidSendData(0x00);             // High Byte
            UART_VoidSendData((u8)loc_Temp);     // Temp Value (Read Only)
            UART_VoidSendData(0x31);             // CRC Low
            UART_VoidSendData(0xCA);             // CRC High

#elif MODBUS_MODE == MODBUS_HOLDING_REG_MODE

            if (loc_u8Key == 'r' || loc_u8Key == 'R') 
            {
                // Holding Register Read (0x03)
                UART_VoidSendData(0x01);                // Slave ID
                UART_VoidSendData(0x03);                // Function Code 0x03
                UART_VoidSendData(0x02);                // Byte Count
                UART_VoidSendData(0x00);                // High Byte
                UART_VoidSendData(Loc_TempThreshold);   // Current Threshold
                UART_VoidSendData(0x31);                // CRC Low
                UART_VoidSendData(0xCA);                // CRC High
            }
            else if (loc_u8Key == 'w' || loc_u8Key == 'W')
            {
                // Holding Register Write (0x06)
                Loc_TempThreshold = 45;                 // Change Threshold to 45°C
                
                UART_VoidSendData(0x01);                // Slave ID
                UART_VoidSendData(0x06);                // Function Code 0x06
                UART_VoidSendData(0x00);                // Register Addr High
                UART_VoidSendData(0x00);                // Register Addr Low
                UART_VoidSendData(0x00);                // Value High
                UART_VoidSendData(Loc_TempThreshold);   // New Threshold (0x2D)
                UART_VoidSendData(0x31);                // CRC Low
                UART_VoidSendData(0xCA);                // CRC High
            }
#endif
        }

        MODBUS_voidTask();
    }
}