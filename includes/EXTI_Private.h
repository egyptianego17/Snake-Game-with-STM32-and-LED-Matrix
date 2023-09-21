/*****************************************************/
/*                SWC: EXTI Driver                   */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*             Date: 19 August - 2023                */
/*****************************************************/


/* File Gaurd */
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

/* Base Address of EXTI 0x40013C00 - 0x40013FFF */
typedef struct
{
    volatile u32 IMR;
    volatile u32 EMR;
    volatile u32 RTSR;
    volatile u32 FTSR;
    volatile u32 SWIER;
    volatile u32 PR;
} EXTI_R;

#define EXTI                         ((EXTI_R*)0x40013C00)

typedef struct
{
    volatile u32 EXTICR[4];
} SYSCFG_R;

#define SYSCFG_EX                ((SYSCFG_R*)0x40013808)

#endif
