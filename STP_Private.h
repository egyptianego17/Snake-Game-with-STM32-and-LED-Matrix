/*****************************************************/
/*                SWC: STP Driver                    */
/*            Author: Abdulrahman Omar               */
/*                 Version: v 1.0                    */
/*             Date: 28 August - 2023                */
/*****************************************************/


/* File Gaurd */
#ifndef STP_PRIVATE_H
#define STP_PRIVATE_H

/* GPIO Port IDs */
#define IOA   0
#define IOB   1
#define IOC   2

/* GPIO Pin Numbers */
#define PIN0       0
#define PIN1       1
#define PIN2       2
#define PIN3       3
#define PIN4       4
#define PIN5       5
#define PIN6       6
#define PIN7       7
#define PIN8       8
#define PIN9       9
#define PIN10      10
#define PIN11      11
#define PIN12      12
#define PIN13      13
#define PIN14      14
#define PIN15      15

/* Macros to map integer values to port and pin values */
#define GET_PORT(pin) ((pin) / 16)
#define GET_PIN(pin)  ((pin) % 16)

#endif
