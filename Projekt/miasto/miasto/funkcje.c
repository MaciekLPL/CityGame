#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

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


void SimplePrintScreen(char** board, int rows, int cols) {
	
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
	ShowConsoleCursor(1);
}

void drawingTool(char** board, int* x, int* y, int rows, int cols) {

	int x1 = *x, y1 = *y, x2, y2;
	int tmp = board[*y][*x];
	int chr = _getch();
	if (chr != 'q' && chr != 'w' && chr != 'e' && chr != 'd') return;
	if (chr == 'd') chr = '\0';
	board[*y][*x] = 'X';
	SimplePrintScreen(board, rows, cols);

	while (1) {
		gotoxy(*x, *y);
		int c = _getch();
		if (c == 0xE0)
			arrowsHandling(x, y, c, rows, cols);
		else if (c == 'a') {
			x2 = *x, y2 = *y;
			break;
		}
		else {
			board[y1][x1] = tmp;
			return;
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (((i >= y1 && i <= y2) || (i >= y2 && i <= y1)) &&
				((j >= x1 && j <= x2) || (j >= x2 && j <= x1)))
				board[i][j] = chr;
		}
	}
	*x = x2;
	*y = y2;
}
