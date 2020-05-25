#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#include "funkcje.h"
#include "struktury.h"

int main() {
	ShowConsoleCursor(1);
	LARGE_INTEGER t1;
	QueryPerformanceCounter(&t1);


	int rows = 13 + 2, cols = 31 + 2;
	char** board = createBoard(rows, cols);

	budget* wallet = calloc(1, sizeof(budget));
	wallet->money = 19999;

	setBorders(board, rows, cols);
	int x = 1, y = 1;

	while (1)
	{

		SimplePrintScreen(board, rows, cols, t1, wallet->money);
		
		while (!_kbhit())
			printMenu(rows, t1, x, y, wallet->money);
		
		int c = _getch();

		if (c == 0xE0)
			arrowsHandling(&x, &y, c, rows, cols);
		if (c == 'q')
			buildRoad(board, x, y, &wallet);
		if (c == 'w')
			board[y][x] = 'w';
		if (c == 'e')
			board[y][x] = 'e';
		if (c == 'x')
			drawingTool(board, &x, &y, rows, cols, t1, &wallet);
		if (c == 'd') {
			if(board[y][x] == 'q')
				newWallet(1000, &wallet);
			board[y][x] = '\0';
		}
	}

}
