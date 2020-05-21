#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

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


void SimplePrintScreen(char** board, int rows, int cols, LARGE_INTEGER t1) {
	
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
	LARGE_INTEGER freq, t2;
	QueryPerformanceCounter(&t2);
	QueryPerformanceFrequency(&freq);
	double elapsedTime = (t2.QuadPart - t1.QuadPart) / (double)freq.QuadPart;
	printf("Godzina: %2d Dzien: %d", elapsedTime, ceil(elapsedTime / 24));
	ShowConsoleCursor(1);
}

void printMenu(int rows, LARGE_INTEGER t1) {
	ShowConsoleCursor(0);
	gotoxy(0, rows);
	LARGE_INTEGER freq, t2;
	QueryPerformanceCounter(&t2);
	QueryPerformanceFrequency(&freq);
	double elapsedTime = (t2.QuadPart - t1.QuadPart) / (double)freq.QuadPart;
	printf("Godzina: %2d Dzien: %d", (int)elapsedTime % 24, (int)(elapsedTime / 24));
	
}

void drawingTool(char** board, int* x, int* y, int rows, int cols, LARGE_INTEGER t1) {

	int x1 = *x, y1 = *y, x2, y2;
	int tmp1 = board[*y][*x];
	int tmp2, c;
	board[*y][*x] = 'X';
	SimplePrintScreen(board, rows, cols, t1);

	while (1) {
		while (!_kbhit()) {
			printMenu(rows, t1);
			gotoxy(*x, *y);					///wywaliæ to i zostawiæ goto
			ShowConsoleCursor(1);
		}
		c = _getch();
		if (c == 0xE0) 
			arrowsHandling(x, y, c, rows, cols);
		else if (c == 'x') {
			x2 = *x, y2 = *y;
			tmp2 = board[*y][*x];
			board[*y][*x] = 'X';
			SimplePrintScreen(board, rows, cols, t1);
			while (!_kbhit()) {
				printMenu(rows, t1);
				gotoxy(*x, *y);				///wywaliæ to i zostawiæ goto
				ShowConsoleCursor(1);
			}
			gotoxy(*x, *y);
			c = _getch();
			if (c != 'q' && c != 'w' && c != 'e' && c != 'd') {
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
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (((i >= y1 && i <= y2) || (i >= y2 && i <= y1)) &&
				((j >= x1 && j <= x2) || (j >= x2 && j <= x1)))
				board[i][j] = c;
		}
	}
	*x = x2;
	*y = y2;
}

