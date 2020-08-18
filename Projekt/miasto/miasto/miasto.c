#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#include "funkcje.h"
#include "struktury.h"
#include "memorilo.h"
#include <stdlib.h>
#include <crtdbg.h>


int main() {
	int num = printStartingMenu();

	int rows, cols;
	chunk** board = NULL;
	budget* wallet = (budget*)malloc(sizeof(budget));
	LARGE_INTEGER t1;
	int time = 0;

	if (num == 1) {
		board = newGame(&rows, &cols, board, &wallet);
	}
	else if (num == 2)
		board = loadGame(&rows, &cols, &wallet, &time);
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
	renderBoard(board, rows, cols, t1, wallet->money);				//wstêpne wyœwietlenie miasta
	printMenu(board, rows, cols, t1, wallet->money, countPopulation(board, rows, cols), time);  //wstêpne wyœwietlenie menu
	
	while (1)
	{
		while (!_kbhit()) {

			int timeNow = (int)getTime(t1, time);
			int population = countPopulation(board, rows, cols);

			if (timeNow != timeLast) {				//ograniczenie odœwie¿ania, w ka¿dym nowym dniu podatki + sprawdzanie atrakcyjnoœci/populacji
				if (timeNow % 24 == 0) {
					calcTaxes(population, &wallet);
					checkAttractiveness(board, rows, cols);
				}

				renderBoard(board, rows, cols, t1, wallet->money);
				printMenu(board, rows, cols, t1, wallet->money, population, time);
				timeLast = timeNow;
			}
			gotoxy(x, y);
		}

		int c = _getch();
		if (c == 0xE0) {

			arrowsHandling(&x, &y, c, cols, rows, 1, 1);
			printMenu(board, rows, cols, t1, wallet->money, countPopulation(board, rows, cols), time);
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
				if (exitGame() == 1) {
					int timeToSave = (int)getTime(t1, time);
					saveGame(board, &rows, &cols, wallet, &timeToSave);
				}
				deleteBoard(board, rows);
				freeBudget(wallet);
				wallet = NULL;
				return 0;
			}
			renderBoard(board, rows, cols, t1, wallet->money);
		}
	}
}
