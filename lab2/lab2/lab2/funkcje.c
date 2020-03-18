#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"


int** create2Darray(int R, int C) {

	int** tab = calloc(R, sizeof(int*));

	for (int i = 0; i < R; i++) {
		tab[i] = calloc(C, sizeof(int));
	}

	srand(time(NULL));

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			tab[i][j] = rand() % 10;
		}
	}

	return tab;
}

void displayArray(int** tab, int R, int C) {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf_s("%d ", tab[i][j]);
		}
		printf_s("\n");
	}
}

void deleteArray(int** tab, int R) {

	for (int i = 0; i < R; i++) {
		free(tab[i]);
	}
	free(tab);
	tab = NULL;
}

int* createArray() {

	int liczba;
	int ilosc = 0;
	int* tab = NULL;
	scanf_s("%d", &liczba);

	while (liczba != 0) {
		ilosc++;
		tab = realloc(tab, ilosc * sizeof(int));
		tab[ilosc - 1] = liczba;
		scanf_s("%d", &liczba);
	}

	for (int i = 0; i < ilosc; i++) {
		printf_s("%d ", tab[i]);
	}
	return tab;
}

