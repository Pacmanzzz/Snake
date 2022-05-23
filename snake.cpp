#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool isGameOver;
const int w = 20;
const int h = 20;

int x, y, foodX, foodY, score;
int snakeX[100], snakeY[100];
int nsnake;


enum eDirection
{
    STOP = 0,
    LEFT, RIGHT, UP, DOWN
};
eDirection dir;

void Start()
{
	isGameOver = false;
	dir = STOP;
	x = w/2;
	y = h/2;
	foodX = rand()%w;
	foodY = rand()%h;
	score = 0;
}
void DrawMap()
{
	system("cls"); //system("clear");
	for (int i = 0; i < w+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == foodY && j == foodX)
				cout << "x";
			else
			{
				bool print = false;
				for (int k = 0; k < nsnake; k++)
				{
					if (snakeX[k] == j && snakeY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == w-1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < w+2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}
void KeyboardInput()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			isGameOver = true;
			break;
		}
	}
}

int main()
{
	Start();
	while (!isGameOver)
	{
		DrawMap();
		KeyboardInput();
		int prevX = snakeX[0];
        int prevY = snakeY[0];
        int prev2X, prev2Y;
        snakeX[0] = x;
        snakeY[0] = y;
        for (int i = 1; i < nsnake; i++)
        {
            prev2X = snakeX[i];
            prev2Y = snakeY[i];
            snakeX[i] = prevX;
            snakeY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        switch (dir)
        {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;
        }
        if (x > w || x < 0 || y > h || y < 0) isGameOver = true;
        for (int i = 0; i < nsnake; i++)
            if (snakeX[i] == x && snakeY[i] == y)
                isGameOver = true;

        if (x == foodX && y == foodY)
        {
            score += 10;
            foodX = rand()%w;
            foodY = rand()%h;
            nsnake++;
        }
            Sleep(10);
        }
    cout << "\n GAME OVER" << endl;
	return 0;
}
