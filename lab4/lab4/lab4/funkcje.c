#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funkcje.h"


void zamien(char* napis) {

	int l = strlen(napis);

	for (int i = 0; i < l; i++) {
		napis[i] = isupper(napis[i]) ? tolower(napis[i]) : toupper(napis[i]);
	}
}

void wypisz(char* napis) {

	int l = strlen(napis);

	for (int i = 0; i < l; i++) {
		printf("%c", napis[i]);
	}
}

void dataNapis(char* str, int d, int m, int r) {
	sprintf(str, "%d-%02d-%02d", r, m, d);
}

bool napisData(char* str, int* d, int* m, int* r) {

	if (str[4] != '-' || str[7] != '-')
		return false;

	sscanf(str, "%d-%d-%d", r, m, d);
	return true;
}

void wstaw(char* napis, char* znaki, int ilosc) {
	memmove(napis + ilosc, napis, strlen(napis) + 1);
	memmove(napis, znaki, ilosc);
}