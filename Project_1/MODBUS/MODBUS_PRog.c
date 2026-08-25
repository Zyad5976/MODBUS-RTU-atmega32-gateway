/*
 * MODBUS_Prog.c
 *
 * Created: 8/3/2026 11:26:02 AM
 * Author: Eltawel
 */ 
#include "../Lib/STD_TYPES.h"
#include "../Lib/BIT_MATH.h"
#include "../MCAL/DIO/DIO_INterface.h"
#include "../MCAL/UART/UART_INterface.h"
#include "../HAL/MAX485/MAX485_INterface.h"
#include "../HAL/Relay/RELAY_INterface.h"
#include "../MCAL/ADC/ADC_INterface.h"
#include "MODBUS_INterface.h"
#include "MODBUS_CFG.h"

#define MODBUS_SLAVE_ID                 0x01
#define FC_WRITE_SINGLE_COIL            0x05
#define FC_READ_INPUT_REG               0x04
#define FC_READ_HOLDING_REG             0x03

static u16 MODBUS_u16ClacCRC(u8 *pu8data, u8 u8length)
{
    u16 Loc_CRC = 0xFFFF;
    u8 Loc_Byte = 0, Loc_Bit = 0;
    
    for(Loc_Byte = 0; Loc_Byte < u8length; Loc_Byte++)
    {
        Loc_CRC ^= (u16)pu8data[Loc_Byte];
        
        for(Loc_Bit = 0; Loc_Bit < 8; Loc_Bit++)
        {
            if(Loc_CRC & 0x0001)
            {
                Loc_CRC >>= 1;
                Loc_CRC ^= 0xA001;
            }
            else
            {
                Loc_CRC >>= 1;
            }
        }
    }
    
    return Loc_CRC;
}

static void MODBUS_VoidProcessFrame(u8 *pu8frame)
{
	u8 Loc_TXIndex = 0;
	
	// 1. Check Slave ID
	if(pu8frame[0] != MODBUS_SLAVE_ID)
	{
		return;
	}
	
	// 2. Validate Received CRC
	u16 loc_CalculatedCRC = MODBUS_u16ClacCRC(pu8frame, 6);
	u16 loc_ReceivedCRC   = ((u16)pu8frame[7] << 8) | pu8frame[6];
	
	if(loc_CalculatedCRC != loc_ReceivedCRC)
	{
		return;
	}
	
	// 3. Process Function Codes
	if(pu8frame[1] == FC_WRITE_SINGLE_COIL)
	{
		if(pu8frame[4] == 0xFF && pu8frame[5] == 0x00)
		{
			RELAY_VoidTurnON();
		}
		else if(pu8frame[4] == 0x00 && pu8frame[5] == 0x00)
		{
			RELAY_VoidTurnOFF();
		}
		
		for(Loc_TXIndex = 0; Loc_TXIndex < 8; Loc_TXIndex++)
		{
			UART_VoidSendData(pu8frame[Loc_TXIndex]);
		}
	}
	else if((pu8frame[1] == FC_READ_INPUT_REG) || (pu8frame[1] == FC_READ_HOLDING_REG))
	{
		u16 loc_ADCVal     = ADC_u16GetChannelReading(ADC2);
		u16 loc_Temp       = (u16)(((u32)loc_ADCVal * 500) / 1024);

		u8 Loc_TXBuffer[9];
		Loc_TXBuffer[0] = MODBUS_SLAVE_ID;
		Loc_TXBuffer[1] = pu8frame[1];
		Loc_TXBuffer[2] = 0x04;                           // Byte Count (4 Bytes Data)
		
		// Register 1: Temp
		Loc_TXBuffer[3] = (u8)(loc_Temp >> 8);            // High Byte
		Loc_TXBuffer[4] = (u8)(loc_Temp & 0xFF);          // Low Byte
		
		// CRC Calculation for 7 Bytes
		u16 loc_ResponseCRC = MODBUS_u16ClacCRC(Loc_TXBuffer, 5);
		Loc_TXBuffer[5] = (u8)(loc_ResponseCRC & 0xFF);   // CRC Low
		Loc_TXBuffer[6] = (u8)(loc_ResponseCRC >> 8);     // CRC High
		
		// Send Response Frame
		for(Loc_TXIndex = 0; Loc_TXIndex < 9; Loc_TXIndex++)
		{
			UART_VoidSendData(Loc_TXBuffer[Loc_TXIndex]);
		}
	}
}

void MODBUS_voidInit(void)
{
    MAX485_VoidInit();
}

void MODBUS_voidTask(void)
{
    static u8 Loc_Frame[8];
    static u8 Loc_Index = 0;
    u8 Loc_NewByte = 0;
    
    if (UART_u8ReceiveNoBlock(&Loc_NewByte) == 1)
    {
        if (Loc_Index == 0 && Loc_NewByte != MODBUS_SLAVE_ID)
        {
            Loc_Index = 0;
            return;
        }

        Loc_Frame[Loc_Index] = Loc_NewByte;
        Loc_Index++;
        
        if (Loc_Index == 8)
        {
            MODBUS_VoidProcessFrame(Loc_Frame);
            Loc_Index = 0;
        }
    }
}