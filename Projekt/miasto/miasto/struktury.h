#ifndef STRUKTURY_H

#define STRUKTURY_H

#include <stdbool.h>

typedef struct chunk {
	int c;
	int population;
	int attractiveness;

}chunk;

typedef struct budget {
	int money;
	struct budget* next;
}budget;

#endif