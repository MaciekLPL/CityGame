#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#include "funkcje.h"
#include "struktury.h"

int main() {

	int num = printStartingMenu();

	int rows, cols;
	chunk** board = NULL;
	budget* wallet = calloc(1, sizeof(budget));
	LARGE_INTEGER t1;

	if (num == 1)
		board = newGame(&rows, &cols, board, &wallet);
	else if (num == 2)
		;
	else
		return 0;

	system("cls");
	gotoxy(0, 0);
	ShowConsoleCursor(1);
	QueryPerformanceCounter(&t1);

	printBorders(rows, cols);		//rysowanie granic miasta
	printHelp(cols);				//pomoc

	int x = 1, y = 1;
	int timeLast = 0;
	renderBoard(board, rows, cols, t1, wallet->money);				//wst�pne wy�wietlenie miasta
	printMenu(board, rows, cols, t1, wallet->money, countPopulation(board, rows, cols));  //wst�pne wy�wietlenie menu
	
	while (1)
	{
		while (!_kbhit()) {

			int timeNow = (int)getTime(t1);
			int population = countPopulation(board, rows, cols);

			if (timeNow != timeLast) {				//ograniczenie od�wie�ania, w ka�dym nowym dniu podatki + sprawdzanie atrakcyjno�ci/populacji
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

			arrowsHandling(&x, &y, c, cols, rows, 1, 1);
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
			else if (c == 'p') {
				if (exitGame() == 1)
					saveGame();
				return 0;
			}

			renderBoard(board, rows, cols, t1, wallet->money);
		}
		
	}
}
