/*! \file
	\brief Plik zawiera g³ówn¹ funkcjê gry */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "funkcje.h"
#include "struktury.h"
#include "memorilo.h"


int main() {

	while (1) {
		system("cls");
		gotoxy(0, 0);

		int rows, cols;
		chunk** board = NULL;
		budget* wallet = NULL;
		LARGE_INTEGER t1;
		int time = 0;

		while (board == NULL) {

			switch (printStartingMenu()) {					//wybór z menu g³ównego
			case 1:
				board = newGame(&rows, &cols, &wallet);
				break;
			case 2:
				board = loadGame(&rows, &cols, &wallet, &time);
				break;
			default:
				return 0;
			}

			system("cls");
			gotoxy(0, 0);
		}

		ShowConsoleCursor(1);
		QueryPerformanceCounter(&t1);	//timer gry - start

		printBorders(rows, cols);		//rysowanie granic miasta
		printHelp(cols);				//pomoc

		int x = 1, y = 1;
		int timeLast = 0;
		renderBoard(board, rows, cols, t1, wallet->money);				//wstêpne wyœwietlenie miasta
		printMenu(board, rows, cols, t1, wallet->money, countPopulation(board, rows, cols), time);  //wstêpne wyœwietlenie menu

		while (1) {
			while (!_kbhit()) {							//gdy uzytkownik nic nie naciska

				int timeNow = (int)getTime(t1, time);
				int population = countPopulation(board, rows, cols);

				if (timeNow != timeLast) {				//ograniczenie odœwie¿ania, w ka¿dym nowym dniu podatki + sprawdzanie atrakcyjnoœci/populacji
					if (timeNow % 24 == 0) {
						calcTaxes(population, &wallet);				//pobranie podatków
						checkAttractiveness(board, rows, cols);		//sprawdzanie atrakcyjnoœci i populacji
						roadCosts(board, rows, cols, &wallet);		//utrzymanie dróg
						if (wallet->money < -5000)					//sprawdzenie czy gracz nie zbankrutowa³
							break;
					}

					renderBoard(board, rows, cols, t1, wallet->money);
					printMenu(board, rows, cols, t1, wallet->money, population, time);
					timeLast = timeNow;
				}
				gotoxy(x, y);
			}
			
			if (wallet->money < -5000) {
				bankrupt(board, rows, wallet);
				break;
			}

			int c = _getch();							//gdy uzytkownik nacisnie klawisz
			if (c == 0xE0) {
				arrowsHandling(&x, &y, c, cols, rows, 1, 1);
				printMenu(board, rows, cols, t1, wallet->money, countPopulation(board, rows, cols), time);
			}

			else {
				if (c == 'q')
					buildRoad(board, x - 1, y - 1, &wallet);
				else if (c == 'w' || c == 'e' || c == 'r')
					setZone(board, x - 1, y - 1, c, &wallet);
				else if (c == 'd') {
					c = '\0';
					setZone(board, x - 1, y - 1, c, &wallet);
				}
				else if (c == 'p') {								//wyjscie z gry
					if (exitGame() == 1) {							//czy zapisaæ?
						int timeToSave = (int)getTime(t1, time);	
						saveGame(board, &rows, &cols, wallet, &timeToSave);
					}

					freeBoard(board, rows);			//zwalnianie pamiêci
					freeBudget(wallet);
					break;
				}
				renderBoard(board, rows, cols, t1, wallet->money);
			}
		}
	}
}
