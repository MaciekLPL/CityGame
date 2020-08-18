
#ifndef MEMORILO_H
#define MEMORILO_H

void * Malloc (long int size, const char* filename, int line);
void   Free (void * p, const char* filename, int line);

/////////////////////////


#define malloc(size)  Malloc (size, __FILE__, __LINE__)
#define free(p)       Free (p, __FILE__, __LINE__)

#endif
