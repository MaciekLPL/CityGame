#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funkcje.h"
#include "struktury.h"

double procent(double K, double n, double p, double k) {
	return K * pow(p / (100 * k) + 1, n * k);
}

void funkcja() {

	char imie[16];
	double K, n, p, k;
	int l;

	if (scanf("%15s %lf %lf %lf %lf %d", imie, &K, &n, &p, &k, &l) != 6) {
		printf("DUPA ERROR CODE");
	}
	else {
		printf("%s %.*f", imie, l, procent(K, n, p, k));
	}
	
	

}
