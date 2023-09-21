/*****************************************************/
/*              SWC: SysTick Driver                  */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*              Date: 4 August - 2023                */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SysTick_Interface.h"
#include "SysTick_Private.h"
#include "SysTick_Config.h"

/* Global variable to store the interval mode */
static u8 Global_u8IntervalMode;

/* Function pointer to store the callback function for interval-based operations */
static void (*GpF)(void) = NULL;


/*****************************************************************************/
/* Function Name: STK_voidInit                                               */
/* i/p Arguments: none                                                       */
/* Return: void                                                              */
/* Description: This function initializes the SysTick timer. It configures   */
/*              the SysTick control register and sets the clock source       */
/*              (AHB or AHB/8).                                              */
/*****************************************************************************/

void STK_voidInit(void)
{
    /* Stop Timer */
    CLR_BIT(STK_CTRL_Reg, STK_CTRL_ENABLE);

    /* Stop Exception Request */
    CLR_BIT(STK_CTRL_Reg, STK_CTRL_TICK_INT);

    /* Set SysTick Clock Source */
    #if (STK_CLK_SOURCE == AHB)

        /* Set Clock Source = AHB */
        SET_BIT(STK_CTRL_Reg, STK_CTRL_CLK_SOURCE);

    #elif (STK_CLK_SOURCE == AHB_DIV_BY_8)

        /* Set Clock Source = AHB/8 */
        CLR_BIT(STK_CTRL_Reg, STK_CTRL_CLK_SOURCE);

    #endif
}


/*****************************************************************************/
/* Function Name: STK_voidDelay_us                                           */
/* i/p Arguments: u32 Copy_u32Time - The desired delay time in microseconds  */
/* Return: void                                                              */
/* Description: This function provides a delay in microseconds. It uses the  */
/*              SysTick timer to generate the delay by counting the number   */
/*              of SysTick ticks, it can handle up to 16Mhz for AHB Clock.   */
/*****************************************************************************/

void STK_voidDelay_us(u32 Copy_u32Time)
{
    u16 Local_u16Overflow_Counter = 0;

    if (Copy_u32Time % TICKS_OF_ONE_SECOND != 0)
    {
        /* Set Load Value for the partial microsecond delay */
        STK_LOAD_Reg = (Copy_u32Time % TICKS_OF_ONE_SECOND) * TICKS_DIV_FACTOR;

        /* Start Timer */
        SET_BIT(STK_CTRL_Reg, STK_CTRL_ENABLE);

        /* Poll on the Count Flag to wait for the partial delay */
        while (GET_BIT(STK_CTRL_Reg, STK_CTRL_COUNT_FLAG) == 0);
    }

    /* Start Timer for the remaining time in seconds */
    SET_BIT(STK_CTRL_Reg, STK_CTRL_ENABLE);

    /* Set Load Value for the remaining seconds delay */
    STK_LOAD_Reg = TICKS_OF_ONE_SECOND * TICKS_DIV_FACTOR;

    /* Count to the specified time in seconds */
    while (Local_u16Overflow_Counter != Copy_u32Time / TICKS_OF_ONE_SECOND)
    {
        if (GET_BIT(STK_CTRL_Reg, STK_CTRL_COUNT_FLAG) == 1)
        {
            Local_u16Overflow_Counter++;
        }
    }

    /* Stop Timer */
    STK_voidStopTimer();
}


/*****************************************************************************/
/* Function Name: STK_voidDelay_ms                                           */
/* i/p Arguments: u32 Copy_u32Time - The desired delay time in milliseconds  */
/* Return: void                                                              */
/* Description: This function provides a delay in milliseconds. It uses the  */
/*              SysTick timer to generate the delay by counting the number   */
/*              of SysTick ticks, it can handle up to 16Mhz for AHB Clock.   */
/*****************************************************************************/

void STK_voidDelay_ms(u32 Copy_u32Time)
{
    u16 Local_u16Overflow_Counter = 0;

    if (Copy_u32Time * 1000 % TICKS_OF_ONE_SECOND != 0)
    {
        /* Set Load Value for the partial millisecond delay */
        STK_LOAD_Reg = (Copy_u32Time % TICKS_OF_ONE_SECOND) * TICKS_DIV_FACTOR;

        /* Start Timer */
        SET_BIT(STK_CTRL_Reg, STK_CTRL_ENABLE);

        /* Poll on the Count Flag to wait for the partial delay */
        while (GET_BIT(STK_CTRL_Reg, STK_CTRL_COUNT_FLAG) == 0);
    }

    /* Start Timer for the remaining time in seconds */
    SET_BIT(STK_CTRL_Reg, STK_CTRL_ENABLE);

    /* Set Load Value for the remaining seconds delay */
    STK_LOAD_Reg = TICKS_OF_ONE_SECOND * TICKS_DIV_FACTOR;

    /* Count to the specified time in seconds */
    while (Local_u16Overflow_Counter != Copy_u32Time * 1000 / TICKS_OF_ONE_SECOND)
    {
        if (GET_BIT(STK_CTRL_Reg, STK_CTRL_COUNT_FLAG) == 1)
        {
            Local_u16Overflow_Counter++;
        }
    }

    /* Stop Timer */
    STK_voidStopTimer();
}


/*****************************************************************************/
/* Function Name: STK_voidSetIntervalSingle                                  */
/* i/p Arguments: u32 Copy_u32Time - The desired delay time in microseconds  */
/* i/p Arguments: void (LpF)(void) - Pointer to the callback function to be  */
/*                                   executed after the interval             */
/* Return: void                                                              */
/* Description: This function sets a single interval for a specific time and */
/*              associates a callback function to be executed after the      */
/*              interval elapses.                                            */
/*****************************************************************************/

void STK_voidSetIntervalSingle(u32 Copy_u32Time, void (*LpF)(void))
{
    /* Set Load Value */
    STK_LOAD_Reg = Copy_u32Time;

    /* Start Timer */
    SET_BIT(STK_CTRL_Reg, STK_CTRL_ENABLE);

    /* Set Callback Function */
    GpF = LpF;

    /* Set Interval Mode Flag */
    Global_u8IntervalMode = SINGLE_INTERVAL;

    /* Enable Interrupt */
    SET_BIT(STK_CTRL_Reg, STK_CTRL_TICK_INT);
}


/*****************************************************************************/
/* Function Name: STK_voidSetIntervalPeriodic                                */
/* i/p Arguments: u32 Copy_u32Time - The desired delay time in microseconds  */
/* i/p Arguments: void (LpF)(void) - Pointer to the callback function to be  */
/*                                   executed after each interval            */
/* Return: void                                                              */
/* Description: This function sets a periodic interval for a specific time   */
/*              and associates a callback function to be executed after each */
/*              interval elapses.                                            */
/*****************************************************************************/

void STK_voidSetIntervalPeriodic(u32 Copy_u32Time, void (*LpF)(void))
{
    /* Set Load Value */
    STK_LOAD_Reg = Copy_u32Time;

    /* Start Timer */
    SET_BIT(STK_CTRL_Reg, STK_CTRL_ENABLE);

    /* Set Callback Function */
    GpF = LpF;

    /* Set Interval Mode Flag */
    Global_u8IntervalMode = PERIODIC_INTERVAL;

    /* Enable Interrupt */
    SET_BIT(STK_CTRL_Reg, STK_CTRL_TICK_INT);
}


/*****************************************************************************/
/* Function Name: STK_voidStopTimer                                          */
/* i/p Arguments: none                                                       */
/* Return: void                                                              */
/* Description: This function stops the SysTick timer.                       */
/*****************************************************************************/

/* Function to stop the SysTick timer */
void STK_voidStopTimer(void)
{
    /* Stop Timer */
    CLR_BIT(STK_CTRL_Reg, STK_CTRL_ENABLE);

    /* Stop Exception Request */
    CLR_BIT(STK_CTRL_Reg, STK_CTRL_TICK_INT);

    /* Clear Load and Value Registers */
    STK_LOAD_Reg = 0;
    STK_VAL_Reg = 0;
}


/*****************************************************************************/
/* Function Name: SysTick_Handler                                            */
/* i/p Arguments: none                                                       */
/* Return: void                                                              */
/* Description: This is the SysTick timer interrupt handler.                 */
/*****************************************************************************/

/* SysTick interrupt handler */
void SysTick_Handler(void)
{
    /* Temporary variable to read and clear the Count Flag */
    u8 Local_u8Temp = 0;

    /* Check if it's a single interval mode */
    if (Global_u8IntervalMode == SINGLE_INTERVAL)
    {
        /* Stop Timer in single interval mode */
        STK_voidStopTimer();
    }

    /* Check if a callback function is set */
    if (GpF != NULL)
    {
        /* Call the callback function */
        GpF();
    }

    /* Clear the Count Flag */
    Local_u8Temp = GET_BIT(STK_CTRL_Reg, STK_CTRL_COUNT_FLAG);
}
