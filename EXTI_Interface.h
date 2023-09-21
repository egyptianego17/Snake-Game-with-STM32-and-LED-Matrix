/*****************************************************/
/*                SWC: EXTI Driver                   */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*             Date: 19 August - 2023                */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* File Gaurd */
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

/* Function Prototypes */
void EXTI_voidInit(u8 Copy_u8ID, u8 Copy_u8Mode);
void EXTI_voidEXTIConfig(u8 Copy_u8ID, u8 Copy_u8Port);
void EXTI_voidEnable(u8 Copy_u8ID);
void EXTI_voidDisable(u8 Copy_u8ID);
void EXTI_voidSoftwareTrigger(u8 Copy_u8ID);
void EXTI_voidSetCallBack(u8 Copy_u8ID ,void (*LpF)(void));

/* Options for Copy_u8Port */
#define EXTI_PA                 0
#define EXTI_PB                 1
#define EXTI_PC                 2
 
/* Options for Copy_u8Mode */ 
#define EXTI_RISING_EDGE        0
#define EXTI_FALLING_EDGE       1
#define EXTI_ON_CHANGE          2
 
/* Options for Copy_u8ID */
#define EXTI_EXTI0              0
#define EXTI_EXTI1              1
#define EXTI_EXTI2              2
#define EXTI_EXTI3              3
#define EXTI_EXTI4              4
#define EXTI_EXTI5              5
#define EXTI_EXTI6              6
#define EXTI_EXTI7              7
#define EXTI_EXTI8              8
#define EXTI_EXTI9              9
#define EXTI_EXTI10             10
#define EXTI_EXTI11             11
#define EXTI_EXTI12             12
#define EXTI_EXTI13             13
#define EXTI_EXTI14             14
#define EXTI_EXTI15             15

#endif
