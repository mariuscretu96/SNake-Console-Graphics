#include <vector>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

class Snake
{
private:
    int x,z,Dollars,y,Bonus,time,tail;
    char *map;
    bool L,R,D,U,A;
    std::vector <int> past;

public:
    Snake()
    {
        map = new char [2000];
        L = 0;
        R = 1;
        D = 0;
        U = 0;
        A = 0;
        tail = 1;
        x = 1000;
        Dollars = 0;
        Bonus = 0;
        time = 40;
        z = 1;
	}

    ~Snake()
    {
        delete [] map;
    }

    void Graphics ();
    void GameLogic();
    void KEYBOARD ();
    void Pineapple();
    int GameOver ();
    void Start();
    friend void clearscreen();
    friend void sp();
    friend void s();
};
////////////////////////////////////////////////////////////////////////////////// Windows
void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void sp(int choosecolor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), choosecolor);
}
void s()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
////////////////////////////////////////////////////////////////////////////////// ^ Windows
void Snake::Start()
{
    for(int p = 0;p < 2000;p++)
    {
        map[p] = ' ';
    }

    map[ x ] = char(219);
    Pineapple();
    Graphics();
}
//////////////////////////////////////////////////////////////////////////////////////////
int Snake::GameOver()
{
    Sleep(2500);
    system("cls");
    std::cout <<     std::endl << "Oops...Ai adunat " << Dollars + Bonus << " fructe...";
    Sleep(1800);
    return 0;
}
void Snake::Graphics()
{
    sp(697);
    std::cout << Dollars + Bonus << " Fructe ";
    std::cout << "\n";
    s();
    for(int u = 0;u < 50;u++)
    {
        sp(750);
        std::cout << char(219);
        s();
    }

	std::cout <<     std::endl;
/***********************************************************************/
    for(int x1 = 0;x1 < 2000 ; x1++)
    {
        if(x1 % 50 == 0 && x1 != 0)
        {
            std::cout <<     std::endl;
        }
        if(x1 % 50 == 0 || (x1-(x1 / 50)) % 49 == 0)
		{
            map[x1] = char(219);
            sp(750);
            std::cout << map[x1];
            s();
		}
	else if(map[x1]!=char(219) && map[x1]!=map[z])
    {
        std::cout << map[x1];
    }
    else if(x1 == z)
    {
        sp(10);
        std::cout << map[x1];
        s();
    }
    else
    {
        sp(750);
        std::cout << map[x1];
        s();
	}

    }

	std::cout <<     std::endl;
/***********************************************************************/
    for(int u = 0;u < 50;u++)
    {
        sp(750);
        std::cout << char(219);
        s();
    }
    if(U == 1 || D == 1)
	{
        Sleep(19);
    }
    if(map[z] == char(5))
    {
        time--;
        if(time == 0)
		{
            Dollars++;
            time = 40;
            Pineapple();
        }
    }

    clearscreen();
    GameLogic();
}

void Snake::Pineapple()
{
    map[z] = ' ';
    if(Dollars % 8 != 0 || Dollars == 0)
    {
        while(map[z] != ' ' && z % 50 != 0 && (z-(z/50)) % 49!= 0);
        {
            z = rand()%2000 + 1;
		}

	    map[z] = char(229);
    }

    else
    {
        while(map[z] != ' ' && z % 50 != 0 && (z-(z/50)) % 49 != 0);
        {
            z = rand()%2000 + 1;
        }
        map[z] = char(5);
    }

}

void Snake::KEYBOARD()
{
/***********************************************************************************************/
if(_kbhit())

{
    char key;
    key = _getch();
    switch( key )
    {
        case 'd':
        {
            if (L == 0)
            {
                L = 0, U = 0, D = 0,
                R = 1;
			}
            break;
        }

        case 'w':
        {
            if (D == 0)
            {
                L = 0, D = 0, R = 0,
                U = 1;
            }
        break;
        }

        case 'a':
        {
            if (R == 0)
            {
                D = 0, U = 0, R = 0,
                L = 1;
			}
        break;
        }

        case 's':
        {
            if (U == 0)
            {
                L = 0, U = 0, R = 0,
                D = 1;
            }
        break;
        }

    }

}
}

/**************************************************************************/
void Snake::GameLogic()
{
    past.insert(past.begin(),x);
    KEYBOARD();
    if(R == 1)
    {
        x++;
    }
    else if(L == 1)
    {
        x--;
    }
    else if(U == 1)
    {
        x-= 50;
    }
    else
    {
        x+= 50;
    }
    if(map[ x ] == char(219) || x % 50 == 0 || x > 2000 || x < 0 || (x-(x / 50)) % 49 == 0)
    {
        GameOver();
        return;
    }
    if(map[x] == char(229))
    {
        A = true;
        tail++;
        Pineapple();
        Dollars++;
	}
    else if (map[x] == char(5))
    {
        A = true;
        tail++;
        Pineapple();
        Bonus+=time;
    }

    map[x] = char(219);
/**********/
    if(A == false)
    {
        y = past[past.size() - tail];
        map[y] = ' ';
    }

    A = false;
    if(tail!=1)
    {
        for(int u = past.size() - 2;u > 0;u--)
		{
            past[u+1] = past[u];
        }
    past.erase(past.end()-tail);
    }
    else
    {
        past.erase(past.begin());
    } //
    Graphics();
}
int main()
{
    srand((unsigned)time(0));
    Snake SNAKE;
    SNAKE.Start();
}

