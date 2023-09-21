/*****************************************************/
/*              SWC: SysTick Driver                  */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*              Date: 4 August - 2023                */
/*****************************************************/

#include "SysTick_Config.h"

/* File Gaurd */
#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

/* Base Address of SysTick 0xE000E010 - 0xE000E01C*/

#define STK_CTRL_Reg            *((volatile u32*)0xE000E010)
#define STK_LOAD_Reg            *((volatile u32*)0xE000E014)
#define STK_VAL_Reg             *((volatile u32*)0xE000E018)

/* SysTick control and status register */
#define STK_CTRL_ENABLE         0
#define STK_CTRL_TICK_INT       1
#define STK_CTRL_CLK_SOURCE     2
#define STK_CTRL_COUNT_FLAG     16

/* SysTick reload value register */
#define STK_LOAD_RELOAD0        0
#define STK_LOAD_RELOAD23       23

#define AHB                     0
#define AHB_DIV_BY_8            1

#define SINGLE_INTERVAL         0
#define PERIODIC_INTERVAL       1

#if (STK_CLK_SOURCE == AHB)
	#define TICKS_DIV_FACTOR (AHB_CLK_VALUE/(TICKS_OF_ONE_SECOND))
#elif (STK_CLK_SOURCE == AHB_DIV_BY_8)
	#define TICKS_DIV_FACTOR (AHB_CLK_VALUE/(TICKS_OF_ONE_SECOND*8))
#endif

#define TICKS_OF_ONE_SECOND     1000000

#endif
