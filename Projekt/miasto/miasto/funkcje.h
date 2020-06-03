#ifndef FUNKCJE_H

#define FUNKCJE_H

#include <stdbool.h>
#include "struktury.h"

chunk** createBoard(int rows, int cols);

void printBorders(int rows, int cols);

void printHelp(int cols);

void arrowsHandling(int* x, int* y, int c, int rows, int cols);

void ShowConsoleCursor(int showFlag);

void gotoxy(int x, int y);

int drawRoad(chunk** board, int i, int j, int rows, int cols);

void renderBoard(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money);

double getTime(LARGE_INTEGER t1);

int countPopulation(chunk** board, int rows, int cols);

void printMenu(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money, int population);

void buildRoad(chunk** board, int x, int y, budget** wallet);

void newWallet(int diff, budget** wallet);

void setZone(chunk** board, int x, int y, int c, struct budget** wallet);

bool isValid(int x, int y, int rows, int columns);

void checkAttractiveness(chunk** board, int rows, int cols);

void checkNeigboursResidential(chunk** board, int r, int c, int rows, int cols);

void checkNeigboursService(chunk** board, int r, int c, int rows, int cols);

void checkNeigboursIndustrial(chunk** board, int r, int c, int rows, int cols);

void calcTaxes(int population, budget** wallet);


#endif

