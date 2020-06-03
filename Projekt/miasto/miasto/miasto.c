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

	int rows = 15, cols = 35;		//wielkoœc miasta
	chunk** board = createBoard(rows, cols);

	budget* wallet = calloc(1, sizeof(budget));
	wallet->money = 50000;			//iloœæ pieniêdzy

	printBorders(rows, cols);		//granice miasta
	printHelp(cols);				//pomoc

	int x = 1, y = 1;
	int timeLast = 0;
	renderBoard(board, rows, cols, t1, wallet->money);				//wstêpne wyœwietlenie
	printMenu(board, rows, cols, t1, wallet->money, countPopulation(board, rows, cols));
	


	while (1)
	{
		while (!_kbhit()) {

			int timeNow = (int)getTime(t1);
			int population = countPopulation(board, rows, cols);

			if (timeNow != timeLast) {				//ograniczenie odœwie¿ania, w ka¿dym nowym dniu podatki + sprawdzanie atrakcyjnoœci/populacji
				if (timeNow % 24 == 0) {
					calcTaxes(population, &wallet);
					checkAttractiveness(board, rows, cols);
				}

				renderBoard(board, rows, cols, t1, wallet->money);
				printMenu(board, rows, cols, t1, wallet->money, population);
				timeLast = timeNow;
			}
			gotoxy(x, y);
		}

		int c = _getch();
		if (c == 0xE0) {

			arrowsHandling(&x, &y, c, rows, cols);
			printMenu(board, rows, cols, t1, wallet->money, countPopulation(board, rows, cols));
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
			renderBoard(board, rows, cols, t1, wallet->money);
		}
		
	}
}
