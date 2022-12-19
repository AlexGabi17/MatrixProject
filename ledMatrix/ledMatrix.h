#ifndef _LEDMATRIX_
#define _LEDMATRIX_

#include "../deque/deque.h"
#include "../menu/init.h"

short int refresh_time_matrix = 600; // should be change during the game
const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;
const byte matrixSize = 8;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No.DRIVER
byte matrixBrightness = 5;
byte matrixGameLogic[matrixSize][matrixSize];
unsigned long lastRefreshLedMatrix = 0;
byte startGame = 0;

byte foodX;
byte foodY;
byte foodAte = 0;      // must be generated new food position
byte increaseTail = 0; // set to False
// Snake logic variables

byte direction; // 0 -> UP, 1 -> DOWN, 2 -> LEFT, 3 -> RIGHT
                // The direction at the beginning of the game is UP. will be set in initSnake routine

int snakeLength()
{
    return snakePositionsDeque.count();
}
void addHead(snakePosition head)
{
    matrixGameLogic[head.x][head.y] = 1;
    snakePositionsDeque.push_front(head);
}
addTail(snakePosition tail)
{
    matrixGameLogic[tail.x][tail.y] = 1;
    snakePositionsDeque.push_back(tail);
}
void cutTail()
{
    snakePosition position;
    position = snakePositionsDeque.pop_back();
    matrixGameLogic[position.x][position.y] = 0;
}
void releaseFood()
{
    matrixGameLogic[foodX][foodY] = 1;
    // foodAte = 1;
}
void eatFood()
{
    matrixGameLogic[foodX][foodY] = 0;
    foodAte = 0;
    // TODO increase snake's tail
}
void initSnake()
{
    matrixGameLogic[5][2] = 1; // de aici incepe sarpili
    matrixGameLogic[6][2] = 1;
    matrixGameLogic[7][2] = 1;

    struct snakePosition startPos;
    startPos.x = 7;
    startPos.y = 2;
    snakePositionsDeque.push_front(startPos);

    startPos.x = 6;
    startPos.y = 2;
    snakePositionsDeque.push_front(startPos);

    startPos.x = 5;
    startPos.y = 2;
    snakePositionsDeque.push_front(startPos);
    direction = 1;
    startGame = 1;
}
void ledMatrixSetup()
{

    for (int row = 0; row < matrixSize; row++)
    {
        for (int col = 0; col < matrixSize; col++)
        {
            matrixGameLogic[row][col] = 0;
        }
    }
    lc.shutdown(0, false);                // turn off power saving, enables display
    lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
    lc.clearDisplay(0);                   // clear screen
}
byte verifySnakePositions(byte posX, byte posY)
{
    snakePosition *positions;
    positions = snakePositionsDeque.to_array();
    for (int index = 0; index < snakePositionsDeque.count(); index++)
    {
        // debug
        // Serial.println(index + ", X= " + String(positions[index].x) + ", Y= " + String(positions[index].y));
        if (posX == positions[index].x && posY == positions[index].y)
        {
            return 0;
        }
    }
    return 1;
}

void resetMatrix()
{
    for (int row = 0; row < matrixSize; row++)
    {
        for (int col = 0; col < matrixSize; col++)
        {
            matrixGameLogic[row][col] = 0;
        }
    }
}
void clearSnakeMemory() // free memory used for snake position's for last game
{
    while (snakePositionsDeque.count())
    {
        snakePositionsDeque.pop_back();
    }
}
void updateSnake()
{

    short int movementPosition = getMovementPosition();

    if (movementPosition != -1)
    {
        if (direction == 1 && movementPosition != 0)
        {
            direction = movementPosition;
        }
        if (direction == 0 && movementPosition != 1)
        {
            direction = movementPosition;
        }
        if (direction == 2 && movementPosition != 3)
        {
            direction = movementPosition;
        }
        if (direction == 3 && movementPosition != 2)
        {
            direction = movementPosition;
        }
        // Serial.println(movementPosition);
    }

    snakePosition head = snakePositionsDeque.peek_front();
    snakePosition newHead;
    switch (direction)
    {
    case 0:
        newHead.x = head.x + 1;
        newHead.y = head.y;
        break;
    case 1:
        newHead.x = head.x - 1;
        newHead.y = head.y;
        break;
    case 2:
        newHead.x = head.x;
        newHead.y = head.y + 1;
        break;
    case 3:
        newHead.x = head.x;
        newHead.y = head.y - 1;
        break;
    default:
        newHead.x = head.x + 1;
        newHead.y = head.y;
    }

    // generate food
    byte okFoodValues = 0;
    byte newFoodX, newFoodY;
    Serial.println("foodAte = " + String(foodAte));

    if (foodAte == 0)
    {
        foodAte = 1;
        while (!okFoodValues)
        {
            // randomSeed(newHead.x);
            // newFoodX = foodPositionsX[indexPositions]; // generating pseudo-random values
            // newFoodY = foodPositionsY[indexPositions];
            newFoodX = random(1, 6);
            newFoodY = random(1, 6);
            if (verifySnakePositions(newFoodX, newFoodY)) // verify not to spawn food on the snake :)
            {
                if (newFoodX != newHead.x && newFoodY != newHead.y)
                {
                    // Serial.println(newFoodX, newFoodY);

                    okFoodValues = 1;
                }
            }
        }
        foodX = newFoodX;
        foodY = newFoodY;
    }
    if (newHead.x == foodX && newHead.y == foodY)
    {
        eatFood();
        foodX = -1;
        foodY = -1;
        foodAte = 0;
        increaseTail = 1;
    }

    // Serial.println("Food = " + String(foodX) + ", " + String(fo odY));
    if ((newHead.x < 0 || newHead.x > 7 || newHead.y < 0 || newHead.y > 7) || (!verifySnakePositions(newHead.x, newHead.y)))
    {
        // move to LOST state of menu
        menuState = LOST;
        lastSwitch = millis();
        startGame = !startGame;
        clearSnakeMemory();
    }
    else
    {
        releaseFood();
        addHead(newHead);
        if (increaseTail == 0)
        {
            cutTail();
        }
        increaseTail = 0;
    }
}
void updateMatrix()
{

    if (!startGame)
    {
        resetMatrix();

        initSnake();
        delay(50); // give user the time to prepare for game
    }

    if (millis() - lastRefreshLedMatrix >= refresh_time_matrix)
    {
        updateSnake();
        for (int row = 0; row < matrixSize; row++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                lc.setLed(0, row, col, matrixGameLogic[row][col]);
            }
        }
        lastRefreshLedMatrix = millis();
    }
}
#endif