#include <iostream>
#include <conio.h>
#include<time.h>
#include<windows.h>

using namespace std;

void draw_ground();
void check_food_status();
void Measure_Values_Then_GOTO_draw_snake_OR_ClearSnake();
void draw_snake_between_2_points(int startingPoint);
void clear_snake_between_2_points(int startingPoint);
void update_tail();
void Alive_or_dead();
void take_input();
void gotoxy(int,int);

#define initial_food_x 15
#define initial_food_y 19

#define initial_snake_tail_x 5
#define initial_snake_head_x 10

#define initial_snake_tail_y 10
#define initial_snake_head_y 10

#define playground_x_width 40
#define playground_y_height 20
#define playground_size (playground_x_width*playground_y_height)

#define snake_tail_location_in_array 0
#define initial_snake_head_location_in_array 1

typedef struct Point{
    int x;
    int y;
} Point;

enum MovementLane {X_LANE, Y_LANE};
enum Direction { UP,DOWN,LEFT,RIGHT};

//INITIAL STARTING VALUES
Point food = {initial_food_x, initial_food_y};

Point snakeTurningPoints[playground_size] = {
    {initial_snake_tail_x,initial_snake_tail_y},
    {initial_snake_head_x,initial_snake_head_y},
};

int head= initial_snake_head_location_in_array;
Direction snakeTailMovingDirection;
MovementLane snakeCalculatedLane;

int m=4,score=0;

int   flag, Length_Between_2_Cordinates,  check,        Length_Sign;
bool  InputFailed=true,breakk=false;
char  show,restart;

int main()
{
    draw_ground();
    while(1)
    {
        check_food_status();
        Measure_Values_Then_GOTO_draw_snake_OR_ClearSnake();
        update_tail();
        Alive_or_dead();
        if(breakk==true)
        {
            break;
        }
        take_input();
    }

    _sleep(2500);
    system("cls");

    draw_ground();
    gotoxy(5,10);
    cout<<"GAME OVER";
    gotoxy(5,11);
    cout<<"YOUR SCORE IS:   "<<score;
    _sleep(5000);

    return 0;
}
//****************************************************************
void draw_ground()
{
    for(int y=0; y<=playground_y_height; y++)
    {
        for(int x=0; x<=playground_x_width; x++)
        {
            // Draw * on border pixels
            if(x==0 || x==playground_x_width || y==0 || y==playground_y_height)
            {
                cout<<'*';
            }
            // Draw empty space on non-border pixels
            else
            {
                cout<<" ";
            }
        }
        cout<<endl;
    }
}
//*******************************************************************
void Measure_Values_Then_GOTO_draw_snake_OR_ClearSnake()
{
    for(int x=1; x<=2; x++)
    {
        for(int j=0; j<head; j++)
        {
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

                // Updated head location and J value
                head--;
                j--;
                continue;
            }


            // Determine direction of snake here
            // x coordinates of adjacent values are same => snake moving in direction of x
            if((snakeTurningPoints[j+1].x - snakeTurningPoints[j].x) ==0)
            {
                snakeCalculatedLane = MovementLane::Y_LANE;
                Length_Between_2_Cordinates = snakeTurningPoints[j+1].y - snakeTurningPoints[j].y;
            }
            // y coordinates of adjacent values are same => snake moving in direction of y
            else if((snakeTurningPoints[j+1].y - snakeTurningPoints[j].y) ==0)
            {
                snakeCalculatedLane = MovementLane::X_LANE;
                Length_Between_2_Cordinates = snakeTurningPoints[j+1].x - snakeTurningPoints[j].x;
            }

            // In initial loop, determine x or y direction in CHECK , determine up-down, or left-right using LENGTH_SIGN

            if(j==0){
                if(snakeCalculatedLane == MovementLane::X_LANE){
                    if(Length_Between_2_Cordinates>0){
                        snakeTailMovingDirection = Direction::RIGHT;
                    }
                    else{
                        snakeTailMovingDirection = Direction::LEFT;
                    }
                }
                else if(snakeCalculatedLane == MovementLane::Y_LANE){
                    if(Length_Between_2_Cordinates>0){
                        snakeTailMovingDirection = Direction::DOWN;
                    }
                    else{
                        snakeTailMovingDirection = Direction::UP;
                    }
                }
            }

            //////////////////////////////////////////////////

            if(x==1)
            {
                draw_snake_between_2_points(j);
            }
            if(x==2)
            {
                clear_snake_between_2_points(j);
            }
        }
        if(x==1)
        {
            _sleep(90);
        }
    }

}
//**********************************************************
void draw_snake_between_2_points(int startingPoint)
{
    int i=0;
    while(1)
    {
        // Goto each Pixel with increments
        if(snakeCalculatedLane == X_LANE)
            gotoxy(snakeTurningPoints[startingPoint].x+i ,snakeTurningPoints[startingPoint].y);
        else if(snakeCalculatedLane == Y_LANE)
            gotoxy(snakeTurningPoints[startingPoint].x, snakeTurningPoints[startingPoint].y+i);

        // Display Head Symbol if it is last line ( head-1 to head) and it is the last point(head)
        if(startingPoint==head-1 && i==Length_Between_2_Cordinates)
            cout<<'$';
        // Display Body Symbol
        else
            cout<<'O';

        // Break if all the pixels between 2 points are drawn
        if(Length_Between_2_Cordinates>0){
            i++;
            if(i==Length_Between_2_Cordinates+1) break;
        }
        if(Length_Between_2_Cordinates<0){
            i--;
            if(i==Length_Between_2_Cordinates-1) break;
        }
    }
}
void clear_snake_between_2_points(int startingPoint)
{

    int i=0;
    while(1)
    {
        // Goto each Pixel with increments
        if(snakeCalculatedLane == X_LANE)
            gotoxy(snakeTurningPoints[startingPoint].x+i ,snakeTurningPoints[startingPoint].y);
        else if(snakeCalculatedLane == Y_LANE)
            gotoxy(snakeTurningPoints[startingPoint].x, snakeTurningPoints[startingPoint].y+i);

        // Clear snake
        cout<<' ';

        // Break if all the pixels between 2 points are drawn
        if(Length_Between_2_Cordinates>0){
            i++;
            if(i==Length_Between_2_Cordinates+1) break;
        }
        if(Length_Between_2_Cordinates<0){
            i--;
            if(i==Length_Between_2_Cordinates-1) break;
        }
    }
}

//*************************************************
void update_tail()
{
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
}
//******************************************************
void take_input()
{
    if(_kbhit())
    {
        InputFailed=false;
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
            InputFailed=true;
        }

        if(InputFailed==false)
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

void check_food_status()
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
        food.x=rand()% (playground_x_width-1) + 1;
        food.y=rand()% (playground_y_height-1) + 1;

        score++;
    }

    gotoxy(food.x,food.y);
    cout<<'%';
}

void Alive_or_dead()
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
        snakeTurningPoints[head].x==playground_x_width ||
        snakeTurningPoints[head].y==0 ||
        snakeTurningPoints[head].y==playground_y_height)
    {
        breakk=true;
    }
}
//***********************************************************************

void gotoxy(int cordx,int cordy)
{
    COORD coord= {cordx,cordy};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
