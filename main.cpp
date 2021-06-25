#include <iostream>
#include <conio.h>
#include<time.h>
#include<windows.h>

using namespace std;

void draw_ground();
void foodcheck();
void Measure_Values_Then_GOTO_draw_snake_OR_ClearSnake();
void draw_snake_OR_ClearSnake(int j,char show,int x);
void update_tail();
void Alive_or_dead();
void take_input();

void gotoxy(int,int);

int   foodx=15,foody=19,head=1,m=4,score=0; //INITIAL STARTING VALUES
int   cordx[800]= {10,10},cordy[800]= {5,10};

int   flag, Length_Between_2_Cordinates,  check,        Length_Sign;
bool  InputFailed=true,breakk=false;
char  show,restart;

int main()
{
    draw_ground();
    while(1)
    {
        foodcheck();
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
    gotoxy(10,5);
    cout<<"GAME OVER";
    gotoxy(11,5);
    cout<<"YOUR SCORE IS:   "<<score;
    _sleep(5000);

    return 0;
}
//****************************************************************
void draw_ground()
{
    for(int x=0; x<=20; x++)
    {
        for(int y=0; y<=40; y++)
        {
            if(x==0 || x==20 || y==0 || y==40)
            {
                cout<<'*';
            }
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
            if(cordx[1]-cordx[0]==0 && cordy[1]-cordy[0]==0)
            {
                for(int i=0; i<=head; i++)
                {
                    cordx[i]=cordx[i+1];
                    cordy[i]=cordy[i+1];
                }

                head--;
                j--;
                continue;
            }


            if(cordx[j+1]-cordx[j]==0)
            {
                Length_Between_2_Cordinates=cordy[j+1]-cordy[j];
                flag=1;
            }
            else if(cordy[j+1]-cordy[j]==0)
            {
                Length_Between_2_Cordinates=cordx[j+1]-cordx[j];
                flag=2;
            }
            //////////////////////////////////////////////////
            if(j==0 && flag==1)
            {
                check=1;
                Length_Sign=Length_Between_2_Cordinates;
            }
            if(j==0 && flag==2)
            {
                check=2;
                Length_Sign=Length_Between_2_Cordinates;
            }
            //////////////////////////////////////////////////

            if(x==1)
            {
                show='O';
                draw_snake_OR_ClearSnake(j,show,x);
            }
            if(x==2)
            {
                show=' ';
                draw_snake_OR_ClearSnake(j,show,x);
            }
        }
        if(x==1)
        {
            _sleep(90);
        }
    }

}
//**********************************************************
void draw_snake_OR_ClearSnake(int j,char show,int x)
{
    int i=0;

    while(1)
    {
        if(flag==1)
        {
            gotoxy(cordx[j],cordy[j]+i);
        }
        else if(flag==2)
        {
            gotoxy(cordx[j]+i,cordy[j]);
        }

        if(x==1 && j==head-1 && i==Length_Between_2_Cordinates)
        {
            cout<<'$';
        }
        else
        {
            cout<<show;
        }

        if(Length_Between_2_Cordinates>0)
        {
            i++;
            if(i==Length_Between_2_Cordinates+1)
            {
                break;
            }
        }
        if(Length_Between_2_Cordinates<0)
        {
            i--;
            if(i==Length_Between_2_Cordinates-1)
            {
                break;
            }
        }
    }
}
//*************************************************
void update_tail()
{
    if(check==1)
    {
        if(Length_Sign>0)
        {
            cordy[0]++;
        }
        else
        {
            cordy[0]--;
        }
    }
    else if(check==2)
    {
        if(Length_Sign>0)
        {
            cordx[0]++;
        }
        else
        {
            cordx[0]--;
        }
    }
}
//******************************************************
void take_input()
{
    if(_kbhit())
    {
        InputFailed=false;
        cordx[head+1]=0;
        cordy[head+1]=0;
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
            cordx[head]=cordx[head]+cordx[head-1];
            cordy[head]=cordy[head]+cordy[head-1];
        }
    }

    if     (m==1)
    {
        cordx[head]--;
    }
    else if(m==2)
    {
        cordx[head]++;
    }
    else if(m==3)
    {
        cordy[head]--;
    }
    else
    {
        cordy[head]++;
    }
}
//***********************************************************************

void foodcheck()
{
    if(cordx[head]==foodx && cordy[head]==foody)
    {
        if(cordx[1]>cordx[0])
        {
            cordx[0]--;
        }
        else if(cordx[1]<cordx[0])
        {
            cordx[0]++;
        }
        else if(cordy[1]>cordy[0])
        {
            cordy[0]--;
        }
        else if(cordy[1]<cordy[0])
        {
            cordy[0]++;
        }

        srand(time(NULL));
        foodx=rand()%19+1;
        foody=rand()%39+1;

        score++;
    }

    gotoxy(foodx,foody);
    cout<<'%';
}

void Alive_or_dead()
{
    for(int i=0; i<head-1; i++)
    {
        if     (cordx[head]>=cordx[i] && cordx[head]<=cordx[i+1] && cordy[head]==cordy[i])       breakk=true;

        else if(cordy[head]>=cordy[i] && cordy[head]<=cordy[i+1] && cordx[head]==cordx[i])       breakk=true;

        else if(cordx[head]<=cordx[i] && cordx[head]>=cordx[i+1] && cordy[head]==cordy[i])       breakk=true;

        else if(cordy[head]<=cordy[i] && cordy[head]>=cordy[i+1] && cordx[head]==cordx[i])       breakk=true;
    }

    if(cordx[head]==0 || cordx[head]==20 || cordy[head]==0 || cordy[head]==40)
    {
        breakk=true;
    }
}
//***********************************************************************

void gotoxy(int cordx,int cordy)
{
    COORD coord= {cordy,cordx};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
