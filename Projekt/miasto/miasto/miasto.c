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
	wallet->money = 20000;

	printBorders(rows, cols);
	int x = 1, y = 1;
	int timeLast = 0;
	SimplePrintScreen(board, rows, cols, t1, wallet->money);
	printMenu(board, rows, cols, t1, x, y, wallet->money);
	
	while (1)
	{
		while (!_kbhit()) {
			int timeNow = (int)getTime(t1);
			if (timeNow != timeLast) {					//ograniczenie odœwie¿ania, nie dotykaæ póki dzia³a
				SimplePrintScreen(board, rows, cols, t1, wallet->money);
				printMenu(board, rows, cols, t1, x, y, wallet->money);
				timeLast = timeNow;
			}
			gotoxy(x, y);
		}

		int c = _getch();

		if (c == 0xE0) {
			arrowsHandling(&x, &y, c, rows, cols);
			printMenu(board, rows, cols, t1, x, y, wallet->money);
		}
		else {
			if (c == 'q')
				buildRoad(board, x-1, y-1, &wallet);
			else if (c == 'w' || c == 'e' || c == 'r')
				setZone(board, x-1, y-1, c, &wallet);
			else if (c == 'd') {
				c = '\0';
				setZone(board, x-1, y-1, c, &wallet);
			}
			SimplePrintScreen(board, rows, cols, t1, wallet->money);
		}
		
	}
}
