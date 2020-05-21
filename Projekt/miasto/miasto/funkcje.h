#ifndef FUNKCJE_H

#define FUNKCJE_H

char** createBoard(int rows, int cols);

void setBorders(char** board, int rows, int cols);

void arrowsHandling(int* x, int* y, int c, int rows, int cols);

void drawingTool(char** board, int* x, int* y, int rows, int cols, LARGE_INTEGER t1);

void ShowConsoleCursor(int showFlag);

void gotoxy(int x, int y);

int drawRoad(char** board, int i, int j, int rows);

void SimplePrintScreen(char** board, int rows, int cols, LARGE_INTEGER t1);

void printMenu(int rows, LARGE_INTEGER t1);

#endif

