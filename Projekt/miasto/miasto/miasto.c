#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "funkcje.h"
#include "struktury.h"

int main() {
	ShowConsoleCursor(1);

	int rows = 27 + 2, cols = 50 + 2;
	char** board = createBoard(rows, cols);

	setBorders(board, rows, cols);

	int x = 1, y = 1;

	while (1)
	{
		SimplePrintScreen(board, rows, cols);

		gotoxy(x, y);

		//int ax = _kbhit(); // ta funkcja sie moze gdzies tez Panu przydac
		int c = _getch();

		if (c == 0xE0)
			arrowsHandling(&x, &y, &c, rows, cols);
		if (c == 'q')
			board[y][x] = 'q';
		if (c == 'r')
			board[y][x] = 'r';
		if (c == 's')
			board[y][x] = 's';
		if (c == 'i')
			board[y][x] = 'i';
		if (c == 'd')
			board[y][x] = NULL;

	}

}
