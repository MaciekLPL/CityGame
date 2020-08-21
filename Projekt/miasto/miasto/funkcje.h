#ifndef FUNKCJE_H

#define FUNKCJE_H

#include <stdbool.h>
#include "struktury.h"

chunk** createBoard(int rows, int cols);

void printBorders(int rows, int cols);

void printHelp(int cols);

void arrowsHandling(int* x, int* y, int c, int maxx, int maxy, int minx, int miny);

void ShowConsoleCursor(int showFlag);

void gotoxy(int x, int y);

int drawRoad(chunk** board, int i, int j, int rows, int cols);

void renderBoard(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money);

double getTime(LARGE_INTEGER t1, int time);

int countPopulation(chunk** board, int rows, int cols);

void printMenu(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money, int population, int time);

void buildRoad(chunk** board, int x, int y, budget** wallet);

void newWallet(int diff, budget** wallet);

void setZone(chunk** board, int x, int y, int c, struct budget** wallet);

bool isValid(int x, int y, int rows, int columns);

void checkAttractiveness(chunk** board, int rows, int cols);

void checkNeigboursResidential(chunk** board, int r, int c, int rows, int cols);

void checkNeigboursService(chunk** board, int r, int c, int rows, int cols);

void checkNeigboursIndustrial(chunk** board, int r, int c, int rows, int cols);

void calcTaxes(int population, budget** wallet);

int printStartingMenu();

void getSaveName(char* saveName);

chunk** newGame(int* rows, int* cols, chunk** board, budget** wallet);

bool validateFile(FILE** file);

chunk** loadGame(int* rows, int* cols, budget** wallet, int* time);

void saveBudget(FILE** file, budget* wallet);

void saveGame(chunk** board, int* rows, int* cols, budget* wallet, int* timeToSave);

void freeBoard(chunk** board, int rows);

void freeBudget(budget* wallet);

int exitGame();


#endif

