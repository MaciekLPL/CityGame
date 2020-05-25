#ifndef STRUKTURY_H

#define STRUKTURY_H

#include <stdbool.h>

typedef struct chunk {
	int c;
	bool active;
	bool checked;
}chunk;

typedef struct budget {
	int money;
	struct budget* next;
}budget;

#endif