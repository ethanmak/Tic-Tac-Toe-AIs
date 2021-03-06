// InitializeTextbook.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "stdlib.h"
#include <iostream>
#include <string>

using namespace std;

enum Switches {
	notAssigned = 0,
	human = 1,
	AI = 2
};

Switches mainLoop = notAssigned;
char tictactoe[3][3] = { {' ',' ',' '},{' ',' ',' '},{' ',' ',' '} };
short moveCount = 0;

void askforTurns();
void printBoard();
void playerTurn();
int checkforWin(char arr[][3]);
void switchTurns();
void cpuTurn();

int main()
{
	askforTurns();
	while (checkforWin(tictactoe) == 2)
	{
		if (mainLoop == human)
		{
			switchTurns();
			printBoard();
			playerTurn();
		}
		else if (mainLoop == AI)
		{
			switchTurns();
			printBoard();
			cpuTurn();
		}
		
	}
	if (checkforWin(tictactoe) == 1)
	{
		printBoard();
		printf("CPU has won!\n");
	}
	else if (checkforWin(tictactoe) == 0)
	{
		printBoard();
		printf("Both sides have tied\n");
	}
	else if (checkforWin(tictactoe) == -1)
	{
		printBoard();
		printf("Player has won!\n");
	}
    return 0;
}

void askforTurns()
{
	char temp;
	printf("You: X		CPU: O\n");
	printf("Would you like to go first? Y/N \n");
	scanf("%c", &temp);
	if (temp == 'Y')
	{
		mainLoop = human;
	}
	else if(temp == 'N')
	{
		mainLoop = AI;
	}
	else
	{
		askforTurns();
	}
}

void printBoard()
{
	short row = 1;
	printf("  1 2 3\n");
	printf("%d ", row);
	for (int i = 1, lineArr = 0, rowArr = 0; i <= 9; i++)
	{
		printf("%c", tictactoe[lineArr][rowArr]);
		if (i % 3 == 0 && i != 9)
		{
			printf("\n ------- \n");
			printf("%d ", ++row);
			rowArr = 0;
			lineArr++;
		}
		else if (i % 3 != 0)
		{
			printf("|");
			rowArr += 1;
		}
	}
	printf("\n");
}

void playerTurn()
{
	int playerXPos;
	int playerYPos;
	printf("Please enter X coordinates for move: ");
	scanf("%d", &playerXPos);
	printf("\nPlease enter Y coordinates for move: ");
	scanf("%d", &playerYPos);
	printf("\n");
	if (tictactoe[playerYPos - 1][playerXPos - 1] == ' ')
	{
		tictactoe[playerYPos - 1][playerXPos - 1] = 'X';
	}
	else
	{
		printf("Space already taken, Try again\n");
		playerTurn();
	}
}

int checkforWin(char arr[][3])
{
	int Pos, countx, county;
	//up and down and left and right
	for (Pos = 0; Pos <= 2; Pos++)
	{
		if (arr[Pos][0] == 'X' && arr[Pos][1] == 'X' && arr[Pos][2] == 'X')
		{
			return -1;
		}
		if (arr[0][Pos] == 'X' && arr[1][Pos] == 'X' && arr[2][Pos] == 'X')
		{
			return -1;
		}
		if (arr[Pos][0] == 'O' && arr[Pos][1] == 'O' && arr[Pos][2] == 'O')
		{
			return 1;
		}
		if (arr[0][Pos] == 'O' && arr[1][Pos] == 'O' && arr[2][Pos] == 'O')
		{
			return 1;
		}
	}
	//diagonal
	if (arr[0][0] == 'O' && arr[1][1] == 'O' && arr[2][2] == 'O')
	{
		return 1;
	}
	//anti-diagonal
	if (arr[0][2] == 'O' && arr[1][1] == 'O' && arr[2][0] == 'O')
	{
		return 1;
	}
	//diagonal
	if (arr[0][0] == 'X' && arr[1][1] == 'X' && arr[2][2] == 'X')
	{
		return -1;
	}
	//anti-diagonal
	if (arr[0][2] == 'X' && arr[1][1] == 'X' && arr[2][0] == 'X')
	{
		return -1;
	}
	//tie
	for (countx = 0, county = 0, Pos = 1; Pos <= 9; Pos++)
	{
		if(arr[county][countx] == ' ')
		{
			return 2;
		}
		//incrementing x and y
		if (Pos % 3 == 0 && Pos != 9)
		{
			countx = 0;
			county++;
		}
		else if (Pos % 3 != 0)
		{
			countx += 1;
		}
	}
	return 0;
}

void switchTurns()
{
	if (mainLoop == human)
	{
		mainLoop = AI;
	}
	else
	{
		mainLoop = human;
	}
	moveCount++;
}

int minmax(char array[][3], int player)
{
	int countx, county, i;
	int score = -2, current;
	int winner = checkforWin(array);
	if (winner != 2)
	{
		return winner*player;
	}

	for (countx = 0, county = 0, i = 1; i <= 9; i++)
	{
		if (array[county][countx] == ' ') //if valid
		{
			if(player == 1)
			{
				array[county][countx] = 'O';
			}
			if (player == -1)
			{
				array[county][countx] = 'X';
			}
			current = -minmax(array, player*-1);
			if (current > score)
			{
				score = current;
			}
			array[county][countx] = ' '; //set it back
		}

		//incrementing x and y
		if (i % 3 == 0 && i != 9)
		{
			countx = 0;
			county++;
		}
		else if (i % 3 != 0)
		{
			countx += 1;
		}
	}
	return score;
}

void cpuTurn()
{
	char mimic[3][3];
	
	int countx, county, i, score = -2, current, moveX, moveY;

	for (countx = 0, county = 0, i = 1; i <= 9; i++)
	{
		mimic[county][countx] = tictactoe[county][countx];

		//incrementing x and y
		if (i % 3 == 0 && i != 9)
		{
			countx = 0;
			county++;
		}
		else if (i % 3 != 0)
		{
			countx += 1;
		}
	}

	for (countx = 0, county = 0, i = 1; i <= 9; i++)
	{
		if (mimic[county][countx] == ' ') //if valid
		{
			mimic[county][countx] = 'O';
			current = -minmax(mimic, -1);
			if (current > score)
			{
				score = current;
				moveX = countx;
				moveY = county;
			}
			mimic[county][countx] = ' '; //set it back
		}
		
		//incrementing x and y
		if (i % 3 == 0 && i != 9)
		{
			countx = 0;
			county++;
		}
		else if (i % 3 != 0)
		{
			countx += 1;
		}
	}
	//make the turn
	tictactoe[moveY][moveX] = 'O';
}