#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
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
				board[i][j] = NULL;
		}
	}

	board[rows - 1][cols / 2] = 186;
}

void arrowsHandling(int* x, int* y, int* c, int rows, int cols) {
	*c = _getch();
	switch (*c)
	{
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




void SimplePrintScreen(char** board, int rows, int cols) {

	gotoxy(0, 0);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			putc(board[i][j], stdout);
		}
		putc('\n', stdout);
	}
}