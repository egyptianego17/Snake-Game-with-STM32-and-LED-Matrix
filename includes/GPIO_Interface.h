/*****************************************************/
/*                 SWC: GPIO Driver                  */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.1                    */
/*              Date: 28 July - 2023                 */
/*****************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* File Gaurd */
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/* Function Prototypes */
void GPIO_voidDefaultInit();
void GPIO_voidSetPinMode(u8 Copy_u8Pin, u8 Copy_u8PinMode);
void GPIO_voidSetPinType(u8 Copy_u8Pin, u8 Copy_u8PinType);
void GPIO_voidSetPinSpeed(u8 Copy_u8Pin, u8 Copy_u8PinSpeed);
void GPIO_voidSetPinPUPD(u8 Copy_u8Pin, u8 Copy_u8PinPUPDOption);
void GPIO_voidSetPinValue(u8 Copy_u8Pin, u8 Copy_u8PinValue);
void GPIO_voidSetPinValueDirectAccess(u8 Copy_u8Pin, u8 Copy_u8PinValue);
void GPIO_voidSetPortValue(u8 Copy_u8PortId, u16 Copy_u8PortValue);
u8   GPIO_u8GetPinValue(u8 Copy_u8Pin);

/* GPIO Pins */
#define PA0       0 
#define PA1       1
#define PA2       2
#define PA3       3
#define PA4       4
#define PA5       5
#define PA6       6
#define PA7       7
#define PA8       8
#define PA9       9
#define PA10      10
#define PA11      11
#define PA12      12
#define PA13      13
#define PA14      14
#define PA15      15
#define PB0       16
#define PB1       17
#define PB2       18
#define PB3       19
#define PB4       20
#define PB5       21
#define PB6       22
#define PB7       23
#define PB8       24
#define PB9       25
#define PB10      26
#define PB11      27
#define PB12      28
#define PB13      29
#define PB14      30
#define PB15      31
#define PC13      45
#define PC14      46
#define PC15      47

/* GPIO Pin Modes */
#define INPUT      0
#define OUTPUT     1
#define AF         2
#define ANALOG     3

/* GPIO Pin Output Types */
#define OUTPUT_PP  0
#define OUTPUT_OD  1

/* GPIO Pin Output Speeds */
#define OUTPUT_LS  0
#define OUTPUT_MS  1
#define OUTPUT_HS  2
#define OUTPUT_VHS 3

/* GPIO Pin Logic Levels */
#define HIGH       1
#define LOW        0

/* GPIO Pin Value Set Options */
#define SET        0
#define RST        1

/* GPIO Pin Pull-Up/Pull-Down Configurations */
#define FLOATING   0
#define INPUT_PU   1
#define INPUT_PD   2

/* Define for the values for each alternate function */
#define AF0                     0
#define AF1                     1
#define AF2                     2
#define AF3                     3
#define AF4                     4
#define AF5                     5
#define AF6                     6
#define AF7                     7
#define AF8                     8
#define AF9                     9
#define AF10                    10
#define AF11                    11
#define AF12                    12
#define AF13                    13
#define AF14                    14
#define AF15                    15

#endif
