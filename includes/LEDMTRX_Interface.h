/*****************************************************/
/*              SWC: LEDMTRX Driver                  */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*             Date: 31 August - 2023                */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "CHARACTERS.h"

/* File Gaurd */
#ifndef LEDMTRX_INTERFACE_H
#define LEDMTRX_INTERFACE_H

/* Function Prototypes */
void LEDMTRX_voidInit(void);
void LEDMTRX_voidSendFrame(u8 *Copy_u8Frame);

#endif
