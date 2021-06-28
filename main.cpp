#include <iostream>
#include <conio.h>
#include<time.h>
#include<windows.h>

using namespace std;

#define INITIAL_FOOD_X 15
#define INITIAL_FOOD_Y 19

#define INITIAL_SNAKE_TAIL_X 5
#define INITIAL_SNAKE_HEAD_X 10

#define INITIAL_SNAKE_TAIL_Y 10
#define INITIAL_SNAKE_HEAD_Y 10

#define PLAYGROUND_X_WIDTH 40
#define PLAYGROUND_Y_HEIGHT 20
#define PLAYGROUND_SIZE (PLAYGROUND_X_WIDTH*PLAYGROUND_Y_HEIGHT)

#define SNAKE_TAIL_LOC 0
#define SNAKE_TAIL_ADJACENT 1

typedef struct Point{
    int x;
    int y;
} Point;

enum MovementLane {X_LANE, Y_LANE};
enum Direction { UP,DOWN,LEFT,RIGHT};

// helper functions
MovementLane calculateSnakeLane(int startingPoint);
int LengthBetween2Cordinates(int startingPoint);
void GoToXY(int,int);

// Game functions
void DrawGround();
void CheckFoodStatus();
void DrawSnake();
void ClearSnake();
void DrawSnakeBetween2Points(int startingPoint);
void ClearSnakeBetween2Points(int startingPoint);
void UpdateTail();
void AliveOrDead();
void TakeInput();

//INITIAL STARTING VALUES
Point food = {INITIAL_FOOD_X, INITIAL_FOOD_Y};

Point snakeTurningPoints[PLAYGROUND_SIZE] = {
    {INITIAL_SNAKE_TAIL_X,INITIAL_SNAKE_TAIL_Y},
    {INITIAL_SNAKE_HEAD_X,INITIAL_SNAKE_HEAD_Y},
};

int head = 1;
Direction snakeTailMovingDirection;
MovementLane snakeCalculatedLane;

int m=4,score=0;

int   flag, lengthBetween2Cordinates, check, lengthSign;
bool  inputFailed=true,breakk=false;
char  show,restart;

int main()
{
    DrawGround();
    while(1)
    {
        CheckFoodStatus();
        DrawSnake();
        ClearSnake();
        UpdateTail();
        AliveOrDead();
        if(breakk==true)
        {
            break;
        }
        TakeInput();
    }

    _sleep(2500);
    system("cls");

    DrawGround();
    GoToXY(5,10);
    cout<<"GAME OVER";
    GoToXY(5,11);
    cout<<"YOUR SCORE IS:   "<<score;
    _sleep(5000);

    return 0;
}
//****************************************************************
void DrawGround()
{
    for(int y=0; y<=PLAYGROUND_Y_HEIGHT; y++)
    {
        for(int x=0; x<=PLAYGROUND_X_WIDTH; x++)
        {
            // Draw * on border pixels
            if(x==0 || x==PLAYGROUND_X_WIDTH || y==0 || y==PLAYGROUND_Y_HEIGHT)
                cout<<'*';
            // Draw empty space on non-border pixels
            else
                cout<<" ";
        }
        cout<<endl;
    }
}
//*******************************************************************
MovementLane calculateSnakeLane(int startingPoint){
    // Determine direction of snake here
    // x coordinates of adjacent values are same => snake moving in direction of x
    if((snakeTurningPoints[startingPoint+1].x - snakeTurningPoints[startingPoint].x) ==0)
    {
        return MovementLane::Y_LANE;
    }

    // y coordinates of adjacent values are same => snake moving in direction of y
    return MovementLane::X_LANE;

}

int LengthBetween2Cordinates(int startingPoint){
    if(calculateSnakeLane(startingPoint) == MovementLane::Y_LANE){
        return snakeTurningPoints[startingPoint+1].y - snakeTurningPoints[startingPoint].y;
    }

    return snakeTurningPoints[startingPoint+1].x - snakeTurningPoints[startingPoint].x;
}

void DrawSnake()
{
    for(int coordinateNumber=0; coordinateNumber<head; coordinateNumber++)
    {
        snakeCalculatedLane = calculateSnakeLane(coordinateNumber);
        lengthBetween2Cordinates = LengthBetween2Cordinates(coordinateNumber);
        DrawSnakeBetween2Points(coordinateNumber);
    }
    _sleep(90);
}
void ClearSnake(){

    for(int coordinateNumber=0; coordinateNumber<head; coordinateNumber++)
    {
        snakeCalculatedLane = calculateSnakeLane(coordinateNumber);
        lengthBetween2Cordinates = LengthBetween2Cordinates(coordinateNumber);
        ClearSnakeBetween2Points(coordinateNumber);
    }
}

//**********************************************************
void DrawSnakeBetween2Points(int startingPoint)
{
    int i=0;
    while(1)
    {
        // Goto each Pixel with increments
        if(snakeCalculatedLane == X_LANE)
            GoToXY(snakeTurningPoints[startingPoint].x+i ,snakeTurningPoints[startingPoint].y);
        else if(snakeCalculatedLane == Y_LANE)
            GoToXY(snakeTurningPoints[startingPoint].x, snakeTurningPoints[startingPoint].y+i);

        // Display Head Symbol if it is last line ( head-1 to head) and it is the last point(head)
        if(startingPoint==head-1 && i==lengthBetween2Cordinates)
            cout<<'$';
        // Display Body Symbol
        else
            cout<<'O';

        // Break if all the pixels between 2 points are drawn
        if(lengthBetween2Cordinates>0){
            i++;
            if(i==lengthBetween2Cordinates+1) break;
        }
        if(lengthBetween2Cordinates<0){
            i--;
            if(i==lengthBetween2Cordinates-1) break;
        }
    }
}
void ClearSnakeBetween2Points(int startingPoint)
{
    int i=0;
    while(1)
    {
        // Goto each Pixel with increments
        if(snakeCalculatedLane == X_LANE)
            GoToXY(snakeTurningPoints[startingPoint].x+i ,snakeTurningPoints[startingPoint].y);
        else if(snakeCalculatedLane == Y_LANE)
            GoToXY(snakeTurningPoints[startingPoint].x, snakeTurningPoints[startingPoint].y+i);

        // Clear snake
        cout<<' ';

        // Break if all the pixels between 2 points are drawn
        if(lengthBetween2Cordinates>0){
            i++;
            if(i==lengthBetween2Cordinates+1) break;
        }
        if(lengthBetween2Cordinates<0){
            i--;
            if(i==lengthBetween2Cordinates-1) break;
        }
    }
}

//*************************************************
void UpdateTail()
{
    MovementLane snakeTailLane = calculateSnakeLane(0);
    int lengthBetweenTailAdjacents = LengthBetween2Cordinates(0);

    if(snakeTailLane == MovementLane::X_LANE){
        if(lengthBetweenTailAdjacents > 0){
            snakeTailMovingDirection = Direction::RIGHT;
        }
        else{
            snakeTailMovingDirection = Direction::LEFT;
        }
    }
    else if(snakeTailLane == MovementLane::Y_LANE){
        if(lengthBetweenTailAdjacents > 0){
            snakeTailMovingDirection = Direction::DOWN;
        }
        else{
            snakeTailMovingDirection = Direction::UP;
        }
    }

    if(snakeTailMovingDirection == UP){
            snakeTurningPoints[0].y--;
    }
    else if(snakeTailMovingDirection == DOWN){
            snakeTurningPoints[0].y++;
    }
    else if(snakeTailMovingDirection == LEFT){

            snakeTurningPoints[0].x--;
    }
    else if(snakeTailMovingDirection == RIGHT){
            snakeTurningPoints[0].x++;
    }

    // If the tail has come to end, remove it by shifting all values in array to left
    // And skip for this turn
    if(snakeTurningPoints[1].x - snakeTurningPoints[0].x ==0 &&
       snakeTurningPoints[1].y - snakeTurningPoints[0].y ==0)
    {
        for(int i=0; i<=head; i++)
        {
            snakeTurningPoints[i].x = snakeTurningPoints[i+1].x;
            snakeTurningPoints[i].y = snakeTurningPoints[i+1].y;
        }

        // Updated head location
        head--;
    }

}
//******************************************************
void TakeInput()
{
    if(_kbhit())
    {
        inputFailed=false;
        snakeTurningPoints[head+1].x = 0;
        snakeTurningPoints[head+1].y = 0;
        char c=getch();

        if     (c=='w' && m!=1 && m!=2)
        {
            m=1;
        }
        else if(c=='s' && m!=2 && m!=1)
        {
            m=2;
        }
        else if(c=='a' && m!=3 && m!=4)
        {
            m=3;
        }
        else if(c=='d' && m!=4 && m!=3)
        {
            m=4;
        }
        else
        {
            inputFailed=true;
        }

        if(inputFailed==false)
        {
            head++;
            snakeTurningPoints[head].x = snakeTurningPoints[head].x + snakeTurningPoints[head-1].x;
            snakeTurningPoints[head].y = snakeTurningPoints[head].y + snakeTurningPoints[head-1].y;
        }
    }

    if     (m==1)
    {
        snakeTurningPoints[head].y--;
    }
    else if(m==2)
    {
        snakeTurningPoints[head].y++;
    }
    else if(m==3)
    {
        snakeTurningPoints[head].x--;
    }
    else
    {
        snakeTurningPoints[head].x++;
    }
}
//***********************************************************************

void CheckFoodStatus()
{
    if(snakeTurningPoints[head].x == food.x && snakeTurningPoints[head].y == food.y)
    {
        if(snakeTurningPoints[1].x > snakeTurningPoints[0].x)
        {
            snakeTurningPoints[0].x--;
        }
        else if(snakeTurningPoints[1].x < snakeTurningPoints[0].x)
        {
            snakeTurningPoints[0].x++;
        }
        else if(snakeTurningPoints[1].y > snakeTurningPoints[0].y)
        {
            snakeTurningPoints[0].y--;
        }
        else if(snakeTurningPoints[1].y < snakeTurningPoints[0].y)
        {
            snakeTurningPoints[0].y++;
        }

        srand(time(NULL));
        food.x=rand()% (PLAYGROUND_X_WIDTH-1) + 1;
        food.y=rand()% (PLAYGROUND_Y_HEIGHT-1) + 1;

        score++;
    }

    GoToXY(food.x,food.y);
    cout<<'%';
}

void AliveOrDead()
{
    for(int i=0; i<head-1; i++)
    {
        if(snakeTurningPoints[head].x >= snakeTurningPoints[i].x &&
           snakeTurningPoints[head].x<=snakeTurningPoints[i+1].x &&
           snakeTurningPoints[head].y==snakeTurningPoints[i].y)
        {
            breakk=true;
        }

        else if(snakeTurningPoints[head].y>=snakeTurningPoints[i].y &&
                snakeTurningPoints[head].y<=snakeTurningPoints[i+1].y &&
                snakeTurningPoints[head].x==snakeTurningPoints[i].x)
        {
            breakk=true;
        }

        else if(snakeTurningPoints[head].x<=snakeTurningPoints[i].x &&
                snakeTurningPoints[head].x>=snakeTurningPoints[i+1].x &&
                snakeTurningPoints[head].y==snakeTurningPoints[i].y)
        {
            breakk=true;
        }

        else if(snakeTurningPoints[head].y<=snakeTurningPoints[i].y &&
                snakeTurningPoints[head].y>=snakeTurningPoints[i+1].y &&
                snakeTurningPoints[head].x==snakeTurningPoints[i].x)
        {
            breakk=true;
        }
    }

    if(snakeTurningPoints[head].x==0 ||
        snakeTurningPoints[head].x==PLAYGROUND_X_WIDTH ||
        snakeTurningPoints[head].y==0 ||
        snakeTurningPoints[head].y==PLAYGROUND_Y_HEIGHT)
    {
        breakk=true;
    }
}
//***********************************************************************

void GoToXY(int cordx,int cordy)
{
    COORD coord= {cordx,cordy};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
