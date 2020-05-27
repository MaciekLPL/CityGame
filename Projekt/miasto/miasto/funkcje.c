#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define RST "\x1B[0m"

#include "struktury.h"


chunk** createBoard(int rows, int cols) {

	chunk** board = calloc(rows, sizeof(chunk*));

	for (int i = 0; i < rows; i++) {
		board[i] = calloc(cols, sizeof(chunk));
	}
	return board;
}


void setBorders(chunk** board, int rows, int cols) {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == 0 || i == rows - 1)
				board[i][j].c = 219;
			else if (j == 0 || j == cols - 1)
				board[i][j].c = 219;
			else {
				board[i][j].c = '\0';
				board[i][j].attractiveness = 0;
				board[i][j].population = 0;
			}
		}
	}
	board[rows - 1][cols / 2].c = 'q';
}


void arrowsHandling(int* x, int* y, int c, int rows, int cols) {
	
	c = _getch();
	switch (c) {
	case 0x4B:
		if (*x != 1) (*x)--;
		break;
	case 0x4D:
		if (*x != cols - 2) (*x)++;
		break;
	case 0x48:
		if (*y != 1) (*y)--;
		break;
	case 0x50:
		if (*y != rows - 2) (*y)++;
		break;
	default:
		break;
	}
}


void ShowConsoleCursor(int showFlag) {

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = showFlag;
	cursorInfo.dwSize = 100;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


void gotoxy(int x, int y) {

	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int drawRoad(chunk** board, int i, int j, int rows) {

	int c = 186;
	if (i == rows - 1);	
	else if (board[i - 1][j].c == 'q' && board[i + 1][j].c == 'q' && board[i][j - 1].c == 'q' && board[i][j + 1].c == 'q')
		c = 206;
	else if (board[i][j - 1].c == 'q' && board[i - 1][j].c == 'q' && board[i + 1][j].c == 'q')
		c = 185;
	else if (board[i][j - 1].c == 'q' && board[i - 1][j].c == 'q' && board[i][j + 1].c == 'q')
		c = 202;
	else if (board[i - 1][j].c == 'q' && board[i][j + 1].c == 'q' && board[i + 1][j].c == 'q')
		c = 204;
	else if (board[i][j - 1].c == 'q' && board[i + 1][j].c == 'q' && board[i][j + 1].c == 'q')
		c = 203;
	else if (board[i - 1][j].c == 'q' && board[i][j - 1].c == 'q')
		c = 188;
	else if (board[i - 1][j].c == 'q' && board[i][j + 1].c == 'q')
		c = 200;
	else if (board[i + 1][j].c == 'q' && board[i][j + 1].c == 'q')
		c = 201;
	else if (board[i + 1][j].c == 'q' && board[i][j - 1].c == 'q')
		c = 187;
	else if (board[i][j - 1].c == 'q' || board[i][j + 1].c == 'q')
		c = 205;
	return c;
}

double getTime(LARGE_INTEGER t1) {

	LARGE_INTEGER freq, t2;
	QueryPerformanceCounter(&t2);
	QueryPerformanceFrequency(&freq);
	return (t2.QuadPart - t1.QuadPart) / (double)freq.QuadPart;
}

void printMenu(int rows, LARGE_INTEGER t1, int x, int y, int money) {

	ShowConsoleCursor(0);
	gotoxy(0, rows+1);

	double elapsedTime = getTime(t1);
	printf("Dzien: %d \nGodzina: %02d \n", (int)(elapsedTime / 24), (int)elapsedTime % 24);
	printf("Budzet: %d              ", money);

	gotoxy(x, y);
	ShowConsoleCursor(1);
}

void SimplePrintScreen(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money) {
	
	ShowConsoleCursor(0);
	gotoxy(0, 0);

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {

			if (board[i][j].c == 'q')
				printf("%c", drawRoad(board, i, j, rows));
			else if(board[i][j].c == 'w')
				printf(GRN "%c" RST, 176);
			else if(board[i][j].c == 'e')
				printf(BLU "%c" RST, 176);
			else if (board[i][j].c == 'r')
				printf(YEL "%c" RST, 176);
			else
				putc(board[i][j].c, stdout);
		}
		putc('\n', stdout);
	}
	printMenu(rows, t1, 0, 0, money);
}


void newWallet(int diff, budget** wallet) {

	budget* new_wallet;
	new_wallet = (budget*)calloc(1, sizeof(budget));

	new_wallet->money = (*wallet)->money + diff;
	new_wallet->next = *wallet;
	*wallet = new_wallet;
}


void buildRoad(chunk** board, int x, int y, struct budget** wallet) {

	if ((*wallet)->money >= 2000 && board[y][x].c != 'q') {
		newWallet(-2000, wallet);
		board[y][x].c = 'q';
	}
}


void setZone(chunk** board, int x, int y, int c, struct budget** wallet) {

	if (board[y][x].c == 'q')
		newWallet(1000, wallet);
	board[y][x].c = c;
}

