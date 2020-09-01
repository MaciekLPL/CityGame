/*! \file
	\brief Plik zawiera deklaracje funkcji*/
#ifndef FUNKCJE_H

#define FUNKCJE_H

#include <stdbool.h>
#include "struktury.h"

/*! \fn void ShowConsoleCursor(int showFlag)
	\brief Funkcja ustawiaj�ca widoczno�� kursora.
	\param showFlag Parametr widoczno�ci kursora
	\return Funkcja nic nie zwraca. */
void ShowConsoleCursor(int showFlag);

/*! \fn void gotoxy(int x, int y)
	\brief Funkcja zmieniaj�ca pozycj� kursora na zadan�.
	\param x Wsp�rz�dna X
	\param y Wsp�rz�dna Y
	\return Funkcja nic nie zwraca. */
void gotoxy(int x, int y);

/*! \fn chunk** createBoard(int rows, int cols)
	\brief Funkcja alokuj�ca i zeruj�ca dwuwymiarow� tablic� do reprezentacji planszy gry.
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\return Pusta plansza */
chunk** createBoard(int rows, int cols);

/*! \fn void printBorders(int rows, int cols)
	\brief Funkcja rysuj�ca granice miasta.
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\return Funkcja nic nie zwraca. */
void printBorders(int rows, int cols);

/*! \fn void printHelp(int cols)
	\brief Funkcja wypisuj�ca instrukcj�/pomoc dla gracza.
	\param cols Liczba kolumn planszy
	\return Funkcja nic nie zwraca. */
void printHelp(int cols);

/*! \fn void arrowsHandling(int* x, int* y, int c, int maxx, int maxy, int minx, int miny)
	\brief Funkcja obs�uguj�ca sterowanie pozycj� kursora za pomoc� strza�ek.
	\param x Wsp�rz�dna X kursora
	\param y Wsp�rz�dna Y kursora
	\param c Naci�ni�ty klawisz
	\param maxx Maksymalna warto�� wsp�rz�dnej X
	\param maxy Maksymalna warto�� wsp�rz�dnej Y
	\param minx Minimalna warto�� wsp�rz�dnej X
	\param miny Minimalna warto�� wsp�rz�dnej Y
	\return Funkcja nic nie zwraca. */
void arrowsHandling(int* x, int* y, int c, int maxx, int maxy, int minx, int miny);

/*! \fn bool isValid(int x, int y, int rows, int cols)
	\brief Funkcja sprawdzaj�ca, czy wsp�rz�dne nie wychodz� poza tablic�.
	\param x Wsp�rz�dna X
	\param y Wsp�rz�dna Y
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\return True - wsp�rz�dne s� prawid�owe; False - wsp�rz�dne s� nieprawid�owe */
bool isValid(int x, int y, int rows, int cols);

/*! \fn int drawRoad(chunk** board, int i, int j, int rows, int cols)
	\brief Funkcja dobieraj�ca odpowiedni kod ASCII dla pola z drog� (wyszukuj�ce po��czenia drogi)
	\param board Plansza
	\param i Wsp�rz�dna Y na planszy
	\param j Wsp�rz�dna X na planszy
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\return Liczba reprezentuj�ca kod ASCII rozpatrywanego pola */
int drawRoad(chunk** board, int i, int j, int rows, int cols);

/*! \fn bool checkNeighbours(chunk** board, int character, int r, int c, int rows, int cols)
	\brief Funkcja sprawdzaj�ca s�siednie pola strefy, aby ustali� wsp�czynnik atrakcyjno�ci.
	\param board Plansza
	\param character Znak reprezentuj�cy dane pole
	\param r Wsp�rz�dna Y na planszy
	\param c Wsp�rz�dna X na planszy
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\return Funkcja nic nie zwraca. */
bool checkNeighbours(chunk** board, int character, int r, int c, int rows, int cols);

/*! \fn void checkAttractiveness(chunk** board, int rows, int cols)
	\brief Funkcja wywo�uj�ca sprawdzanie atrakcyjno�ci oraz aktualizacj� populacji na danym polu.
	\param board Plansza
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\return Funkcja nic nie zwraca. */
void checkAttractiveness(chunk** board, int rows, int cols);

/*! \fn double getTime(LARGE_INTEGER t1, int time)
	\brief Funkcja obliczaj�ca ca�kowity czas gry.
	\param t1 Czas rozpocz�cia obecnej sesji gry
	\param time Czas gry z poprzednich sesji
	\return Ca�kowity czas gry */
double getTime(LARGE_INTEGER t1, int time);

/*! \fn int countPopulation(chunk** board, int rows, int cols)
	\brief Funkcja obliczaj�ca populacj� miasta.
	\param board Plansza
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\return Ca�kowita populacja miasta */
int countPopulation(chunk** board, int rows, int cols);

/*! \fn void printMenu(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money, int population, int time)
	\brief Funkcja wypisuj�ca dolne menu pod plansz�.
	\param board Plansza
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\param t1 Czas rozpocz�cia obecnej sesji gry
	\param money Ilo�� posiadanych pieni�dzy
	\param population Populacja miasta
	\param time Czas gry z poprzednich sesji
	\return Funkcja nic nie zwraca. */
void printMenu(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money, int population, int time);

/*! \fn void renderBoard(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money)
	\brief Funkcja renderuj�ca plansz�.
	\param board Plansza
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\param t1 Czas rozpocz�cia obecnej sesji gry
	\param money Ilo�� posiadanych pieni�dzy
	\return Funkcja nic nie zwraca. */
void renderBoard(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money);

/*! \fn void newWallet(int diff, budget** wallet)
	\brief Funkcja aktualicuj�ca bud�et zadan� warto�ci�.
	\param diff Warto�� kt�r� nale�y doda�/odj�� w bud�ecie
	\param wallet Lista jednokierunkowa z bud�etem
	\return Funkcja nic nie zwraca. */
void newWallet(int diff, budget** wallet);

/*! \fn void buildRoad(chunk** board, int x, int y, budget** wallet)
	\brief Funkcja buduj�ca drog� na zadanym polu.
	\param board Plansza
	\param x Wsp�rz�dna X
	\param y Wsp�rz�dna Y
	\param wallet Lista jednokierunkowa z bud�etem
	\return Funkcja nic nie zwraca. */
void buildRoad(chunk** board, int x, int y, budget** wallet);

/*! \fn void setZone(chunk** board, int x, int y, int c, budget** wallet)
	\brief Funkcja ustawiaj�ca zadan� stref� na polu gry.
	\param board Plansza
	\param x Wsp�rz�dna X
	\param y Wsp�rz�dna Y
	\param c Zadana strefa lub jej brak
	\param wallet Lista jednokierunkowa z bud�etem
	\return Funkcja nic nie zwraca. */
void setZone(chunk** board, int x, int y, int c, budget** wallet);

/*! \fn void calcTaxes(int population, budget** wallet)
	\brief Funkcja kalkuluj�ca pobrane podatki.
	\param population Populacja miasta
	\param wallet Lista jednokierunkowa z bud�etem
	\return Funkcja nic nie zwraca. */
void calcTaxes(int population, budget** wallet);

/*! \fn void roadCosts(chunk** board, int rows, int cols, budget** wallet)
	\brief Funkcja kalkuluj�ca koszty utrzymania dr�g.
	\param board Plansza
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\param wallet Lista jednokierunkowa z bud�etem
	\return Funkcja nic nie zwraca. */
void roadCosts(chunk** board, int rows, int cols, budget** wallet);

/*! \fn int printStartingMenu();
	\brief Funkcja wy�wietlaj�ca menu g��wne.
	\return Wybrana przez u�ytkownika opcja */
int printStartingMenu();

/*! \fn chunk** newGame(int* rows, int* cols, budget** wallet)
	\brief Funkcja tworz�ca now� gr�.
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\param wallet Lista jednokierunkowa z bud�etem
	\return Zaalokowan� i wyzerowan� plansz� */
chunk** newGame(int* rows, int* cols, budget** wallet);

/*! \fn void saveBudget(FILE** file, budget* wallet)
	\brief Funkcja zapisuj�ca list� jednokierunkow� z bud�etem do pliku.
	\param file Plik
	\param wallet Lista jednokierunkowa z bud�etem
	\return Funkcja nic nie zwraca. */
void saveBudget(FILE** file, budget* wallet);

/*! \fn void getSaveName(char* saveName)
	\brief Funkcja pobieraj�ca od u�ytkownika nazw� pliku zapisu.
	\param saveName Pusty string
	\return Funkcja nic nie zwraca. */
void getSaveName(char* saveName);

/*! \fn void saveGame(chunk** board, int* rows, int* cols, budget* wallet, int* timeToSave)
	\brief Funkcja zapisuj�ca stan gry do pliku.
	\param board Plansza
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\param wallet Lista jednokierunkowa z bud�etem
	\param timeToSave Dotychczasowy czas gry do zapisania.
	\return Funkcja nic nie zwraca. */
void saveGame(chunk** board, int* rows, int* cols, budget* wallet, int* timeToSave);

/*! \fn bool validateFile(FILE** file)
	\brief Funkcja waliduj�ca czy plik jest prawid�owy i czy zosta� prawid�owo otwarty.
	\param file Plik
	\return True - je�eli plik zosta� otwarty i posiada string kontrolny; False - w przeciwnym wypadku */
bool validateFile(FILE** file);

/*! \fn chunk** loadGame(int* rows, int* cols, budget** wallet, int* time)
	\brief Funkcja wczytuj�ca stan gry z pliku.
	\param rows Liczba rz�d�w planszy
	\param cols Liczba kolumn planszy
	\param wallet Lista jednokierunkowa z bud�etem
	\param time Odczytany czas gry z innych sesji
	\return Wczytana plansza */
chunk** loadGame(int* rows, int* cols, budget** wallet, int* time);

/*! \fn int exitGame()
	\brief Funkcja wy�wietlaj�ca menu wyj�cia z gry.
	\return Warto�� liczbowa reprezentuj�ca wyb�r u�ytkownika */
int exitGame();

/*! \fn void freeBoard(chunk** board, int rows)
	\brief Funkcja zwalniaj�ca plansz� z pami�ci
	\param board Plansza
	\param rows Liczba rz�d�w planszy
	\return Funkcja nic nie zwraca. */
void freeBoard(chunk** board, int rows);

/*! \fn void freeBudget(budget* wallet)
	\brief Funkcja zwalniaj�ca list� jednokierunkow� z pami�ci
	\param wallet Lista jednokierunkowa z bud�etem
	\return Funkcja nic nie zwraca. */
void freeBudget(budget* wallet);


/*! \fn void bankrupt(chunk** board, int rows, budget* wallet);
	\brief Funkcja obs�uguj�ca bankructwo miasta
	\param board Plansza
	\param rows Liczba rz�d�w planszy
	\param wallet Lista jednokierunkowa z bud�etem
	\return Funkcja nic nie zwraca. */
void bankrupt(chunk** board, int rows, budget* wallet);

#endif

