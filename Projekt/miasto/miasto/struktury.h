#ifndef STRUKTURY_H

#define STRUKTURY_H

#include <stdbool.h>

typedef struct chunk {
	int ch;
	bool active;
	bool checked;
}chunk;

typedef struct budget {
	int money;
	struct budget* next;
}budget;

#endif