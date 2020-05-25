#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"


#ifndef max
#define max(a,b)  (((a) >= (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)  (((a) <= (b)) ? (a) : (b))
#endif


#include "struktury.h"


char** createBoard(int rows, int cols) {
	char** board = calloc(rows, sizeof(char*));

	for (int i = 0; i < rows; i++) {
		board[i] = calloc(cols, sizeof(char));
	}
	return board;
}


void setBorders(char** board, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == 0 || i == rows - 1)
				board[i][j] = 219;
			else if (j == 0 || j == cols - 1)
				board[i][j] = 219;
			else
				board[i][j] = '\0';
		}
	}
	board[rows - 1][cols / 2] = 'q';
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


int drawRoad(char** board, int i, int j, int rows) {

	int c = 186;
	if (i == rows - 1);	
	else if (board[i - 1][j] == 'q' && board[i + 1][j] == 'q' && board[i][j - 1] == 'q' && board[i][j + 1] == 'q')
		c = 206;
	else if (board[i][j - 1] == 'q' && board[i - 1][j] == 'q' && board[i + 1][j] == 'q')
		c = 185;
	else if (board[i][j - 1] == 'q' && board[i - 1][j] == 'q' && board[i][j + 1] == 'q')
		c = 202;
	else if (board[i - 1][j] == 'q' && board[i][j + 1] == 'q' && board[i + 1][j] == 'q')
		c = 204;
	else if (board[i][j - 1] == 'q' && board[i + 1][j] == 'q' && board[i][j + 1] == 'q')
		c = 203;
	else if (board[i - 1][j] == 'q' && board[i][j - 1] == 'q')
		c = 188;
	else if (board[i - 1][j] == 'q' && board[i][j + 1] == 'q')
		c = 200;
	else if (board[i + 1][j] == 'q' && board[i][j + 1] == 'q')
		c = 201;
	else if (board[i + 1][j] == 'q' && board[i][j - 1] == 'q')
		c = 187;
	else if (board[i][j - 1] == 'q' || board[i][j + 1] == 'q')
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
	printf("Godzina: %02d Dzien: %d \n", (int)elapsedTime % 24, (int)(elapsedTime / 24));
	printf("Budzet: %d              ", money);

	gotoxy(x, y);
	ShowConsoleCursor(1);
}

void SimplePrintScreen(char** board, int rows, int cols, LARGE_INTEGER t1, int money) {
	
	ShowConsoleCursor(0);
	gotoxy(0, 0);

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {

			if (board[i][j] == 'q')
				printf("%c", drawRoad(board, i, j, rows));
			else if(board[i][j] == 'w')
				printf(GRN "%c" RESET, 177);
			else if(board[i][j] == 'e')
				printf(CYN "%c" RESET, 177);
			else
				putc(board[i][j], stdout);
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


bool buildRoad(char** board, int x, int y, struct budget** wallet) {
	if ((*wallet)->money >= 2000 && board[y][x] != 'q') {
		newWallet(-2000, wallet);
		board[y][x] = 'q';
		return 1;
	}
	else return 0;
}


void fillBoard(char** board, int x1, int x2, int y1, int y2, int c, budget** wallet) {
	for (int i = min(y1, y2); i <= max(y1, y2); i++) {
		for (int j = min(x1, x2); j <= max(x1, x2); j++) {
			if (c == 'q' && board[i][j] != 'q') {
				if (!buildRoad(board, j, i, wallet))
					break;
			}
			else if (c == '\0') {
				if (board[i][j] == 'q')
						newWallet(1000, wallet);
					board[i][j] = '\0';
			}
			else
				board[i][j] = c;
		}
	}
}


void drawingTool(char** board, int* x, int* y, int rows, int cols, LARGE_INTEGER t1, budget** wallet) {

	int x1 = *x, y1 = *y, x2, y2;
	int tmp1 = board[*y][*x];
	int tmp2, c;
	board[*y][*x] = 'X';
	SimplePrintScreen(board, rows, cols, t1, (*wallet)->money);

	while (1) {
		while (!_kbhit())
			printMenu(rows, t1, *x, *y, (*wallet)->money);
		c = _getch();
		if (c == 0xE0) 
			arrowsHandling(x, y, c, rows, cols);

		else if (c == 'x') {
			x2 = *x, y2 = *y;
			tmp2 = board[*y][*x];
			board[*y][*x] = 'X';
			SimplePrintScreen(board, rows, cols, t1, (*wallet)->money);

			while (!_kbhit())
				printMenu(rows, t1, *x, *y, (*wallet)->money);

			c = _getch();
			if (c != 'q' && c != 'w' && c != 'e' && c != 'd' || (c == 'q' && (*wallet)->money < 2000)) {
				board[y1][x1] = tmp1;
				board[y2][x2] = tmp2;
				return;
			}

			if (c == 'd') c = '\0';
			break;
		}
		else {
			board[y1][x1] = tmp1;
			return;
		}
	}
	board[y1][x1] = tmp1;
	board[y2][x2] = tmp2;

	fillBoard(board, x1, x2, y1, y2, c, wallet);
	*x = x2;
	*y = y2;
}





