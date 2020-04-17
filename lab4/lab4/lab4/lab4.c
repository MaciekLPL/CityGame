#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funkcje.h"

int main() {

	char napis[] = "Dupa dUPA";
	zamien(napis);
	wypisz(napis);

	char data[11];
	dataNapis(data, 20, 04, 2020);
	wypisz(data);

	int d, m, r;
	if(napisData(data, &d, &m, &r))
		printf("%d %d %d", d, m, r);
	
	char napis2[20] = "ma kota";
	char znaki[] = "ala ";
	wstaw(napis2, znaki, strlen(znaki));


}