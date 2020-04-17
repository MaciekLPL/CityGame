#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"
#include "struktury.h"


void samogloski() {

	char napis[20];
	//scanf_s("%s", napis, _countof(napis));
	fgets(napis, 254, stdin);

	char litery[] = "a¹eêiouy";
	char* ptr = strpbrk(napis, litery);

	while (ptr != NULL) {
		printf_s("%d \n", ptr - napis);
		ptr = strpbrk(ptr+1, litery);
	}

}

void podziel() {

	char napisy[10][6] = { 0 };
	char napis[254];
	fgets(napis, 254, stdin);
	char znaki[] = " .?,!:-;";
	int i = 0;
	char* ptr = strtok(napis, znaki);
	
	while (ptr != NULL && i < 10) {
		strncpy(napisy[i], ptr, 5);
		ptr = strtok(NULL, znaki);
		i++;
	}

	for (int i = 0; i < 10; i++) {
		printf_s("%s \n", napisy[i]);
	}
}

void zapisz(Osoba* osoby, int n) {

	FILE* file = fopen("output.bin", "wb");
	if (file != NULL) {
		fwrite(&n, sizeof(int), 1, file);
		for (int i = 0; i < n; i++) {
			int l = strlen(osoby[i].imie) + 1;
			fwrite(&l, sizeof(int), 1, file);
			fwrite(&osoby[i], sizeof(int) + sizeof(char) * l, 1, file);
		}
	}

	fclose(file);
}

void wczytaj(Osoba** osoby, int* n) {

	FILE* file2 = fopen("output.bin", "rb");
	if (file2 != NULL) {
		fread(n, sizeof(int), 1, file2);
		int size;
		osoby = calloc(*n, sizeof(Osoba*));
		for (int i = 0; i < *n; i++) {
			fread(&size, sizeof(int), 1, file2);
			osoby[i] = malloc(sizeof(int) + sizeof(char) * size);
			fread(&osoby[i], sizeof(int) + sizeof(char) * size, 1, file2);
		}
	}
	fclose(file2);
}