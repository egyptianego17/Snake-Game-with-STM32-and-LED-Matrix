#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "SysTick_Interface.h"
#include "NVIC_Interface.h"
#include "EXTI_Interface.h"
#include "LEDMTRX_Interface.h"
#include "CHARACTERS.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define DIFFICULTY  15

/* Enum to represent directions */
typedef enum {
    RIGHT = 0, LEFT = 1, UP = 2, DOWN = 3
} Direction;

/* Static array to represent the game frame */
static u8 GameFrame[8] = {0};

/* LED matrix Characters */
static u8 GameOver[8][8] = {
    {G}, {A}, {M}, {E}, {O}, {V}, {E}, {R}
};

static u8 Start[5][8] = {
    {S}, {T}, {A}, {R}, {T}
};

/* Variable to store the current direction of the snake */
static Direction currentDirection = RIGHT;

/* Node structure for a doubly linked list to represent the snake */
struct Node {
    u8 row;
    u8 col;
    struct Node* next;
    struct Node* prev;
};

struct Point {
    u8 row;
    u8 col;
};

/* Structure object to represent the current position of the snake food */
struct Point* food = NULL;

/* Initialize linkedlist head */
struct Node* head = NULL;

/* Variable to store the remaining time to appear the food on random position */
static u8 foodTimer = 0;

/* Function prototypes for the linked list operations */
struct Node* getNodeByIndex(struct Node* head, u8 index);
void insertFront(struct Node** head, u8 row, u8 col);
void insertAfter(struct Node* prevNode, u8 row, u8 col);
void insertEnd(struct Node** head, u8 row, u8 col);
void deleteNode(struct Node** head, struct Node* delNode);
void deleteHead(struct Node** head);
void generateRandomFood(void);
u8 getLength(struct Node* head);

/* Function prototype for displaying a scrolling string on the LED matrix */
void displayString(u8 string[][8], u8 stringSize, Direction direction);

/* Function prototypes for the game operations */
static inline void moveSnake(void);
static inline void checkNext(void);
static inline void startGame(void);
static inline void drawFrame(void);
static inline void gameOver(void);
static inline void restart(void);

/* Functions to handle user input (setting direction) */
void setDirectionDown(void);
void setDirectionUp(void);
void setDirectionLeft(void);
void setDirectionRight(void);

/* Function to initialize EXTI and related configurations */
static inline void initEXTI(void);

int main() 
{
    /* Initialize the system clock */
    RCC_voidInitSysClk();

    /* Enable GPIO peripheral clocks for the relevant ports */
    RCC_voidEnablePeripheralClk(AHB1, RCC_AHB1ENR_GPIOAEN);
    RCC_voidEnablePeripheralClk(AHB1, RCC_AHB1ENR_GPIOBEN);
    RCC_voidEnablePeripheralClk(AHB1, RCC_AHB1ENR_GPIOCEN);
    RCC_voidEnablePeripheralClk(APB2, RCC_APB2ENR_SYSCFGEN);

    /* Initialize the SysTick timer */
    STK_voidInit();

    /* Initialize EXTI & NVIC Configuration */
    initEXTI();

    /* Initialize the LED matrix */
    LEDMTRX_voidInit();

    startGame();

    while (1) 
    {
        /* Update the game frame based on the snake's position */
        drawFrame();

        /* Display the game frame (repeat for smooth scrolling) */
        for (u8 repeat = 0; repeat < 10; repeat++) 
        {
            LEDMTRX_voidSendFrame(GameFrame);
        }

        /* Move the snake based on the current direction */
        moveSnake();
        checkNext();
    }

    return 0;
}

/* Function to initialize EXTI and related configurations */
static inline void initEXTI(void) 
{
    /* Configure GPIO pins as inputs and enable pull-up resistors */
    GPIO_voidSetPinMode(PB0, INPUT);
    GPIO_voidSetPinMode(PB1, INPUT);
    GPIO_voidSetPinMode(PB2, INPUT);
    GPIO_voidSetPinMode(PB3, INPUT);
    GPIO_voidSetPinPUPD(PB0, INPUT_PU);
    GPIO_voidSetPinPUPD(PB1, INPUT_PU);
    GPIO_voidSetPinPUPD(PB2, INPUT_PU);
    GPIO_voidSetPinPUPD(PB3, INPUT_PU);

    /* Enable Interrupts for EXTI lines */
    NVIC_EnableIRQ(EXTI0);
    NVIC_EnableIRQ(EXTI1);
    NVIC_EnableIRQ(EXTI2);
    NVIC_EnableIRQ(EXTI3);

    /* Configure EXTI lines for falling edge triggers on corresponding pins */
    EXTI_voidInit(EXTI_EXTI0, EXTI_FALLING_EDGE);
    EXTI_voidEXTIConfig(EXTI_EXTI0, EXTI_PB);
    EXTI_voidEnable(EXTI_EXTI0);

    EXTI_voidInit(EXTI_EXTI1, EXTI_FALLING_EDGE);
    EXTI_voidEXTIConfig(EXTI_EXTI1, EXTI_PB);
    EXTI_voidEnable(EXTI_EXTI1);

    EXTI_voidInit(EXTI_EXTI2, EXTI_FALLING_EDGE);
    EXTI_voidEXTIConfig(EXTI_EXTI2, EXTI_PB);
    EXTI_voidEnable(EXTI_EXTI2);

    EXTI_voidInit(EXTI_EXTI3, EXTI_FALLING_EDGE);
    EXTI_voidEXTIConfig(EXTI_EXTI3, EXTI_PB);
    EXTI_voidEnable(EXTI_EXTI3);

    /* Set callback functions for EXTI interrupts */
    EXTI_voidSetCallBack(EXTI_EXTI0, setDirectionDown);
    EXTI_voidSetCallBack(EXTI_EXTI1, setDirectionUp);
    EXTI_voidSetCallBack(EXTI_EXTI2, setDirectionLeft);
    EXTI_voidSetCallBack(EXTI_EXTI3, setDirectionRight);
}

/* Function to update the game frame based on the snake's position and food */
static inline void drawFrame(void) 
{
    /* Clear the game frame for the next frame by setting all elements to 0 */
    for (u8 counter = 0; counter < 8; counter++) 
    {
        GameFrame[counter] = 0;
    }

    /* Iterate through the linked list representing the snake's body */
    u8 length = getLength(head);
    for (u8 counter = 0; counter < length; counter++) 
    {
        /* Set the corresponding bit in the game frame to represent the snake's body */
        struct Node* node = getNodeByIndex(head, counter);
        SET_BIT(GameFrame[node->row], node->col);
    }

    /* Check if it's time to generate a new food item */
    if (foodTimer == DIFFICULTY) 
    {
        generateRandomFood(); // Generate a new food item at a random position
    }

    /* Update the game frame with the position of the food */
    SET_BIT(GameFrame[food->row], food->col);
    foodTimer++;
}

/* Functions to handle user input for setting the snake's direction */
void setDirectionDown(void) 
{
    if (currentDirection != UP) 
    {
        currentDirection = DOWN; // Change the snake's direction to "down" if not currently moving "up"
    }
}

void setDirectionUp(void) 
{
    if (currentDirection != DOWN) 
    {
        currentDirection = UP; // Change the snake's direction to "up" if not currently moving "down"
    }
}

void setDirectionLeft(void) 
{
    if (currentDirection != RIGHT) 
    {
        currentDirection = LEFT; // Change the snake's direction to "left" if not currently moving "right"
    }
}

void setDirectionRight(void) 
{
    if (currentDirection != LEFT) 
    {
        currentDirection = RIGHT; // Change the snake's direction to "right" if not currently moving "left"
    }
}

/* Function to check the consequences of the snake's next move */
static inline void checkNext(void) 
{
    /* Get the last node (head) of the snake */
    u8 length = getLength(head);
    struct Node* snakeHead = getNodeByIndex(head, length - 1);
    struct Node* node = NULL;
    u8 row = snakeHead->row;
    u8 col = snakeHead->col;

    /* Check the outcome of the next move (Move - Eat Food - Eat Itself) */
    for (u8 counter = 0; counter < length; counter++) 
    {
        node = getNodeByIndex(head, counter);
        if (counter == (length - 1)) 
        {
            continue; // Skip the last element (the head) during checking
        } 
        else if ((row == food->row) && (col == food->col)) 
        {
            /* If the next step is food, add a new node to the snake and generate a new random food item */
            insertEnd(&head, row, col);
            generateRandomFood();
        } 
        else if ((row == node->row) && (col == node->col)) 
        {
            /* If the next step is the snake's body, the game is over, and it's time to restart */
            gameOver();
            restart();
        }
    }
}

/* Function to handle the game over scenario */
void gameOver(void) 
{
    /* Blink the LED Matrix to signal the end of the game */
    for (u8 blink = 0; blink < 4; blink++) 
    {
        for (u8 repeat = 0; repeat < 20; repeat++) 
        {
            LEDMTRX_voidSendFrame(GameFrame);
        }
        STK_voidDelay_us(400000); // Delay to create a blinking effect
    }

    /* Display the "GameOver" message on the LED Matrix */
    displayString(GameOver, 8, LEFT);
}

/* Function to generate a random position for food */
void generateRandomFood(void) 
{
    /* Reset the food timer to count from 0 when the period elapses or when the snake eats food */
    foodTimer = 0;
    u8 length = getLength(head);
    struct Node* node = NULL;

    /* Create a 2D array to store occupied positions by the snake's body */
    u8 occupied[8][8] = {0};

    /* Mark occupied positions based on the snake's body */
    for (u8 counter = 0; counter < length; counter++) 
    {
        node = getNodeByIndex(head, counter);
        occupied[node->row][node->col] = 1;
    }

    u8 row, col;
    /* Check and select a new food position that is not occupied by the snake */
    do 
    {
        row = (u8)(rand() % 8);
        col = (u8)(rand() % 8);
    } while (occupied[row][col] == 1);

    /* Update the food's position */
    food->row = row;
    food->col = col;
}

/* Function to start a new game */
static inline void startGame(void) 
{
    /* Display the "Start" message on the LED Matrix */
    displayString(Start, 5, LEFT);

    /* Initialize the snake and food with initial positions */
    insertEnd(&head, 1, 2);
    insertEnd(&head, 1, 3);

    generateRandomFood(); // Generate the initial food item
}

/* Function to restart the game */
static inline void restart(void) 
{
    u8 length = getLength(head);
    /* Delete all existing nodes to clear the snake's body */
    for (u8 counter = 0; counter < length; counter++) 
    {
        deleteHead(&head);
    }
    
    /* Initialize the snake with new initial positions */
    insertEnd(&head, 1, 2);
    insertEnd(&head, 1, 3);
}

/* Function to move the snake based on its current direction */
static inline void moveSnake(void) 
{
    /* Get the last node (tail) of the snake */
    struct Node* node = getNodeByIndex(head, getLength(head) - 1);
    u8 row = node->row;
    u8 col = node->col;

    /* Move the snake based on the current direction */
    switch (currentDirection) 
    {
        case UP:
            /* If the next step is not the edge of the frame, move normally */
            if (row < 7) 
            {
                insertEnd(&head, row + 1, col);
                SET_BIT(GameFrame[row + 1], col);
            } 
            /* If the next step is the edge of the frame, start from the opposite edge */
            else if (row == 7) 
            {
                insertEnd(&head, 0, col);
                SET_BIT(GameFrame[0], col);
            }
            break;
        case DOWN:
            if (row > 0) 
            {
                insertEnd(&head, row - 1, col);
                SET_BIT(GameFrame[row - 1], col);
            } 
            else if (row == 0) 
            {
                insertEnd(&head, 7, col);
                SET_BIT(GameFrame[7], col);
            }
            break;
        case LEFT:
            if (col > 0) 
            {
                insertEnd(&head, row, col - 1);
                SET_BIT(GameFrame[row], col - 1);
            } 
            else if (col == 0) 
            {
                insertEnd(&head, row, 7);
                SET_BIT(GameFrame[row], 7);
            }
            break;
        case RIGHT:
            if (col < 7) 
            {
                insertEnd(&head, row, col + 1);
                SET_BIT(GameFrame[row], col + 1);
            } 
            else if (col == 7) 
            {
                insertEnd(&head, row, 0);
                SET_BIT(GameFrame[row], 0);
            }
            break;
        default:
            break;
    }

    /* Remove the old head (front) of the snake to simulate movement */
    deleteHead(&head);
}

/* Function to display a scrolling string on the LED matrix */
void displayString(u8 string[][8], u8 stringSize, Direction direction) 
{
    /* An array to hold the shifted data for each column */
    static u8 ShiftedData[8] = {0};

    /* Loop through each column in the Characters array */
    for (u8 col = 0; col < stringSize; col++) 
    {
        /* Loop through each row to shift the character data */
        for (u8 shift = 0; shift < 8; shift++) 
        {
            /* Loop through each Byte value within a row */
            for (u8 BytePos = 0; BytePos < 8; BytePos++) 
            {
                /* Combining two row values of characters data */
                u16 frameData;

                /* When it's the last char then skip the next one */
                if (col == stringSize - 1) 
                {
                    /* Shift the frame based on the direction, while LEFT  = shift by 8
                       RIGHT = shift by 0 */
                    frameData = (string[col][BytePos] << direction * 8);
                } else 
                {
                    /* Arrange the 2 chars in frame bits based on direction, while LEFT  = First in MSB, Second in LSBs
                                                                                   RIGHT = First in LSB, Second in MSBs    */
                    frameData = (string[col][BytePos] << direction * 8) |
                                ((string[col + 1][BytePos]) << (!direction) * 8);
                }

                /* Shift the data by the current shift value and based on direction */
                if (direction == LEFT) 
                {
                    ShiftedData[BytePos] = GET_BITS(frameData << shift, 8, 15);
                } else if (direction == RIGHT) 
                {
                    ShiftedData[BytePos] = GET_BITS(frameData >> shift, 0, 7);
                }
            }

            /* Display the shifted data for a short period (repeat for smooth scrolling) */
            for (u8 repeat = 0; repeat < 5; repeat++) 
            {
                LEDMTRX_voidSendFrame(ShiftedData);
            }
        }
    }
}

/* Insert node at the front of the doubly linked list */
void insertFront(struct Node** head, u8 row, u8 col)
{
    /* Allocate memory for a new node */
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    /* Assign data to the new node */
    newNode->row = row;
    newNode->col = col;

    /* Make the new node the head */
    newNode->next = (*head);

    /* Assign NULL to the previous pointer */
    newNode->prev = NULL;

    /* Update the previous pointer of the previous head (if it exists) */
    if ((*head) != NULL)
        (*head)->prev = newNode;

    /* Update the head pointer to point to the new node */
    (*head) = newNode;
}

/* Insert a node after a specific node in the doubly linked list */
void insertAfter(struct Node* prevNode, u8 row, u8 col) 
{
    /* Check if the previous node is NULL */
    if (prevNode == NULL) 
    {
        return;
    }

    /* Allocate memory for a new node */
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    /* Assign data to the new node */
    newNode->row = row;
    newNode->col = col;

    /* Update the next and previous pointers of the new node */
    newNode->next = prevNode->next;
    newNode->prev = prevNode;

    /* Update the next and previous pointers of the surrounding nodes */
    if (prevNode->next != NULL)
        prevNode->next->prev = newNode;

    prevNode->next = newNode;
}

/* Insert a new node at the end of the doubly linked list */
void insertEnd(struct Node** head, u8 row, u8 col) 
{
    /* Allocate memory for a new node */
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    /* Assign data to the new node */
    newNode->row = row;
    newNode->col = col;

    /* Assign NULL to the next pointer */
    newNode->next = NULL;

    /* Store the head node temporarily (for later use) */
    struct Node* temp = *head;

    /* If the linked list is empty, make the new node the head node */
    if (*head == NULL) 
    {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    /* If the linked list is not empty, traverse to the end of the linked list */
    while (temp->next != NULL)
        temp = temp->next;

    /* Now, temp points to the last node of the linked list */

    /* Update the next pointer of the last node (temp) to point to the new node */
    temp->next = newNode;

    /* Update the previous pointer of the new node to point to the last node (temp) */
    newNode->prev = temp;
}

/* Delete a node from the doubly linked list */
void deleteNode(struct Node** head, struct Node* delNode)
{
    /* Check if head or delNode is NULL; deletion is not possible in these cases */
    if (*head == NULL || delNode == NULL)
        return;
  
    /* If delNode is the head node, update the head pointer to the next node */
    if (*head == delNode)
        *head = delNode->next;
  
    /* If delNode is not the last node, update the previous pointer of the node next to delNode */
    if (delNode->next != NULL)
        delNode->next->prev = delNode->prev;
  
    /* If delNode is not the first node, update the next pointer of the previous node to the next node of delNode */
    if (delNode->prev != NULL)
        delNode->prev->next = delNode->next;
  
    /* Free the memory of delNode */
    free(delNode);
}

/* Delete the current head node and update the head pointer */
void deleteHead(struct Node** head) 
{
    if (*head == NULL) 
    {
        return; // No need to delete if the list is empty.
    }

    /* Save a reference to the current head node */
    struct Node* temp = *head;

    /* Update the head pointer to point to the next node */
    *head = (*head)->next;

    /* If the new head node exists, update its previous pointer */
    if (*head != NULL) 
    {
        (*head)->prev = NULL;
    }

    /* Free the memory of the old head node */
    free(temp);
}

/* Get a node by index in the doubly linked list */
struct Node* getNodeByIndex(struct Node* head, u8 index) 
{
    if (head == NULL) 
    {
        return NULL; // Return NULL if the list is empty or the index is negative.
    }

    struct Node* current = head;
    u8 currentIndex = 0;

    while (current != NULL) 
    {
        if (currentIndex == index) 
        {
            return current; // Return the node when the desired index is reached.
        }

        current = current->next;
        currentIndex++;
    }

    return NULL; // Return NULL if the index is out of bounds.
}

/* Get the length of the doubly linked list */
u8 getLength(struct Node* head) 
{
    u8 length = 0;
    struct Node* current = head;

    while (current != NULL) 
    {
        length++;
        current = current->next;
    }

    return length;
}
