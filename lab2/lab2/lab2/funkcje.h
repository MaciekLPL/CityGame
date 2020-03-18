#ifndef FUNKCJE_H

#define FUNKCJE_H
#include "struktury.h"

int** create2Darray(int R, int C);

void displayArray(int** tab, int R, int C);

void deleteArray(int** tab, int R);

int* createArray();

unsigned int hash(int element, unsigned int rozmiarTablicy);

void tablicaMieszajacaWstawianie(listElement** tab, int N, int liczba);

void dodajDoListy(listElement** pHead, int liczba);

void wypiszElementy(listElement** tab, int N);

void wypiszListe(listElement* pHead);

void usunElementy(listElement** tab, int N);

void usunListe(listElement* pHead);

#endif
