/*****************************************************/
/*                SWC: NVIC Driver                   */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*             Date: 11 August - 2023                */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* File Gaurd */
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H


/* CMSIS functions for NVIC control  */
void NVIC_EnableIRQ(u8 Copy_u8IRQn);
void NVIC_DisableIRQ(u8 Copy_u8IRQn);
void NVIC_SetPendingIRQ (u8 Copy_u8IRQn);
void NVIC_ClearPendingIRQ (u8 Copy_u8IRQn);
void NVIC_voidSetPriorityConfig(u8 Copy_u8PriGroup);
void NVIC_voidSetPriority(u8 Copy_u8IRQn, u8 Copy_u8GId, u8 Copy_u8SGId);

/* Options for Priority Group Options */
#define G16_SG0              0
#define G8_SG2               4
#define G4_SG4               5
#define G2_SG8               6
#define G0_SG16              7

/* Options for IRQ */
#define WWDG                 0
#define EXTI16               1
#define EXTI21               2
#define EXTI22               3
#define FLASH                4
#define RCC                  5
#define EXTI0                6
#define EXTI1                7
#define EXTI2                8
#define EXTI3                9
#define EXTI4                10
#define DMA1_Stream0         11
#define DMA1_Stream1         12
#define DMA1_Stream2         13
#define DMA1_Stream3         14
#define DMA1_Stream4         15
#define DMA1_Stream5         16
#define DMA1_Stream6         17
#define ADC                  18
#define EXTI9_5              23
#define TIM1_BRK_TIM9        24
#define TIM1_UP_TIM10        25
#define TIM1_TRG_COM_TIM11   26
#define TIM1_CC              27
#define TIM2                 28
#define TIM3                 29
#define TIM4                 30
#define I2C1_EV              31
#define I2C1_ER              32
#define I2C2_EV              33
#define I2C2_ER              34
#define SPI1                 35
#define SPI2                 36
#define USART1               37
#define USART2               38
#define EXTI15_10            40
#define EXTI17_RTC_Alarm     41
#define EXTI18_OTG_FS_WKUP   42
#define DMA1_Stream7         47
#define SDIO                 49
#define TIM5                 50
#define SPI3                 51
#define DMA2_Stream0         56
#define DMA2_Stream1         57
#define DMA2_Stream2         58
#define DMA2_Stream3         59
#define DMA2_Stream4         60
#define OTG_FS               67
#define DMA2_Stream5         68
#define DMA2_Stream6         69
#define DMA2_Stream7         70
#define USART6               71
#define I2C3_EV              72
#define I2C3_ER              73
#define FPU                  81
#define SPI4                 84

#endif