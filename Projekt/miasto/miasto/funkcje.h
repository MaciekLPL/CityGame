#ifndef FUNKCJE_H

#define FUNKCJE_H

#include <stdbool.h>

char** createBoard(int rows, int cols);

void setBorders(char** board, int rows, int cols);

void arrowsHandling(int* x, int* y, int c, int rows, int cols);

void drawingTool(char** board, int* x, int* y, int rows, int cols, LARGE_INTEGER t1, struct budget** wallet);

void ShowConsoleCursor(int showFlag);

void gotoxy(int x, int y);

int drawRoad(char** board, int i, int j, int rows);

void SimplePrintScreen(char** board, int rows, int cols, LARGE_INTEGER t1, int money);

double getTime(LARGE_INTEGER t1);

void printMenu(int rows, LARGE_INTEGER t1, int x, int y, int money);

void fillBoard(char** board, int x1, int x2, int y1, int y2, int c, struct budget** wallet);

bool buildRoad(char** board, int x, int y, struct budget** wallet);

void newWallet(int diff, struct budget** wallet);

#endif

