/*
 ============================================================================
 Name        : 2048
 Author      : Saket S Komawar
 Description : Console version of the game "2048" for GNU/Linux without GUI.
 ============================================================================
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 4

int score = 0;

/*Functions*/
void AddRandom(int grid[SIZE][SIZE])
{
	int i, j, n, length = 0, block, list[SIZE * SIZE][2];
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			if(grid[i][j] == 0)
			{
				list[length][0] = i;
				list[length][1] = j;
				length++;
			}
		}
	}
	srand(time(NULL)); //Seeding Rand() Function
	if(length > 0)
	{
		block = rand() % length;
		n = 2 * ((rand() % 10) / 9 + 1);
		i = list[block][0];
		j = list[block][1];
		grid[i][j] = n;
	}
}

void DrawBoard(int grid[SIZE][SIZE])
{
	int i, j;
	system("clear");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t 2048\n\n\n\n\n\n");
	for(i = 0; i < SIZE; i++)
	{
		printf("\t\t\t\t\t\t\t");
		for(j = 0; j < SIZE; j++)
		{
			if(j != 3)
				printf("  %d  |", grid[i][j]);
			else
				printf("  %d  ", grid[i][j]);
		}
		printf("\n");
		if(i != 3)
			printf("\t\t\t\t\t\t\t-----------------------");
		printf("\n");
	}
	printf("\n");
	printf("\t\tScore: %d\n\n", score);
	printf("\t\t\tUse Arrow Keys or Use a, s, d, w or Use h, j, k, l to Play AND 'q' to quit!");
	printf("\n");
}

void InitBoard(int grid[SIZE][SIZE])
{
	int i, j;
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			grid[i][j] = 0;
		}
	}
	AddRandom(grid);
	AddRandom(grid);
}

bool FindPair(int grid[SIZE][SIZE])
{
	int i, j;
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			if(grid[i][j] == grid[i][j + 1] || grid[i][j] == grid[i + 1][j])
			{
				return true;
			}
		}
	}
	return false;
}

bool GameEnded(int grid[SIZE][SIZE])
{
	int i, j;
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			if(grid[i][j] == 0)
			{
				return false;
			}
		}
	}
	if(FindPair(grid))
	{
		return false;
	}
	return true;
}

bool SlideLeft(int grid[SIZE])
{
	int i, j, tmp, flag[] = {0, 0, 0, 0};
	bool success = false;
	for(i = 0; i < SIZE; i++)
	{
		tmp = i;
		for(j = 0; j < i; j++)
		{
			if(grid[tmp] != 0)
			{
				if(grid[tmp] == grid[tmp - 1] && flag[tmp - 1] == 0 && flag[tmp] == 0)
				{
					grid[tmp - 1] = 2 * grid[tmp];
					score = score + grid[tmp - 1];
					grid[tmp] = 0;
					switch(tmp - 1)
					{
						case 0:
							flag[0] = 1;
							break;
						case 1:
							flag[1] = 1;
							break;
						case 2:
							flag[2] = 2;
							break;
					}
					success = true;
				}
				else if(grid[tmp - 1] == 0 && grid[tmp] != 0)
				{
					grid[tmp - 1] = grid[tmp];
					grid[tmp] = 0;
					success = true;
				}
			}
			tmp--;
		}	
	}
	return success;
}

/*AntiClockWise*/
void RotateBoard(int grid[SIZE][SIZE])
{
	int i, j, tmp, n = SIZE;
	for(i = 0; i < n / 2; i++)
	{
		for(j = i; j < n - i - 1; j++)
		{
			tmp = grid[i][j];
			grid[i][j] = grid[j][n-i-1];
			grid[j][n-i-1] = grid[n-i-1][n-j-1];
			grid[n-i-1][n-j-1] = grid[n-j-1][i];
			grid[n-j-1][i] = tmp;
		}
	}
}

bool MoveLeft(int grid[SIZE][SIZE])
{
	bool success = false;
	int i;
	for(i = 0; i < SIZE; i++)
	{
		success |= SlideLeft(grid[i]);
	}
	return success;
}

bool MoveUp(int grid[SIZE][SIZE]) 
{
	bool success;
	RotateBoard(grid);
	success = MoveLeft(grid);
	RotateBoard(grid);
	RotateBoard(grid);
	RotateBoard(grid);
	return success;
}

bool MoveDown(int grid[SIZE][SIZE]) 
{
	bool success;
	RotateBoard(grid);
	RotateBoard(grid);
	RotateBoard(grid);
	success = MoveLeft(grid);
	RotateBoard(grid);
	return success;
}

bool MoveRight(int grid[SIZE][SIZE]) 
{
	bool success;
	RotateBoard(grid);
	RotateBoard(grid);
	success = MoveLeft(grid);
	RotateBoard(grid);
	RotateBoard(grid);
	return success;
}

/*Main Function*/
int main()
{
	int Board[SIZE][SIZE], i, j;
	char c;
	bool success = false;
	
	InitBoard(Board);
	DrawBoard(Board);

	while(true)
	{
		c = getchar();
		switch(c) 
		{
			case 97:	// 'a' key
			case 104:	// 'h' key
			case 68:	// left arrow
				success = MoveLeft(Board);  
				break;
			case 100:	// 'd' key
			case 108:	// 'l' key
			case 67:	// right arrow
				success = MoveRight(Board); 
				break;
			case 119:	// 'w' key
			case 107:	// 'k' key
			case 65:	// up arrow
				success = MoveUp(Board);    
				break;
			case 115:	// 's' key
			case 106:	// 'j' key
			case 66:	// down arrow
				success = MoveDown(Board);  
				break;
			default: success = false;
		}
		if(c == 'q')
			break;
		if(GameEnded(Board))
		{
			system("clear");
			printf("\n\n\n\n\n");
			printf("\t\t\t\t\tGame Ended\n");
			break;
		}				
		if(success)
		{
			AddRandom(Board);
			DrawBoard(Board);			
		}
	}
	return 0;
}
