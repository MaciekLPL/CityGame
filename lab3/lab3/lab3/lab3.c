#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"
#include "struktury.h"

int main() {

	//samogloski();
	//podziel();
	
	Osoba tab[3] = { { 11, "D" }, { 22, "DUPA2" }, { 3322222, "Duuuureuhreigurejfdkfdgfd" } };
	zapisz(tab, 3);
	Osoba* tab2;
	int n;
	wczytaj(&tab2, &n);
	return 0;
}
