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


chunk** createBoard(int rows, int cols) {

	chunk** board = calloc(rows, sizeof(chunk*));

	for (int i = 0; i < rows; i++) {
		board[i] = calloc(cols, sizeof(chunk));
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j].c = '\0';
			board[i][j].attractiveness = 0;
			board[i][j].population = 0;
		}
	}
	return board;
}

void printBorders(int rows, int cols) {
	for (int i = 0; i < rows + 2; i++) {
		for (int j = 0; j < cols + 2; j++) {
			if (i == 0 || i == rows + 1)
				putc(219, stdout);
			else if (j == 0 || j == cols + 1)
				putc(219, stdout);
			else
				putc(' ', stdout);
		}
		gotoxy(0, i + 1);
	}
	gotoxy(cols / 2, rows + 1);
	putc(186, stdout);
}


void arrowsHandling(int* x, int* y, int c, int rows, int cols) {
	
	c = _getch();
	switch (c) {
	case 0x4B:
		if (*x != 1) (*x)--;
		break;
	case 0x4D:
		if (*x != cols) (*x)++;
		break;
	case 0x48:
		if (*y != 1) (*y)--;
		break;
	case 0x50:
		if (*y != rows) (*y)++;
		break;
	default:
		break;
	}
}


int drawRoad(chunk** board, int i, int j, int rows, int cols) {

	int c = 186;
	if (i == 0 || j == 0 || i == rows-1 || j == cols-1);
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


bool isValid(int x, int y, int rows, int cols) {

	if ((x >= 0 && x < cols - 1) && (y >= 0 && y < rows - 1))
		return 1;
	return 0;
}

void checkNeigbours(chunk** board, int r, int c, int rows, int cols) {

	for (int i = r - 3; i < r + 3; i++) {
		for (int j = c - 3; j < c + 3; j++) {
			if (isValid(j, i, rows, cols))
				if (board[i][j].c == 'e')
					board[r][c].attractiveness += 2;
				else if (board[i][j].c == 'r')
					board[r][c].attractiveness -= 2;
		}
		gotoxy(1, i + 2);
	}
}

int checkAttractiveness(chunk** board, int rows, int cols) {
	int population = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (board[i][j].c == 'w') {
				board[i][j].attractiveness = 0;
				checkNeigbours(board, i, j, rows, cols);
				board[i][j].population += board[i][j].attractiveness;

				if (board[i][j].population < 0) board[i][j].population = 0;
				if (board[i][j].population > 100) board[i][j].population = 100;
				population += board[i][j].population;
			}
		}
		gotoxy(1, i + 2);
	}
	return population;
}

double getTime(LARGE_INTEGER t1) {

	LARGE_INTEGER freq, t2;
	QueryPerformanceCounter(&t2);
	QueryPerformanceFrequency(&freq);
	return (t2.QuadPart - t1.QuadPart) / (double)freq.QuadPart;
}

void printMenu(chunk** board, int rows, int cols, LARGE_INTEGER t1, int x, int y, int money) {
	ShowConsoleCursor(0);
	double elapsedTime = getTime(t1);
	gotoxy(0, rows+2);
	printf("Dzien: %d \nGodzina: %02d \n", (int)(elapsedTime / 24), (int)elapsedTime % 24);
	printf("Budzet: %d\n", money);
	if (((int)elapsedTime % 24) == 0) {
		int population = checkAttractiveness(board, rows, cols);
		gotoxy(0, rows + 5);
		printf("Populacja: %d              ", population);
	}
	gotoxy(x, y);
	ShowConsoleCursor(1);
}

void SimplePrintScreen(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money) {
	
	ShowConsoleCursor(0);
	gotoxy(1, 1);

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {

			if (board[i][j].c == 'q')
				printf("%c", drawRoad(board, i, j, rows, cols));

			else {
				char c = 176;

				if (board[i][j].population == 100) c = 178;
				else if (board[i][j].population > 50) c = 177;

				if (board[i][j].c == 'w')
					printf(GRN "%c" RST, c);
				else if (board[i][j].c == 'e')
					printf(BLU "%c" RST, c);
				else if (board[i][j].c == 'r')
					printf(YEL "%c" RST, c);
				else
					putc(board[i][j].c, stdout);
			}
		}
		gotoxy(1, i+2);
	}
	printMenu(board, rows, cols, t1, 1, 1, money);
	ShowConsoleCursor(1);
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
