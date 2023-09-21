/*****************************************************/
/*                 SWC: RCC Driver                   */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*              Date: 21 July - 2023                 */
/*****************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_Interface.h"
#include "RCC_Private.h"
#include "RCC_Config.h"

/*********************************************************************/
/* Function Name: RCC_voidInitSysClk                                 */
/* i/p Arguments: None                                               */
/* Return: Void                                                      */
/* Description: This function initializes the system clock based on  */
/* the configured clock source (HSI, HSE, or PLL)                    */
/*********************************************************************/

void RCC_voidInitSysClk(void)
{
    #if (RCC_CLK_SRC == HSI)
        /* Enable HSI */
        SET_BIT(RCC_CR_Reg, RCC_CR_HSION);

        /* Select HSI as System Clk Source SW = 0b00 */
        CLR_BIT(RCC_CFGR_Reg, RCC_CFGR_SW0);
        CLR_BIT(RCC_CFGR_Reg, RCC_CFGR_SW1);

    #elif (RCC_CLK_SRC == HSE)
        /* Enable HSE */
        SET_BIT(RCC_CR_Reg, RCC_CR_HSEON);

        /* Select HSE as System Clk Source SW = 0b01 */
        SET_BIT(RCC_CFGR_Reg, RCC_CFGR_SW0);
        CLR_BIT(RCC_CFGR_Reg, RCC_CFGR_SW1);

    #elif (RCC_CLK_SRC == PLL)

        /* Set PLLM Reg */
        MODIFY_REGISTER_BITS(RCC_PLLCFGR_Reg,RCC_PLLCFGR_PLLM0,RCC_PLLCFGR_PLLM5,RCC_PLLM);

        /* Set PLLN Reg */
        MODIFY_REGISTER_BITS(RCC_PLLCFGR_Reg,RCC_PLLCFGR_PLLN0,RCC_PLLCFGR_PLLN8,RCC_PLLN);

        /* Set PLLP Reg */
        MODIFY_REGISTER_BITS(RCC_PLLCFGR_Reg,RCC_PLLCFGR_PLLP0,RCC_PLLCFGR_PLLP1,RCC_PLLP);

        /* Select PLL Source */
        #if (RCC_PLL_SRC == HSI)
            CLR_BIT(RCC_PLLCFGR_Reg, 22);

        #elif (RCC_PLL_SRC == HSE)
            SET_BIT(RCC_PLLCFGR_Reg, 22);

        #else
            #warning "Wrong Configuration"
        #endif

        /* Enable PLL */
        SET_BIT(RCC_CR_Reg, RCC_CR_PLLON);

        /* Select PLL as System Clk Source SW = 0b11 */
        SET_BIT(RCC_CFGR_Reg, RCC_CFGR_SW0);
        SET_BIT(RCC_CFGR_Reg, RCC_CFGR_SW1);

    #else 
        #warning "Wrong Configuration"
    #endif

    /* Set Prescaler */
    MODIFY_REGISTER_BITS(RCC_CFGR_Reg, RCC_CFGR_HPRE0, RCC_CFGR_HPRE3, RCC_AHB_PRESCALER);
}

/*********************************************************************/
/* Function Name: RCC_voidEnablePeripheralClk                        */
/* i/p Arguments: Copy_u8BusId Options (AHB1, AHB2, APB1, APB2)      */
/* i/p Arguments: Copy_u8PeripheralId Options (0-31)                 */
/* Return: Void                                                      */
/* Description: Enables the clock for a specific peripheral based on */
/* the selected bus identifier and peripheral identifier.            */
/*********************************************************************/

void RCC_voidEnablePeripheralClk(u8 Copy_u8BusId, u8 Copy_u8PeripheralId)
{
    /* i/p validation */
    if ((Copy_u8BusId > APB2) || (Copy_u8PeripheralId > 31))
    {
        /* Do nothing */
    }
    else
    {
        switch (Copy_u8BusId)
        {
        case AHB1:
            SET_BIT(RCC_AHB1ENR_Reg, Copy_u8PeripheralId);
            break;
        case AHB2:
            SET_BIT(RCC_AHB2ENR_Reg, Copy_u8PeripheralId);
            break;

        case APB1:
            SET_BIT(RCC_APB1ENR_Reg, Copy_u8PeripheralId);
            break;

        case APB2:
            SET_BIT(RCC_APB2ENR_Reg, Copy_u8PeripheralId);
            break;
        
        default:
            break;
        }
    }
}
