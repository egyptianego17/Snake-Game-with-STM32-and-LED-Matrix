/*****************************************************/
/*                SWC: NVIC Driver                   */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*             Date: 11 August - 2023                */
/*****************************************************/


/* File Gaurd */
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

/* Base Address of NVIC 0xE000E100 - 0xE000E4EF */
typedef struct
{
    volatile u32 ISER[32];  /* Only first 8 Reg Locations is Accessible and 9 - 31 is Reserved */
    volatile u32 ICER[32];  /* Only first 8 Reg Locations is Accessible and 9 - 31 is Reserved */
    volatile u32 ISPR[32];  /* Only first 8 Reg Locations is Accessible and 9 - 31 is Reserved */
    volatile u32 ICPR[32];  /* Only first 8 Reg Locations is Accessible and 9 - 31 is Reserved */
    volatile u32 IABR[64];  /* Only first 8 Reg Locations is Accessible and 9 - 63 is Reserved */
    volatile u8  IPR [85];  
} NVIC_R;

#define NVIC              ((NVIC_R*)0xE000E100)     

#define SCB_AIRCR_Reg    *((volatile u32*)0xE000ED0C)

#define SCB_PRIGROUP0         8
#define SCB_PRIGROUP1         9
#define SCB_PRIGROUP2         10

#define SCB_VECTKEYSTAT0      16
#define SCB_VECTKEYSTAT15     31

#define IPR_PRI0              4
#define IPR_PRI3              7

#define PRIGROUP_DEFAULT      3

#define VECTKEY               0x5FA

 

#endif
