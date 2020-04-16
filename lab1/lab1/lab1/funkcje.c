#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funkcje.h"
#include "struktury.h"

double procent(double K, double n, double p, double k) {
	
	double s = pow(p/(100*k) + 1, n * k);
	return K * s;

}