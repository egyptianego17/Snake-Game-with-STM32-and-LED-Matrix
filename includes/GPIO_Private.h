/*****************************************************/
/*                 SWC: GPIO Driver                  */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.1                    */
/*              Date: 28 July - 2023                 */
/*****************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* File Gaurd */
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H


typedef struct 
{
    volatile u32 MODER;
    volatile u32 OTYPER;
    volatile u32 OSPEEDR;
    volatile u32 PUDPR;
    volatile u32 IDR;
    volatile u32 ODR;
    volatile u32 BSRR;
    volatile u32 LCKR;
    volatile u32 AFRL;
    volatile u32 AFRH;
} GPIO_R;

/* Base Address of GPIOA 0x40020000 - 0x400203FF */
#define GPIOA       ((GPIO_R*)0x40020000)      

/* Base Address of GPIOB 0x40020400 - 0x400207FF */
#define GPIOB       ((GPIO_R*)0x40020400)      

/* Base Address of GPIOC 0x40020800 - 0x40020BFF */
#define GPIOC       ((GPIO_R*)0x40020800)     

/* Macros to map integer values to port and pin values */ 
#define GET_PORT(pin) ((pin) / 16)
#define GET_PIN(pin)  ((pin) % 16)

/* GPIO Port IDs */
#define IOA        0
#define IOB        1
#define IOC        2

#endif
