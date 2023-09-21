/*****************************************************/
/*                 SWC: RCC Driver                   */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*              Date: 21 July - 2023                 */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"


/* File Gaurd */
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/* Functions Prototypes */
void RCC_voidInitSysClk(void);
void RCC_voidEnablePeripheralClk(u8 Copy_u8BusId, u8 Copy_u8PeripheralId);
void RCC_voidDisablePeripheralClk(u8 Copy_u8BusId, u8 Copy_u8PeripheralId);

/* Options for Copy_u8BusId */
#define AHB1 0
#define AHB2 1
#define APB1 2
#define APB2 3

/* Options for Copy_u8PeripheralId */
/* AHB1 */
#define RCC_AHB1ENR_GPIOAEN   0
#define RCC_AHB1ENR_GPIOBEN   1
#define RCC_AHB1ENR_GPIOCEN   2
#define RCC_AHB1ENR_GPIODEN   3
#define RCC_AHB1ENR_GPIOEEN   4
#define RCC_AHB1ENR_GPIOHEN   7
#define RCC_AHB1ENR_CRCEN     12
#define RCC_AHB1ENR_DMA1EN    21
#define RCC_AHB1ENR_DMA2EN    22

/* AHB2 */
#define RCC_AHB2ENR_OTGFSEN   7

/* APB1 */
#define RCC_APB1ENR_TIM2EN   0
#define RCC_APB1ENR_TIM3EN   1
#define RCC_APB1ENR_TIM4EN   2
#define RCC_APB1ENR_TIM5EN   3
#define RCC_APB1ENR_WWDGEN   11
#define RCC_APB1ENR_SPI2EN   14
#define RCC_APB1ENR_SPI3EN   15
#define RCC_APB1ENR_USART2EN 17
#define RCC_APB1ENR_I2C1EN   21
#define RCC_APB1ENR_I2C2EN   22
#define RCC_APB1ENR_I2C3EN   23
#define RCC_APB1ENR_PWREN    28

/* APB2 */
#define RCC_APB2ENR_TIM1EN    0
#define RCC_APB2ENR_USART1EN  4
#define RCC_APB2ENR_USART6EN  5
#define RCC_APB2ENR_ADC1EN    8
#define RCC_APB2ENR_SDIOEN    11
#define RCC_APB2ENR_SPI1EN    12
#define RCC_APB2ENR_SPI4EN    13
#define RCC_APB2ENR_SYSCFGEN  14
#define RCC_APB2ENR_TIM9EN    16
#define RCC_APB2ENR_TIM10EN   17
#define RCC_APB2ENR_TIM11EN   18

#endif