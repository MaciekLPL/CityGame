#ifndef FUNKCJE_H

#define FUNKCJE_H

#include <stdbool.h>
#include "struktury.h"

chunk** createBoard(int rows, int cols);

void printBorders(int rows, int cols);

void arrowsHandling(int* x, int* y, int c, int rows, int cols);

void ShowConsoleCursor(int showFlag);

void gotoxy(int x, int y);

int drawRoad(chunk** board, int i, int j, int rows, int cols);

void SimplePrintScreen(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money);

double getTime(LARGE_INTEGER t1);

void printMenu(chunk** board, int rows, int cols, LARGE_INTEGER t1, int x, int y, int money);

void buildRoad(chunk** board, int x, int y, budget** wallet);

void newWallet(int diff, budget** wallet);

void setZone(chunk** board, int x, int y, int c, struct budget** wallet);

bool isValid(int x, int y, int rows, int columns);

int checkAttractiveness(chunk** board, int rows, int cols);

void checkNeigbours(chunk** board, int r, int c, int rows, int cols);

#endif

