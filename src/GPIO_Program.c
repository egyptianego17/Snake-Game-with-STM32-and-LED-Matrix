/*****************************************************/
/*                 SWC: GPIO Driver                  */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.1                    */
/*              Date: 28 July - 2023                 */
/*****************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_Interface.h"
#include "GPIO_Private.h"
#include "GPIO_Config.h"


/*****************************************************************************/
/* Function Name: GPIO_voidSetPinMode                                        */
/* i/p Arguments: u8 Copy_u8Pin Options (PA0 -> PC15)                        */
/* i/p Arguments: u8 Copy_u8PinMode Options (INPUT, OUTPUT, AF, ANALOG)      */
/* Return: Void                                                              */
/* Description: This function sets the mode (input, output,                  */
/*              alternate function, or analog) of a specified GPIO pin.      */
/*****************************************************************************/

void GPIO_voidSetPinMode(u8 Copy_u8Pin, u8 Copy_u8PinMode)
{
    /* i/p validation */
    if ((Copy_u8Pin > PC15) || (Copy_u8PinMode > ANALOG))
    {
        /* Do nothing */
    }
    else
    {
       switch (GET_PORT(Copy_u8Pin))
       {
           case IOA:
               MODIFY_REGISTER_BITS(GPIOA->MODER, GET_PIN(Copy_u8Pin)*2, GET_PIN(Copy_u8Pin)*2+1, Copy_u8PinMode);
               break;
           case IOB:
               MODIFY_REGISTER_BITS(GPIOB->MODER, GET_PIN(Copy_u8Pin)*2, GET_PIN(Copy_u8Pin)*2+1, Copy_u8PinMode);
               break;
           case IOC:
               MODIFY_REGISTER_BITS(GPIOC->MODER, GET_PIN(Copy_u8Pin)*2, GET_PIN(Copy_u8Pin)*2+1, Copy_u8PinMode);
               break;
           default:
               break;
       }
    }
}


/***********************************************************************************/
/* Function Name: GPIO_voidSetPinType                                              */
/* i/p Arguments: u8 Copy_u8Pin Options (PA0 -> PC15)                              */
/* i/p Arguments: u8 Copy_u8PinType Options (OUTPUT_PP, OUTPUT_OD)                 */
/* Return: Void                                                                    */
/* Description: This function sets the type (output push-pull, output open-drain.) */
/***********************************************************************************/

void GPIO_voidSetPinType(u8 Copy_u8Pin, u8 Copy_u8PinType)
{
    /* i/p validation */
    if ((Copy_u8Pin > PC15) || (Copy_u8PinType>OUTPUT_OD))
    {
        /* Do nothing */
    }
    else
    {
        switch (Copy_u8PinType)
        {
            case OUTPUT_PP:
                switch (GET_PORT(Copy_u8Pin))
                {
                    case IOA:
                        CLR_BIT(GPIOA->OTYPER, GET_PIN(Copy_u8Pin));
                        break;

                    case IOB:
                        CLR_BIT(GPIOB->OTYPER, GET_PIN(Copy_u8Pin));
                        break;

                    case IOC:
                        CLR_BIT(GPIOC->OTYPER, GET_PIN(Copy_u8Pin));
                        break;

                    default:
                        break;
                }
                break;

            case OUTPUT_OD:
                switch (GET_PORT(Copy_u8Pin))
                {
                    case IOA:
                        SET_BIT(GPIOA->OTYPER, GET_PIN(Copy_u8Pin));
                        break;

                    case IOB:
                        SET_BIT(GPIOB->OTYPER, GET_PIN(Copy_u8Pin));
                        break;

                    case IOC:
                        SET_BIT(GPIOC->OTYPER, GET_PIN(Copy_u8Pin));
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}


/******************************************************************************/
/* Function Name: GPIO_voidSetPinSpeed                                        */
/* i/p Arguments: u8 Copy_u8Pin Options (PA0 -> PC15)                         */
/* i/p Arguments: u8 Copy_u8PinSpeed Options (OUTPUT_LS, OUTPUT_MS,           */
/*                                            OUTPUT_HS, OUTPUT_VHS)          */
/* Return: void                                                               */
/* Description: This function sets the output speed for a specified GPIO pin. */
/******************************************************************************/

void GPIO_voidSetPinSpeed(u8 Copy_u8Pin, u8 Copy_u8PinSpeed)
{
    /* i/p validation */
    if ((Copy_u8Pin > PC15) || (Copy_u8PinSpeed > OUTPUT_VHS))
    {
        /* Do nothing */
    }
    else
    {
        switch (GET_PORT(Copy_u8Pin))
        {
            case IOA:
                MODIFY_REGISTER_BITS(GPIOA->OSPEEDR, GET_PIN(Copy_u8Pin)*2, GET_PIN(Copy_u8Pin)*2+1, Copy_u8PinSpeed);
                break;

            case IOB:
                MODIFY_REGISTER_BITS(GPIOB->OSPEEDR, GET_PIN(Copy_u8Pin)*2, GET_PIN(Copy_u8Pin)*2+1, Copy_u8PinSpeed);
                break;

            case IOC:
                MODIFY_REGISTER_BITS(GPIOC->OSPEEDR, GET_PIN(Copy_u8Pin)*2, GET_PIN(Copy_u8Pin)*2+1, Copy_u8PinSpeed);
                break;

            default:
                break;
        }
    }
}


/**********************************************************************************/
/* Function Name: GPIO_voidDefaultInit                                            */
/* i/p Arguments: u8 Copy_u8Pin Options (PA0 -> PC15)                             */
/* i/p Arguments: u8 Copy_u8PinPUPDOption: Options (FLOATING, INPUT_PU, INPUT_PD) */
/* Return: void                                                                   */
/* Description: This function sets the pull-up/pull-down configuration for        */
/*              a specified GPIO pin.                                             */
/*******************************************************************************s***/

void GPIO_voidSetPinPUPD(u8 Copy_u8Pin, u8 Copy_u8PinPUPDOption)
{
    /* i/p validation */
    if ((Copy_u8Pin > PC15) || (Copy_u8PinPUPDOption > INPUT_PD))
    {
        /* Do nothing */
    }
    else
    {
        switch (GET_PORT(Copy_u8Pin))
        {
            case IOA:
                MODIFY_REGISTER_BITS(GPIOA->PUDPR, GET_PIN(Copy_u8Pin)*2, GET_PIN(Copy_u8Pin)*2+1, Copy_u8PinPUPDOption);
                break;

            case IOB:
                MODIFY_REGISTER_BITS(GPIOB->PUDPR, GET_PIN(Copy_u8Pin)*2, GET_PIN(Copy_u8Pin)*2+1, Copy_u8PinPUPDOption);
                break;

            case IOC:
                MODIFY_REGISTER_BITS(GPIOC->PUDPR, GET_PIN(Copy_u8Pin)*2, GET_PIN(Copy_u8Pin)*2+1, Copy_u8PinPUPDOption);
                break;

            default:
                break;
        }
    }
}


/*****************************************************************************/
/* Function Name: GPIO_voidSetPinValue                                       */
/* i/p Arguments: u8 Copy_u8Pin Options (PA0 -> PC15)                        */
/* i/p Arguments: u8 Copy_u8PinValue Options (LOW, HIGH)                     */
/* Return: Void                                                              */
/* Description: This function sets the value of a specified GPIO pin.        */
/*              The value can be either LOW (0) or HIGH (1).                 */
/*****************************************************************************/

void GPIO_voidSetPinValue(u8 Copy_u8Pin, u8 Copy_u8PinValue)
{
    /* i/p validation */
    if ((Copy_u8Pin > PC15))
    {
        /* Do nothing */
    }
    else
    {
        switch (Copy_u8PinValue)
        {
            case LOW:
                switch (GET_PORT(Copy_u8Pin))
                {
                    case IOA:
                        CLR_BIT(GPIOA->ODR, GET_PIN(Copy_u8Pin));
                        break;

                    case IOB:
                        CLR_BIT(GPIOB->ODR, GET_PIN(Copy_u8Pin));
                        break;

                    case IOC:
                        CLR_BIT(GPIOC->ODR, GET_PIN(Copy_u8Pin));
                        break;

                    default:
                        break;
                }
                break;

            case HIGH:
                switch (GET_PORT(Copy_u8Pin))
                {
                    case IOA:
                        SET_BIT(GPIOA->ODR, GET_PIN(Copy_u8Pin));
                        break;

                    case IOB:
                        SET_BIT(GPIOB->ODR, GET_PIN(Copy_u8Pin));
                        break;

                    case IOC:
                        SET_BIT(GPIOC->ODR, GET_PIN(Copy_u8Pin));
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}


/*****************************************************************************/
/* Function Name: GPIO_voidSetPinValueDirectAccess                           */
/* i/p Arguments: u8 Copy_u8Pin Options (PA0 -> PC15)                        */
/* i/p Arguments: u8 Copy_u8PinValue Options (LOW, HIGH)                     */
/* Return: Void                                                              */
/* Description: This function directly sets or resets a specified GPIO pin.  */
/*****************************************************************************/

void GPIO_voidSetPinValueDirectAccess(u8 Copy_u8Pin, u8 Copy_u8PinValue)
{
    /* i/p validation */
    if ((Copy_u8Pin > PC15))
    {
        /* Do nothing */
    }
    else
    {
        switch (Copy_u8PinValue)
        {
            case RST:
                switch (GET_PORT(Copy_u8Pin))
                {
                    case IOA:
                        GPIOA->BSRR = (1 << GET_PIN(Copy_u8Pin)) + 16;
                        break;

                    case IOB:
                        GPIOB->BSRR = (1 << GET_PIN(Copy_u8Pin)) + 16;
                        break;

                    case IOC:
                        GPIOC->BSRR = (1 << GET_PIN(Copy_u8Pin)) + 16;
                        break;

                    default:
                        break;
                }
                break;

            case SET:
                switch (GET_PORT(Copy_u8Pin))
                {
                    case IOA:
                        GPIOA->BSRR = (1 << GET_PIN(Copy_u8Pin));
                        break;

                    case IOB:
                        GPIOB->BSRR = (1 << GET_PIN(Copy_u8Pin));
                        break;

                    case IOC:
                        GPIOC->BSRR = (1 << GET_PIN(Copy_u8Pin));
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}


/*****************************************************************************/
/* Function Name: GPIO_voidSetPortValue                                      */
/* i/p Arguments: u8 Copy_u8Port Options (IOA, IOB, IOC)                     */
/* i/p Arguments: u16 Copy_u8PortValue (0x0000 to 0xFFFF)                    */
/* Return: Void                                                              */
/* Description: This function sets the value of the entire GPIO port.        */
/*              The port value is specified by a 16-bit binary number,       */
/*              where each bit represents the state of a corresponding pin.  */
/*              The function supports ports A, B, and C.                     */
/*****************************************************************************/

void GPIO_voidSetPortValue(u8 Copy_u8Port, u16 Copy_u8PortValue)
{
    /* i/p validation */
    if (Copy_u8Port > IOC)
    {
        /* Do nothing */
    }
    else
    {
        switch (Copy_u8Port)
        {
            case IOA:
                MODIFY_REGISTER_BITS(GPIOA->ODR, 0, 15, Copy_u8PortValue);
                break;
            case IOB:
                MODIFY_REGISTER_BITS(GPIOB->ODR, 0, 15, Copy_u8PortValue);
                break;
            case IOC:
                MODIFY_REGISTER_BITS(GPIOC->ODR, 0, 15, Copy_u8PortValue);
                break;
            default:
                break;
        }
    }
}


/*****************************************************************************/
/* Function Name: GPIO_u8GetPinValue                                         */
/* i/p Arguments: u8 Copy_u8Pin Options (PA0 -> PC15)                        */
/* Return: u8                                                                */
/* Description: This function reads and returns the value of a specified     */
/*              GPIO pin. The pin value can be either LOW (0) or HIGH (1).   */
/*****************************************************************************/

u8   GPIO_u8GetPinValue(u8 Copy_u8Pin)
{
    u8 Local_u8PinValue = 2;
    if ((Copy_u8Pin > PC15))
    {
        /* Do nothing */
    }
    else
    {
        switch (GET_PORT(Copy_u8Pin))
        {
            case IOA:
                Local_u8PinValue = GET_BIT(GPIOA->IDR, GET_PIN(Copy_u8Pin));
                break;

            case IOB:
                Local_u8PinValue = GET_BIT(GPIOB->IDR, GET_PIN(Copy_u8Pin));
                break;

            case IOC:
                Local_u8PinValue = GET_BIT(GPIOC->IDR, GET_PIN(Copy_u8Pin));
                break;

            default:
                break;
        }
    }
    return Local_u8PinValue;
}
