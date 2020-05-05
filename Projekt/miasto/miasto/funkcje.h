#ifndef FUNKCJE_H

#define FUNKCJE_H

char** createBoard(int rows, int cols);

void setBorders(char** board, int rows, int cols);

void arrowsHandling(int* x, int* y, int* c, int rows, int cols);

void ShowConsoleCursor(int showFlag);

void gotoxy(int x, int y);

void SimplePrintScreen(char** board, int rows, int cols);

#endif

