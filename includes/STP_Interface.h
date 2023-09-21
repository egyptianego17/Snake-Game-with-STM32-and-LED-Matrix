/*****************************************************/
/*                SWC: STP Driver                    */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*             Date: 28 August - 2023                */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* File Gaurd */
#ifndef STP_INTERFACE_H
#define STP_INTERFACE_H

/* Function Prototypes */
void STP_voidSendFrame(u8 Copy_u8DataPin, u8 Copy_u8ClockPin, u8 Copy_u8LatchPin, u8 Copy_u8Frame);

/* Options for Copy_u8DataPin, Copy_u8ClockPin Copy_u8LatchPin (PA0 -> PC15) */

/* Options for Copy_u8Frame (0 -> 255) */

/* Options for Copy_u8Shift (0 -> 8)   */


#endif
