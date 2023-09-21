/*****************************************************/
/*                SWC: STP Driver                    */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*             Date: 28 August - 2023                */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STP_Interface.h"
#include "STP_Private.h"
#include "STP_Config.h"

#include "GPIO_Interface.h"

/*****************************************************************************/
/* Function Name: STP_voidSendFrame                                          */
/* i/p Arguments: u8 Copy_u8DataPin: Options (PA0 -> PC15)                   */
/*                u8 Copy_u8ClockPin: Options (PA0 -> PC15)                  */
/*                u8 Copy_u8LatchPin: Options (PA0 -> PC15)                  */
/*                u8 Copy_u8Frame: Options (0 -> 255)                        */
/* Return: void                                                              */
/* Description: Sends a frame of data to a shift register IC using specified */
/*              pins.                                                        */
/*****************************************************************************/

void STP_voidSendFrame(u8 Copy_u8DataPin, u8 Copy_u8ClockPin, u8 Copy_u8LatchPin, u8 Copy_u8Frame)
{
    /* Set the latch pin LOW to prepare for data transmission */
    GPIO_voidSetPinValue(Copy_u8LatchPin, LOW);

    /* Loop through each bit (8 bits) in the frame data */
    for (u8 Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++)
    {
        /* Set the data pin to either HIGH or LOW based on the current bit in the frame */
        GPIO_voidSetPinValue(Copy_u8DataPin, GET_BIT(Copy_u8Frame, Local_u8Counter));

        /* Pulse the clock pin to shift the current bit into the register */
        GPIO_voidSetPinValue(Copy_u8ClockPin, HIGH);
        GPIO_voidSetPinValue(Copy_u8ClockPin, LOW);
    }

    /* Set the latch pin HIGH to update the shift register's output with the new data */
    GPIO_voidSetPinValue(Copy_u8LatchPin, HIGH);
}
