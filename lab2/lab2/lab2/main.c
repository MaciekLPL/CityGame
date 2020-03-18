#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"

int main() {
	
	//Zadanie 1 i 4
	int R, C;
	scanf_s("%d %d", &R, &C);

	int** tab = create2Darray(R, C);
	displayArray(tab, R, C);
	deleteArray(tab, R);

	//Zadanie 2
	int* tab2 = createArray();
	deleteArray(tab2, 0);

	return 0;

}