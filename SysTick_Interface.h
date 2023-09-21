/*****************************************************/
/*              SWC: SysTick Driver                  */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*              Date: 4 August - 2023                */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* File Gaurd */
#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

/* Function Prototypes */
void STK_voidInit(void);
void STK_voidDelay_us(u32 Copy_u32Time);
void STK_voidDelay_ms(u32 Copy_u32Time);
void STK_voidSetIntervalSingle(u32 Copy_u32Time, void (Copy_pFunc)(void));
void STK_voidSetIntervalPeriodic(u32 Copy_u32Time, void (Copy_pFunc)(void));

#endif