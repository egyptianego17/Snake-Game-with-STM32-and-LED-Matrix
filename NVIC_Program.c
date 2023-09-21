/*****************************************************/
/*                SWC: NVIC Driver                   */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*             Date: 11 August - 2023                */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_Interface.h"
#include "NVIC_Private.h"
#include "NVIC_Config.h"


/*****************************************************************************/
/* Function Name: NVIC_EnableIRQ                                             */
/* Description: Enable a specific interrupt in the NVIC.                     */
/* i/p Arguments: u8 Copy_u8IRQn: Options (0->84)                            */
/* Return: void                                                              */
/*****************************************************************************/

void NVIC_EnableIRQ(u8 Copy_u8IRQn)
{
    /* i/p validation */
    if (Copy_u8IRQn > SPI4)
    {
        /* Do nothing */
    }
    else
    {
        NVIC->ISER[Copy_u8IRQn / 32] = 1 << Copy_u8IRQn % 32;
    }
}


/*****************************************************************************/
/* Function Name: NVIC_DisableIRQ                                            */
/* Description: Disable a specific interrupt in the NVIC.                    */
/* i/p Arguments: u8 Copy_u8IRQn: Options (0->84)                            */
/* Return: void                                                              */
/*****************************************************************************/

void NVIC_DisableIRQ(u8 Copy_u8IRQn)
{
    /* i/p validation */
    if (Copy_u8IRQn > SPI4)
    {
        /* Do nothing */
    }
    else
    {
        NVIC->ICER[Copy_u8IRQn / 32] = 1 << Copy_u8IRQn % 32;
    }
}


/*****************************************************************************/
/* Function Name: NVIC_SetPendingIRQ                                         */
/* Description: Set a specific interrupt as pending.                         */
/* i/p Arguments: u8 Copy_u8IRQn: Options (0->84)                            */
/* Return: void                                                              */
/*****************************************************************************/

void NVIC_SetPendingIRQ(u8 Copy_u8IRQn)
{
    /* i/p validation */
    if (Copy_u8IRQn > SPI4)
    {
        /* Do nothing */
    }
    else
    {
        NVIC->ISPR[Copy_u8IRQn / 32] = 1 << Copy_u8IRQn % 32;
    }
}


/*****************************************************************************/
/* Function Name: NVIC_ClearPendingIRQ                                       */
/* Description: Clear the pending status of a specific interrupt.            */
/* i/p Arguments: u8 Copy_u8IRQn: Options (0->84)                            */
/* Return: void                                                              */
/*****************************************************************************/

void NVIC_ClearPendingIRQ(u8 Copy_u8IRQn)
{
    /* i/p validation */
    if (Copy_u8IRQn > SPI4)
    {
        /* Do nothing */
    }
    else
    {
        NVIC->ICPR[Copy_u8IRQn / 32] = 1 << Copy_u8IRQn % 32;
    }
}


/*****************************************************************************/
/* Function Name: NVIC_voidSetPriorityConfig                                 */
/* Description: Set the priority grouping for the NVIC.                      */
/* i/p Arguments: u8 Copy_u8PriGroup: Options (G16_SG0, G8_SG2, G4_SG4,      */
/*                                             G2_SG8, G0_SG16)              */
/* Return: void                                                              */
/*****************************************************************************/

void NVIC_voidSetPriorityConfig(u8 Copy_u8PriGroup)
{
    /* i/p validation */
    if (Copy_u8PriGroup > G0_SG16)
    {
        /* Do nothing */
    }
    else
    {
        SCB_AIRCR_Reg = (Copy_u8PriGroup << SCB_PRIGROUP0) | (VECTKEY << SCB_VECTKEYSTAT0);
    }
}


/*********************************************************************************/
/* Function Name: NVIC_voidSetPriority                                           */
/* Description: Set the priority of a specific interrupt based on the            */
/*              priority grouping.                                               */
/* i/p Arguments: u8 Copy_u8IRQn: Options (0->84)                                */
/*                u8 Copy_u8GId: Options (0->15)                                 */
/*                u8 Copy_u8SGId: Options (0->15)                                */
/* Return: void                                                                  */
/*********************************************************************************/

void NVIC_voidSetPriority(u8 Copy_u8IRQn, u8 Copy_u8GId, u8 Copy_u8SGId)
{
    /* i/p validation */
    if ((Copy_u8IRQn > SPI4) || (Copy_u8GId > 15) || (Copy_u8SGId > 15))
    {
        /* Do nothing */
    }
    else
    {
    u8 Local_u8Priority = Copy_u8SGId | (Copy_u8GId << (GET_BITS(SCB_AIRCR_Reg, SCB_PRIGROUP0, SCB_PRIGROUP2) - PRIGROUP_DEFAULT));
    MODIFY_REGISTER_BITS(NVIC->IPR[Copy_u8IRQn], IPR_PRI0, IPR_PRI3, Local_u8Priority);
    }
}

