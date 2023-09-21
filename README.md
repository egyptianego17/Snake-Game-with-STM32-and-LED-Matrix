# Snake Game on LED Matrix

Welcome to my Mini-Project! In this README, we'll take a closer look at the technology stack, algorithms, and implementation details that power this classic game.

## Table of Contents
1. [Introduction](#introduction)
2. [Technology Stack](#technology-stack)
3. [Game Algorithm](#game-algorithm)
4. [Implementation](#implementation)
5. [Software Components](#software-components)
6. [Key Functions](#key-functions)
7. [Technical Challenges](#technical-challenges)

## Introduction
The Snake Game on LED Matrix is a fusion of hardware and software, where an 8x8 LED matrix becomes the playground for a classic Snake game. Controlled by external buttons, the game challenges players to navigate a snake to eat food, grow longer, and avoid collisions.

## Technology Stack
Let's begin by exploring the technology stack that forms the backbone of this project:

### Hardware:
- LED Matrix Display: An 8x8 LED matrix serves as the visual output for the game.
- Microcontroller: STM32F401, acts as the brain of the system.
- External Buttons: Four external buttons (up, down, left, right) provide user input.
- Serial to Parallel IC: Facilitates communication between the microcontroller and the LED matrix.

### Software:

## Game Algorithm
The heart of the Snake Game lies in its algorithm. Let's break down how the game operates:

### Initialization:
The game starts with an empty game grid and an empty linked list representing the snake.

### User Input:
The external buttons allow players to control the snake's direction: up, down, left, right.

### Game Loop:
The game runs in a continuous loop, updating the game's state, checking for user input, and rendering the LED matrix display.

### Linked List:
A doubly linked list is used to manage the snake's body. Each node in the list represents a part of the snake.

### Collision Detection:
The algorithm continuously monitors whether the snake collides with itself. A collision ends the game.

### Food Generation:
Food, represented as a dot, appears at random positions on the grid. The algorithm ensures that food does not overlap with the snake's body.

### Scoring:
The player's score is determined by the length of the snake. Eating food increases the snake's length and score.

## Implementation
The implementation details are where the magic happens. Here are some key aspects:

### User Input Interruption:
User input is treated as an interruption to the game loop. When a button is pressed, the microcontroller listens for these interruptions and updates the snake's direction accordingly.

### Direction Control:
The algorithm analyzes interruptions to determine the player's desired direction for the snake. It ensures that the snake cannot reverse direction abruptly, preventing self-collisions.

### Snake Movement:
With the updated direction, the algorithm moves the snake's head in the chosen direction while preserving the tail. The snake's body is effectively shifted forward.

### Food Generation Logic:
To avoid overlap with the snake's body, the algorithm generates food at random, unoccupied positions on the grid.

### Game Over Handling:
When a collision occurs (with the walls or itself), the game ends. A "Game Over" message is displayed, and players have the option to restart.

## Software Components
The software components play a crucial role in driving the functionality of the Snake Game on LED Matrix. These components include:

- `RCC_Interface.h`: Provides functions for controlling the microcontroller's clock settings.
- `GPIO_Interface.h`: Offers GPIO manipulation functions for interfacing with external buttons.
- `SysTick_Interface.h`: Manages the system tick timer for timing and delays.
- `NVIC_Interface.h`: Handles interrupt controller configuration.
- `EXTI_Interface.h`: Manages external interrupts.
- `LEDMTRX_Interface.h`: Interfaces with the LED matrix for display control.
- `CHARACTERS.h`: Contains character data for rendering text on the LED matrix.

## Key Functions

### Linked List Operations
The core of the game revolves around a doubly linked list that represents the snake's body. Let's explore the functions responsible for managing this linked list:

- `insertFront(struct Node** head, u8 row, u8 col)`: This function inserts a new node at the front of the linked list, effectively adding a new segment to the snake's head.

- `insertAfter(struct Node* prevNode, u8 row, u8 col)`: When the snake moves, this function inserts a new node after the previous node, extending the snake's body.

- `insertEnd(struct Node** head, u8 row, u8 col)`: To make the snake longer, this function adds a new node at the end of the linked list, representing the tail.

- `deleteNode(struct Node** head, struct Node* delNode)`: When the snake moves, this function removes a node from the linked list to simulate the snake's forward motion.

- `deleteHead(struct Node** head)`: This function deletes the current head node, effectively shortening the snake as it moves.

- `getNodeByIndex(struct Node* head, u8 index)`: It retrieves a node by its index in the linked list, allowing for efficient traversal and manipulation.

- `getLength(struct Node* head)`: This function calculates and returns the length of the linked list, which directly corresponds to the snake's length.

### Display Functions
The LED matrix display plays a vital role in conveying game information and feedback. These functions are responsible for creating engaging visual effects:

- `displayString(u8 string[][8], u8 stringSize, Direction direction)`: This function scrolls a given string (such as "Start" or "Game Over") on the LED matrix display. It handles animation by shifting characters in the chosen direction, providing a visually appealing user experience.

### Game Logic Functions
The game's core logic and mechanics are driven by these essential functions:

- `moveSnake()`: This function handles the snake's movement based on its current direction. It inserts a new node at the front to simulate forward motion and deletes the tail to maintain the snake's length.

- `checkNext()`: As the game progresses, this function continuously checks the consequences of the snake's next move. It detects collisions with itself or food, triggering game events accordingly.

- `startGame()`: At the game's outset, this function initializes the game state, displays the "Start" message, and sets up the snake's initial position.

- `generateRandomFood()`: To keep the game exciting, this function generates food at random positions on the grid while ensuring it does not overlap with the snake's body.

- `restart()`: When the game ends, this function clears the existing snake and initializes a new game, allowing the player to try again.

Understanding the intricacies of these functions opens up a world of possibilities for learning, experimentation, and even extending the game's features. Dive into the code and explore how these functions come together to create a classic game with a modern twist.

Thank you for delving into the detailed functionality of the Snake Game on LED Matrix project. Enjoy exploring and tinkering with the code to uncover the secrets behind this tech-savvy recreation of a timeless classic!
