#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"
#include "struktury.h"

int main() {
	
	//Zadanie 1 i 4
	//int R, C;
	//scanf_s("%d %d", &R, &C);

	//int** tab = create2Darray(R, C);
	//displayArray(tab, R, C);
	//deleteArray(tab, R);

	////Zadanie 2
	//int* tab2 = createArray();
	//deleteArray(tab2, 0);

	//Zadanie 3

	//listElement* tab[5] = { 0 };

	listElement** tab = calloc(5, sizeof(int*));


	tablicaMieszajacaWstawianie(tab, 5, 1);
	tablicaMieszajacaWstawianie(tab, 5, 2);
	tablicaMieszajacaWstawianie(tab, 5, 3);
	tablicaMieszajacaWstawianie(tab, 5, 4);
	tablicaMieszajacaWstawianie(tab, 5, 1);
	tablicaMieszajacaWstawianie(tab, 5, 0);

	wypiszElementy(tab, 5);

	usunElementy(tab, 5);

	return 0;

}