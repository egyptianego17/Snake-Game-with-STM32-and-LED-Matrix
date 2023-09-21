/*****************************************************/
/*                SWC: EXTI Driver                   */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*             Date: 19 August - 2023                */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_Interface.h"
#include "EXTI_Private.h"
#include "EXTI_Config.h"

/* Function pointers to store the callback function */
typedef void (*FunctionPointer)(void);
static FunctionPointer GpF[16] = {NULL};


/*****************************************************************************/
/* Function Name: EXTI_voidInit                                              */
/* i/p Arguments: u8 Copy_u8ID: Options (EXTI_EXTI0->EXTI_EXTI15)            */
/*                u8 Copy_u8Mode: Options (EXTI_RISING_EDGE,                 */
/*                                         EXTI_FALLING_EDGE                 */
/*                                         EXTI_ON_CHANGE)                   */
/* Return: void                                                              */
/* Description: Initializes the EXTI line with the specified mode.           */
/*****************************************************************************/

void EXTI_voidInit(u8 Copy_u8ID, u8 Copy_u8Mode)
{
    /* i/p validation */
    if (Copy_u8Mode > EXTI_ON_CHANGE)
    {
        /* Do nothing */
    }
    else
    {
        /* Configure the EXTI mode based on the specified mode */
        switch (Copy_u8Mode)
        {
        case EXTI_RISING_EDGE:
            SET_BIT(EXTI->RTSR, Copy_u8ID);   /* Set Rising Edge Trigger */
            CLR_BIT(EXTI->FTSR, Copy_u8ID);   /* Clear Falling Edge Trigger */
            break;
            
        case EXTI_FALLING_EDGE:
            SET_BIT(EXTI->FTSR, Copy_u8ID);   /* Set Falling Edge Trigger */
            CLR_BIT(EXTI->RTSR, Copy_u8ID);   /* Clear Rising Edge Trigger */
            break;

        case EXTI_ON_CHANGE:
            SET_BIT(EXTI->RTSR, Copy_u8ID);   /* Set Rising Edge Trigger */
            SET_BIT(EXTI->FTSR, Copy_u8ID);   /* Set Falling Edge Trigger */
            break;
        
        default:
            break;
        }
    }
}


/*****************************************************************************/
/* Function Name: EXTI_voidEXTIConfig                                        */
/* i/p Arguments: u8 Copy_u8ID: Options (EXTI_EXTI0->EXTI_EXTI15)            */
/*                u8 Copy_u8Port: Options (EXTI_PA, EXTI_PB, EXTI_PC)        */
/* Return: void                                                              */
/* Description: Configures the EXTI peripheral for a specific line.          */
/*****************************************************************************/

void EXTI_voidEXTIConfig(u8 Copy_u8ID, u8 Copy_u8Port)
{
    /* i/p validation */
    if ((Copy_u8ID > EXTI_EXTI15) || (Copy_u8Port > EXTI_PC))
    {
        /* Do nothing */
    }
    else
    {
        /* Configure the EXTI line to use the specified port */
        MODIFY_REGISTER_BITS(SYSCFG_EX->EXTICR[Copy_u8ID / 4], (Copy_u8ID * 4) % 16, ((Copy_u8ID * 4) % 16) + 3, Copy_u8Port);
    }
}


/*****************************************************************************/
/* Function Name: EXTI_voidEnable                                            */
/* i/p Arguments: u8 Copy_u8ID: Options (EXTI_EXTI0->EXTI_EXTI15)            */
/* Return: void                                                              */
/* Description: Enables the EXTI interrupt for the specified line.           */
/*****************************************************************************/

void EXTI_voidEnable(u8 Copy_u8ID)
{
    /* i/p validation */
    if (Copy_u8ID > EXTI_EXTI15)
    {
        /* Do nothing */
    }
    else
    {
        /* Enable EXTI line */
        SET_BIT(EXTI->IMR, Copy_u8ID);
        SET_BIT(EXTI->EMR, Copy_u8ID);
    }
}


/*****************************************************************************/
/* Function Name: EXTI_voidDisable                                           */
/* i/p Arguments: u8 Copy_u8ID: Options (EXTI_EXTI0->EXTI_EXTI15)            */
/* Return: void                                                              */
/* Description: Disables the EXTI interrupt for the specified line.          */
/*****************************************************************************/

void EXTI_voidDisable(u8 Copy_u8ID)
{
    /* i/p validation */
    if (Copy_u8ID > EXTI_EXTI15)
    {
        /* Do nothing */
    }
    else
    {
        /* Disable EXTI line */
        CLR_BIT(EXTI->IMR, Copy_u8ID);
        CLR_BIT(EXTI->EMR, Copy_u8ID);
    }
}


/*****************************************************************************/
/* Function Name: EXTI_voidSoftwareTrigger                                   */
/* i/p Arguments: u8 Copy_u8ID: Options (EXTI_EXTI0->EXTI_EXTI15)            */
/* Return: void                                                              */
/* Description: Triggers the EXTI interrupt manually for the specified line. */
/*****************************************************************************/

void EXTI_voidSoftwareTrigger(u8 Copy_u8ID)
{
    /* i/p validation */
    if (Copy_u8ID > EXTI_EXTI15)
    {
        /* Do nothing */
    }
    else
    {
        /* Set the software trigger bit for the EXTI line */
        SET_BIT(EXTI->SWIER, Copy_u8ID);
    }
}


/*****************************************************************************/
/* Function Name: EXTI_voidSetCallBack                                       */
/* i/p Arguments: u8 Copy_u8ID: Options (EXTI_EXTI0->EXTI_EXTI15)            */
/*                void (*LpF)(void) - Pointer to the callback function       */
/* Return: void                                                              */
/* Description: Associates a callback function with the EXTI interrupt.      */
/*****************************************************************************/

void EXTI_voidSetCallBack(u8 Copy_u8ID, void (*LpF)(void))
{
    /* Store the provided callback function at the specified EXTI line ID */
    GpF[Copy_u8ID] = LpF;
}


void EXTI0_IRQHandler(void)
{
    if (GpF[0] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[0]();
    }
}

void EXTI1_IRQHandler(void)
{
    if (GpF[1] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[1]();
    }
}

void EXTI2_IRQHandler(void)
{
    if (GpF[2] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[2]();
    }
}

void EXTI3_IRQHandler(void)
{
    if (GpF[3] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[3]();
    }
}

void EXTI4_IRQHandler(void)
{
    if (GpF[4] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[4]();
    }
}

void EXTI5_IRQHandler(void)
{
    if (GpF[5] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[5]();
    }
}

void EXTI6_IRQHandler(void)
{
    if (GpF[6] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[6]();
    }
}

void EXTI7_IRQHandler(void)
{
    if (GpF[7] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[7]();
    }
}

void EXTI8_IRQHandler(void)
{
    if (GpF[8] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[8]();
    }
}

void EXTI9_IRQHandler(void)
{
    if (GpF[9] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[9]();
    }
}

void EXTI10_IRQHandler(void)
{
    if (GpF[10] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[10]();
    }
}

void EXTI11_IRQHandler(void)
{
    if (GpF[11] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[11]();
    }
}

void EXTI12_IRQHandler(void)
{
    if (GpF[12] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[12]();
    }
}

void EXTI13_IRQHandler(void)
{
    if (GpF[13] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[13]();
    }
}

void EXTI14_IRQHandler(void)
{
    if (GpF[14] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[14]();
    }
}

void EXTI15_IRQHandler(void)
{
    if (GpF[15] == NULL)
    {
        /* Do nothing */
    }
    else
    {
        GpF[15]();
    }
}
