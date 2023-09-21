/*****************************************************/
/*                 SWC: RCC Driver                   */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*              Date: 21 July - 2023                 */
/*****************************************************/

/* File Gaurd */
#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/* Options for Clk Source (HSI - HSE - PLL)                */
#define RCC_CLK_SRC HSI

/* Options for PLL Source (HSI - HSE)                      */
#define RCC_PLL_SRC HSI

/* PLLM: REG_Range 2 ≤ PLLM ≤ 63
   0.5≤Fsrc(Mhz)/PLLM≤1 
   Recommended to be 0.5 × Fsrc(Mhz)                       */
#define RCC_PLLM 8

/* PLLN: REG_Range 192 ≤ PLLN ≤ 432 
   192≤(PLLN×Fsrc(Mhz)/PLLM)≤432                           */
#define RCC_PLLN 210

/* PLLP Options: 0: PLLP = 2
                 1: PLLP = 4
                 2: PLLP = 6
                 3: PLLP = 8 
   PLLN×Fsrc(Mhz)/(PLLM*PLLP) Must not exceed 84 MHz       */
#define RCC_PLLP 2

/* Options for RCC_AHB_PRESCALER: AHB_PRESCALER_1
                                  AHB_PRESCALER_2   
                                  AHB_PRESCALER_4   
                                  AHB_PRESCALER_8   
                                  AHB_PRESCALER_16  
                                  AHB_PRESCALER_64  
                                  AHB_PRESCALER_128 
                                  AHB_PRESCALER_256 
                                  AHB_PRESCALER_512 
                                                           */

#define RCC_AHB_PRESCALER AHB_PRESCALER_1

/* Options for RCC_CLK_SRC */
#define HSI 0
#define HSE 1
#define PLL 2

/* Options for Init RCC_AHB_PRESCALER */
#define AHB_PRESCALER_1   0
#define AHB_PRESCALER_2   8
#define AHB_PRESCALER_4   9
#define AHB_PRESCALER_8   10
#define AHB_PRESCALER_16  11
#define AHB_PRESCALER_64  12
#define AHB_PRESCALER_128 13
#define AHB_PRESCALER_256 14
#define AHB_PRESCALER_512 15

#endif
