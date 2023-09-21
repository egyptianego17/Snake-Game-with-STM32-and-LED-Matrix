/*****************************************************/
/*                 SWC: RCC Driver                   */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*              Date: 21 July - 2023                 */
/*****************************************************/

/* File Gaurd */
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/* Base Address of RCC 0x40023800 - 0x40023BFF*/

#define RCC_CR_Reg           *((volatile u32*)0x40023800)
#define RCC_PLLCFGR_Reg      *((volatile u32*)0x40023804)
#define RCC_CFGR_Reg         *((volatile u32*)0x40023808)
#define RCC_AHB1ENR_Reg      *((volatile u32*)0x40023830)
#define RCC_AHB2ENR_Reg      *((volatile u32*)0x40023834)
#define RCC_APB1ENR_Reg      *((volatile u32*)0x40023840)
#define RCC_APB2ENR_Reg      *((volatile u32*)0x40023844)

#define AHB_PRESCALER_1   0
#define AHB_PRESCALER_2   8
#define AHB_PRESCALER_4   9
#define AHB_PRESCALER_8   10
#define AHB_PRESCALER_16  11
#define AHB_PRESCALER_64  12
#define AHB_PRESCALER_128 13
#define AHB_PRESCALER_256 14
#define AHB_PRESCALER_512 15

/* RCC Control Register Bits */
#define RCC_CR_HSION        0
#define RCC_CR_HSIRDY       1
#define RCC_CR_HSITRIM0     3
#define RCC_CR_HSITRIM1     4
#define RCC_CR_HSITRIM2     5
#define RCC_CR_HSITRIM3     6
#define RCC_CR_HSITRIM4     7
#define RCC_CR_HSICAL0      8
#define RCC_CR_HSICAL1      9
#define RCC_CR_HSICAL2      10
#define RCC_CR_HSICAL3      11
#define RCC_CR_HSICAL4      12
#define RCC_CR_HSICAL5      13
#define RCC_CR_HSICAL6      14
#define RCC_CR_HSICAL7      15
#define RCC_CR_HSEON        16
#define RCC_CR_HSERDY       17
#define RCC_CR_HSEBYP       18
#define RCC_CR_CSSON        19
#define RCC_CR_PLLON        24
#define RCC_CR_PLLRDY       25
#define RCC_CR_PLLI2SON     26
#define RCC_CR_PLLI2SRDY    27

/* RCC Configuration Register Bits */
#define RCC_CFGR_SW0 0
#define RCC_CFGR_SW1 1
#define RCC_CFGR_SWS0 2
#define RCC_CFGR_SWS1 3
#define RCC_CFGR_HPRE0 4
#define RCC_CFGR_HPRE1 5
#define RCC_CFGR_HPRE2 6
#define RCC_CFGR_HPRE3 7
#define RCC_CFGR_PPRE10 10
#define RCC_CFGR_PPRE11 11
#define RCC_CFGR_PPRE12 12
#define RCC_CFGR_PPRE20 13
#define RCC_CFGR_PPRE21 14
#define RCC_CFGR_PPRE22 15
#define RCC_CFGR_RTCPRE0 16
#define RCC_CFGR_RTCPRE1 17
#define RCC_CFGR_RTCPRE2 18
#define RCC_CFGR_RTCPRE3 19
#define RCC_CFGR_RTCPRE4 20
#define RCC_CFGR_MCO10 21
#define RCC_CFGR_MCO11 22
#define RCC_CFGR_MCO1PRE0 24
#define RCC_CFGR_MCO1PRE1 25
#define RCC_CFGR_MCO1PRE2 26
#define RCC_CFGR_MCO2PRE0 27
#define RCC_CFGR_MCO2PRE1 28
#define RCC_CFGR_MCO2PRE2 29
#define RCC_CFGR_MCO20 30
#define RCC_CFGR_MCO21 31

// RCC_PLLCFGR_Reg bits
#define RCC_PLLCFGR_PLLM0    0
#define RCC_PLLCFGR_PLLM1    1
#define RCC_PLLCFGR_PLLM2    2
#define RCC_PLLCFGR_PLLM3    3
#define RCC_PLLCFGR_PLLM4    4
#define RCC_PLLCFGR_PLLM5    5
#define RCC_PLLCFGR_PLLN0    6
#define RCC_PLLCFGR_PLLN1    7
#define RCC_PLLCFGR_PLLN2    8
#define RCC_PLLCFGR_PLLN3    9
#define RCC_PLLCFGR_PLLN4    10
#define RCC_PLLCFGR_PLLN5    11
#define RCC_PLLCFGR_PLLN6    12
#define RCC_PLLCFGR_PLLN7    13
#define RCC_PLLCFGR_PLLN8    14
#define RCC_PLLCFGR_PLLP0    16
#define RCC_PLLCFGR_PLLP1    17
#define RCC_PLLCFGR_PLLSRC   22
#define RCC_PLLCFGR_PLLQ0    24
#define RCC_PLLCFGR_PLLQ1    25
#define RCC_PLLCFGR_PLLQ2    26
#define RCC_PLLCFGR_PLLQ3    27


#endif