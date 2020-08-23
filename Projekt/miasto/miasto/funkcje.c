/*! \file
	\brief Plik zawiera definicje funkcji*/
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
#include "memorilo.h"

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

	chunk** board = malloc(rows * sizeof(chunk*));

	for (int i = 0; i < rows; i++) {
		board[i] = malloc(cols * sizeof(chunk));
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
	gotoxy((cols / 2) + 1, rows + 1);
	putc(186, stdout);
}

void printHelp(int cols) {

	gotoxy(cols + 3, 1);
	printf("Strzalki - sterowanie");
	gotoxy(cols + 3, 2);
	printf("q - Budowa drogi");
	gotoxy(cols + 3, 3);
	printf("w - Budowa dzielnicy mieszkalnej");
	gotoxy(cols + 3, 4);
	printf("e - Budowa dzielnicy uslugowej");
	gotoxy(cols + 3, 5);
	printf("r - Budowa dzielnicy przemyslowej");
	gotoxy(cols + 3, 6);
	printf("d - Burzenie");
	gotoxy(cols + 3, 7);
	printf("p - Wyjscie z gry");

}

void arrowsHandling(int* x, int* y, int c, int maxx, int maxy, int minx, int miny) {
	
	c = _getch();
	switch (c) {
	case 0x4B:
		if (*x != minx) (*x)--;
		break;
	case 0x4D:
		if (*x != maxx) (*x)++;
		break;
	case 0x48:
		if (*y != miny) (*y)--;
		break;
	case 0x50:
		if (*y != maxy) (*y)++;
		break;
	default:
		break;
	}
}

bool isValid(int x, int y, int rows, int cols) {			//x kolumny(j), y wiersze(i)

	if ((x >= 0 && x < cols) && (y >= 0 && y < rows))		//czy pole le¿y w obrêbie planszy
		return 1;
	return 0;
}

int drawRoad(chunk** board, int i, int j, int rows, int cols) {

	bool n = 0, e = 0, s = 0, w = 0;
	if (isValid(j, i - 1, rows, cols))
		if (board[i - 1][j].c == 'q')
			n = 1;
	if (isValid(j + 1, i, rows, cols))
		if (board[i][j + 1].c == 'q')
			e = 1;
	if (isValid(j, i + 1, rows, cols))
		if (board[i + 1][j].c == 'q')
			s = 1;
	if (isValid(j - 1, i, rows, cols))
		if (board[i][j - 1].c == 'q')
			w = 1;

	if (j == cols / 2 && i == rows - 1)		//wyjazd
		s = 1;

	int c = 186;							//³¹czenie dróg (dobieranie odpowiedniego znaku ascii)
	if (n & e & s & w) c = 206;
	else if (n & s & w) c = 185;
	else if (n & e & w) c = 202;
	else if (n & e & s) c = 204;
	else if (e & s & w) c = 203;
	else if (n & w) c = 188;
	else if (n & e) c = 200;
	else if (e & s) c = 201;
	else if (s & w) c = 187;
	else if (e | w) c = 205;
	return c;
}

void checkNeigboursResidential(chunk** board, int r, int c, int rows, int cols) {

	for (int i = r - 2; i <= r + 2; i++) {
		for (int j = c - 2; j <= c + 2; j++) {
			if (isValid(j, i, rows, cols))
				if (board[i][j].c == 'e')
					board[r][c].attractiveness += 2;
				else if (board[i][j].c == 'r')
					board[r][c].attractiveness -= 2;
		}
		gotoxy(1, i + 2);
	}
}

void checkNeigboursService(chunk** board, int r, int c, int rows, int cols) {

	for (int i = r - 2; i <= r + 2; i++) {
		for (int j = c - 2; j <= c + 2; j++) {
			if (isValid(j, i, rows, cols))
				if (board[i][j].c == 'w')
					board[r][c].attractiveness += 2;
				else if (board[i][j].c == 'e')
					board[r][c].attractiveness -= 1;
				else if (board[i][j].c == 'r')
					board[r][c].attractiveness += 1;
		}
		gotoxy(1, i + 2);
	}
}

void checkNeigboursIndustrial(chunk** board, int r, int c, int rows, int cols) {

	for (int i = r - 2; i <= r + 2; i++) {
		for (int j = c - 2; j <= c + 2; j++) {
			if (isValid(j, i, rows, cols))
				if (board[i][j].c == 'w')
					board[r][c].attractiveness -= 1;
				else if (board[i][j].c == 'e')
					board[r][c].attractiveness += 1;
				else if (board[i][j].c == 'r')
					board[r][c].attractiveness += 1;
		}
		gotoxy(1, i + 2);
	}
}

void checkAttractiveness(chunk** board, int rows, int cols) {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (board[i][j].c == 'w' || board[i][j].c == 'e' || board[i][j].c == 'r') {

				board[i][j].attractiveness = 0;

				if (board[i][j].c == 'w') checkNeigboursResidential(board, i, j, rows, cols);
				else if (board[i][j].c == 'e') checkNeigboursService(board, i, j, rows, cols);
				else if (board[i][j].c == 'r') checkNeigboursIndustrial(board, i, j, rows, cols);

				board[i][j].population += board[i][j].attractiveness;

				if (board[i][j].population < 0) board[i][j].population = 0;
				if (board[i][j].population > 100) board[i][j].population = 100;
			}
		}
		gotoxy(1, i + 2);
	}
}


double getTime(LARGE_INTEGER t1, int time) {

	LARGE_INTEGER freq, t2;
	QueryPerformanceCounter(&t2);
	QueryPerformanceFrequency(&freq);
	return ((t2.QuadPart - t1.QuadPart) / (double)freq.QuadPart) + time;
}


int countPopulation(chunk** board, int rows, int cols) {
	int population = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			population += board[i][j].population;
		}
	}
	return population;
}

void printMenu(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money, int population, int time) {
	double elapsedTime = getTime(t1, time);

	gotoxy(0, rows + 3);
	printf("Dzien: %d \nGodzina: %02d \n", (int)(elapsedTime / 24), (int)elapsedTime % 24);
	printf("Budzet: %-20d\n", money);
	printf("Populacja: %-20d", population);
}

void renderBoard(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money) {
	
	ShowConsoleCursor(0);
	gotoxy(1, 1);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

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
	ShowConsoleCursor(1);
}

void newWallet(int diff, budget** wallet) {

	budget* new_wallet = (budget*)malloc(sizeof(budget));
	new_wallet->money = (*wallet)->money + diff;
	new_wallet->next = *wallet;
	*wallet = new_wallet;
}

void buildRoad(chunk** board, int x, int y, struct budget** wallet) {

	if ((*wallet)->money >= 2000 && board[y][x].c != 'q') {
		newWallet(-2000, wallet);
		board[y][x].c = 'q';
		board[y][x].population = 0;
	}
}

void setZone(chunk** board, int x, int y, int c, struct budget** wallet) {
	if (board[y][x].c != c) {
		board[y][x].population = 0;
		board[y][x].attractiveness = 0;
	}

	if (board[y][x].c == 'q')
		newWallet(1000, wallet);
	board[y][x].c = c;
}

void calcTaxes(int population, budget** wallet) {
	int taxes = 0;
	if (population < 2000)
		taxes = population * 4;
	else
		taxes = population * 2;
	newWallet(taxes, wallet);
}

int printStartingMenu() {

	printf("Witaj w grze \"Miasto\"\n\nWybierz, co chcesz zrobic: \n");
	printf(" 1. Nowa gra\n");
	printf(" 2. Wczytaj gre\n");
	printf(" 3. Wyjdz\n");
	int x = 1, y = 3;
	gotoxy(x, y);

	while (1) {
		int c = _getch();
		if (c == 0xE0)
			arrowsHandling(&x, &y, c, 1, 5, 1, 3);
		else if (c == 13)
			return y - 2;
		gotoxy(x, y);
	}
}

chunk** newGame(int* rows, int* cols, budget** wallet) {

	bool width = false, height = false;
	int clr;
	system("cls");
	printf("Podaj rozmiar miasta\n");

	while (!width) {
		printf("Szerokosc: ");
		if (scanf("%d", cols))
			width = true;
		while (clr = getchar() != '\n');
	}
	while (!height) {
		printf("Wysokosc: ");
		if (scanf("%d", rows))
			height = true;
		while (clr = getchar() != '\n');
	}
	chunk** board = createBoard(*rows, *cols);
	(*wallet) = (budget*)malloc(sizeof(budget));
	(*wallet)->money = 50000;
	(*wallet)->next = NULL;
	return board;
}

void saveBudget(FILE** file, budget* wallet) {
	budget* temp = wallet;
	if (temp == NULL)
		return;
	saveBudget(file, wallet->next);
	fwrite(&wallet->money, sizeof(int), 1, (*file));
}

void getSaveName(char* saveName) {

	system("cls");
	printf("Podaj nazwe zapisu: ");
	scanf("%s", saveName);

	if (strcmp(strrchr(saveName, '\0') - 4, ".bin"))				//dodanie rozszerzenia, je¿eli go nie ma
		strcat(saveName, ".bin");
}

void saveGame(chunk** board, int* rows, int* cols, budget* wallet, int* timeToSave) {

	char saveName[50] = "";
	char checkString[] = "Miasto";
	getSaveName(saveName);

	FILE* file = fopen(saveName, "wb");

	if (file == NULL)
		saveGame(board, rows, cols, wallet, timeToSave);

	fwrite(&checkString, sizeof(char), 7, file);
	fwrite(rows, sizeof(int), 1, file);
	fwrite(cols, sizeof(int), 1, file);
	fwrite(timeToSave, sizeof(LARGE_INTEGER), 1, file);

	for (int i = 0; i < (*rows); i++) {								//zapisanie tablicy
		for (int j = 0; j < (*cols); j++)
			fwrite(&board[i][j], sizeof(chunk), 1, file);
	}

	saveBudget(&file, wallet);
	fclose(file);
}

bool validateFile(FILE** file) {

	if ((*file) == NULL)			//czy plik siê otworzy³
		return false;

	char checkString[7] = "";
	if (fread(&checkString, sizeof(char), 7, (*file)) == 7) {
		if (!strcmp(checkString, "Miasto"))							//czy ma kontrolnego stringa
			return true;
	}

	fclose(*file);
	return false;
}

chunk** loadGame(int* rows, int* cols, budget** wallet, int* time) {

	char saveName[50] = "";
	getSaveName(saveName);

	FILE* file = fopen(saveName, "rb");

	if (!validateFile(&file))
		return NULL;

	fread(rows, sizeof(int), 1, file);
	fread(cols, sizeof(int), 1, file);
	fread(time, sizeof(LARGE_INTEGER), 1, file);

	chunk** board = createBoard((*rows), (*cols));				//alokacja tablicy

	for (int i = 0; i < (*rows); i++) {							//odczyt tablicy
		for (int j = 0; j < (*cols); j++)
			fread(&board[i][j], sizeof(chunk), 1, file);
	}

	int val = 0;
	while (fread(&val, sizeof(int), 1, file) == 1) {			//odczyt bud¿etu
		budget* new_wallet = (budget*)malloc(sizeof(budget));
		new_wallet->money = val;
		new_wallet->next = *wallet;
		*wallet = new_wallet;
	}
	return board;
}

int exitGame() {

	system("cls");
	printf("Czy chcesz zapisac gre?\n\n");
	printf(" 1. Tak\n");
	printf(" 2. Nie\n");
	int x = 1, y = 2;
	gotoxy(x, y);

	while (1) {

		int c = _getch();
		if (c == 0xE0)
			arrowsHandling(&x, &y, c, 1, 3, 1, 2);
		else if (c == 13)
			return y - 1;
		
		gotoxy(x, y);
	}
}

void freeBoard(chunk** board, int rows) {

	for (int i = 0; i < rows; i++)
		free(board[i]);
	free(board);
}

void freeBudget(budget* wallet) {

	while (wallet != NULL) {
		budget* temp = wallet;
		wallet = wallet->next;
		free(temp);
	}
}

