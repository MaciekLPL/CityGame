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
	chunk** board = createBoard(rows, cols);

	budget* wallet = calloc(1, sizeof(budget));
	wallet->money = 199999;

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
		else if (c == 'q')
			buildRoad(board, x, y, &wallet);
		else if (c == 'w' || c == 'e' || c == 'r')
			setZone(board, x, y, c, &wallet);
		else if (c == 'd') {
			c = '\0';
			setZone(board, x, y, c, &wallet);
		}
	}
}
