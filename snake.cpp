#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;


enum eDirecton
{
    STOP = 0,
    LEFT, RIGHT, UP, DOWN
};
eDirecton dir;

void Start()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0;
}
void InitMap()
{
	system("cls"); //system("clear");
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
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
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
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
			gameOver = true;
			break;
		}
	}
}
void GameLogic()
{
	int headX = tailX[0];
	int headY = tailY[0];
	int head2X, head2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		head2X = tailX[i];
		head2Y = tailY[i];
		tailX[i] = headX;
		tailY[i] = headY;
		headX = head2X;
		headY = head2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0) gameOver = true;
    for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == foodX && y == foodY)
	{
		score += 10;
		foodX = rand() % width;
		foodY = rand() % height;
		nTail++;
	}
}
int main()
{
	Start();
	while (!gameOver)
	{
		InitMap();
		KeyboardInput();
		GameLogic();
		Sleep(10);
	}

	cout << "GAME OVER" << endl;
	return 0;
}
