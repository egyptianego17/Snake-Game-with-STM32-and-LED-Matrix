/*****************************************************/
/*              SWC: LEDMTRX Driver                  */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*             Date: 31 August - 2023                */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "LEDMTRX_Interface.h"
#include "LEDMTRX_Private.h"
#include "LEDMTRX_Config.h"

#include "GPIO_Interface.h"
#include "STP_Interface.h"
#include "SysTick_Interface.h"

/*****************************************************************************/
/* Function Name: LEDMTRX_voidInit                                           */
/* i/p Arguments: void                                                       */
/* Return: void                                                              */
/* Description: Initialize Serial to Parallel IC Pins.                       */
/*****************************************************************************/

void LEDMTRX_voidInit(void)
{
    /* Set the pin modes for STP Pins */
    GPIO_voidSetPinMode(COLUMN_DATA, OUTPUT);
    GPIO_voidSetPinMode(COLUMN_CLOCK, OUTPUT);
    GPIO_voidSetPinMode(ROW_DATA, OUTPUT);
    GPIO_voidSetPinMode(ROW_CLOCK, OUTPUT);
    GPIO_voidSetPinMode(LATCH, OUTPUT);

    /* Set the pin speeds for STP Pins */
    GPIO_voidSetPinSpeed(COLUMN_DATA, OUTPUT_MS);
    GPIO_voidSetPinSpeed(COLUMN_CLOCK, OUTPUT_MS);
    GPIO_voidSetPinSpeed(ROW_DATA, OUTPUT_MS);
    GPIO_voidSetPinSpeed(ROW_CLOCK, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LATCH, OUTPUT_MS);
}


/*****************************************************************************/
/* Function Name: LEDMTRX_voidSendFrame                                      */
/* i/p Arguments: u8 Copy_u8Frame: A pointer to the frame array.             */
/* Return: void                                                              */
/* Description: Function to display one frame on the LED matrix.             */
/*****************************************************************************/

void LEDMTRX_voidSendFrame(u8 *Copy_u8Frame)
{
    u8 Local_u8Counter = 0;
    for (Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++)
    {
        /* Disable All Columns */
        STP_voidSendFrame(COLUMN_DATA, COLUMN_CLOCK, LATCH, 0b00000000);

        /* Set Row Value*/
        STP_voidSendFrame(ROW_DATA, ROW_CLOCK, LATCH, ~Copy_u8Frame[Local_u8Counter]);

        /* Enable Column */
        STP_voidSendFrame(COLUMN_DATA, COLUMN_CLOCK, LATCH, (0b00000000 | 1 << Local_u8Counter));

        /* Delay */
        STK_voidDelay_us(2500);
    }
}
