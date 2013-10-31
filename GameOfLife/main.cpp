//The MIT License (MIT)
//
//Copyright (c) 2013 Marius Savickas
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#define DI_X 74
#define DI_Y 45

//1 - alive, 0 - dead
unsigned char grid[DI_X][DI_Y] = {0};
unsigned char grid2[DI_X][DI_Y] = {0};
bool flag = false;
int populution = 0;
int generation = 0;

int deathPercent = 0;
int spawPercent = 0;
int rule = 0;
int lastPopulation = 0;

void gotoXY(int x, int y);
void ShowConsoleCursor( BOOL bShow );
void SetWindowSize(int x, int y);

int main()
{
	ShowConsoleCursor(false);
	SetWindowSize(800, 600);

	printf("***Initial rules***\n");
	printf("Spawn percent(10): ");
	scanf("%i", &spawPercent);
	printf("Rule: ");
	scanf("%i", &rule);
	
	srand(rule);

	//Make random
	for(int y = 0; y < DI_Y; y++)
	{
		for(int x = 0; x < DI_X; x++)
		{
			int random = rand() % 100;
			if(random < spawPercent)grid[x][y] = 1;
		}
	}

	while(true)
	{
		//Simulation
		populution = 0;

		if(flag)
		{
			for(int y = 0; y < DI_Y; y++)
			{
				for(int x = 0; x < DI_X; x++)
				{
					//Draw cells
					if(grid2[x][y] == 1)
					{
						
						//grid[x][y] = 1;
						gotoXY(x, y);
						std::cout << (char)0xFE;
						populution++;
					}
					else 
					{
						gotoXY(x, y);
						std::cout << " ";
					}


					//Check if that cell has neighbours
					int neighbours = 0;
					//Top
					if(y > 0)
					{
						if(grid2[x-1][y-1] == 1) neighbours++;
						if(grid2[x][y-1] == 1) neighbours++;
						if(grid2[x+1][y-1] == 1) neighbours++;
					}

					//Sideways
					if(x > 0 && x < DI_X-1)
					{
						if(grid2[x-1][y] == 1) neighbours++;
						if(grid2[x+1][y] == 1) neighbours++;
					}
				
					//Bottom
					if(y < DI_Y-1)
					{
						if(grid2[x-1][y+1] == 1) neighbours++;
						if(grid2[x][y+1] == 1) neighbours++;
						if(grid2[x+1][y+1] == 1) neighbours++;
					}
					//If over-populated - make the cell dead
					if(neighbours > 3 && grid2[x][y] == 1)
					{
						grid[x][y] = 0;
					}
					//Under-populated - make the cell dead
					else if(neighbours < 2 && grid2[x][y] == 1)
					{
						grid[x][y] = 0;
					}
					//If the size is correct - make the cell alive
					else if(neighbours == 3)
					{
						grid[x][y] = 1;
					}
					else 
					{
						grid[x][y] = grid2[x][y];
					}
	
				}
			}
			flag = false;
		}

		
		else
		{
			for(int y = 0; y < DI_Y; y++)
			{
				for(int x = 0; x < DI_X; x++)
				{
					//Draw cells
					if(grid[x][y] == 1)
					{
						//grid2[x][y] = 1;
						gotoXY(x, y);
						std::cout << (char)0xFE;
						populution++;
					}
					else 
					{
						gotoXY(x, y);
						std::cout << " ";
					}


					//Check if that cell has neighbours
					int neighbours = 0;
					//Top
					if(y > 0)
					{
						if(grid[x-1][y-1] == 1) neighbours++;
						if(grid[x][y-1] == 1) neighbours++;
						if(grid[x+1][y-1] == 1) neighbours++;
					}

					//Sideways
					if(x > 0 && x < DI_X-1)
					{
						if(grid[x-1][y] == 1) neighbours++;
						if(grid[x+1][y] == 1) neighbours++;
					}
				
					//Bottom
					if(y < DI_Y-1)
					{
						if(grid[x-1][y+1] == 1) neighbours++;
						if(grid[x][y+1] == 1) neighbours++;
						if(grid[x+1][y+1] == 1) neighbours++;
					}
					//If over-populated - make the cell dead
					if(neighbours > 3 && grid[x][y] == 1)
					{
						grid2[x][y] = 0;
					}
					//Under-populated - make the cell dead
					else if(neighbours < 2 && grid[x][y] == 1)
					{
						grid2[x][y] = 0;
					}
					//If the size is correct - make the cell alive
					else if(neighbours == 3)
					{
						grid2[x][y] = 1;
					}
					else
					{
						grid2[x][y] = grid[x][y];
					}
	
				}
			}
			flag = true;
		}
		generation++;
		lastPopulation = populution;

		printf("\nPopulution: %d       Generation: %d", populution, generation);
		Sleep(1);
	}
	

	return 0;
}

void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowConsoleCursor( BOOL bShow )
{
 
    HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

	cursorInfo.dwSize   = 10;
    cursorInfo.bVisible     = bShow;
 
    SetConsoleCursorInfo( hOut, &cursorInfo );
}

void SetWindowSize(int x, int y)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, x, y, TRUE);
}