/*! \file
	\brief Plik zawiera deklaracje funkcji*/
#ifndef FUNKCJE_H

#define FUNKCJE_H

#include <stdbool.h>
#include "struktury.h"

/*! \fn void ShowConsoleCursor(int showFlag)
	\brief Funkcja ustawiaj¹ca widocznoœæ kursora.
	\param showFlag Parametr widocznoœci kursora
	\return Funkcja nic nie zwraca. */
void ShowConsoleCursor(int showFlag);

/*! \fn void gotoxy(int x, int y)
	\brief Funkcja zmieniaj¹ca pozycjê kursora na zadan¹.
	\param x Wspó³rzêdna X
	\param y Wspó³rzêdna Y
	\return Funkcja nic nie zwraca. */
void gotoxy(int x, int y);

/*! \fn chunk** createBoard(int rows, int cols)
	\brief Funkcja alokuj¹ca i zeruj¹ca dwuwymiarow¹ tablicê do reprezentacji planszy gry.
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\return Pusta plansza */
chunk** createBoard(int rows, int cols);

/*! \fn void printBorders(int rows, int cols)
	\brief Funkcja rysuj¹ca granice miasta.
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\return Funkcja nic nie zwraca. */
void printBorders(int rows, int cols);

/*! \fn void printHelp(int cols)
	\brief Funkcja wypisuj¹ca instrukcjê/pomoc dla gracza.
	\param cols Liczba kolumn planszy
	\return Funkcja nic nie zwraca. */
void printHelp(int cols);

/*! \fn void arrowsHandling(int* x, int* y, int c, int maxx, int maxy, int minx, int miny)
	\brief Funkcja obs³uguj¹ca sterowanie pozycj¹ kursora za pomoc¹ strza³ek.
	\param x Wspó³rzêdna X kursora
	\param y Wspó³rzêdna Y kursora
	\param c Naciœniêty klawisz
	\param maxx Maksymalna wartoœæ wspó³rzêdnej X
	\param maxy Maksymalna wartoœæ wspó³rzêdnej Y
	\param minx Minimalna wartoœæ wspó³rzêdnej X
	\param miny Minimalna wartoœæ wspó³rzêdnej Y
	\return Funkcja nic nie zwraca. */
void arrowsHandling(int* x, int* y, int c, int maxx, int maxy, int minx, int miny);

/*! \fn bool isValid(int x, int y, int rows, int cols)
	\brief Funkcja sprawdzaj¹ca, czy wspó³rzêdne nie wychodz¹ poza tablicê.
	\param x Wspó³rzêdna X
	\param y Wspó³rzêdna Y
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\return True - wspó³rzêdne s¹ prawid³owe; False - wspó³rzêdne s¹ nieprawid³owe */
bool isValid(int x, int y, int rows, int cols);

/*! \fn int drawRoad(chunk** board, int i, int j, int rows, int cols)
	\brief Funkcja dobieraj¹ca odpowiedni kod ASCII dla pola z drog¹ (wyszukuj¹ce po³¹czenia drogi)
	\param board Plansza
	\param i Wspó³rzêdna Y na planszy
	\param j Wspó³rzêdna X na planszy
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\return Liczba reprezentuj¹ca kod ASCII rozpatrywanego pola */
int drawRoad(chunk** board, int i, int j, int rows, int cols);

/*! \fn bool checkNeighbours(chunk** board, int character, int r, int c, int rows, int cols)
	\brief Funkcja sprawdzaj¹ca s¹siednie pola strefy, aby ustaliæ wspó³czynnik atrakcyjnoœci.
	\param board Plansza
	\param character Znak reprezentuj¹cy dane pole
	\param r Wspó³rzêdna Y na planszy
	\param c Wspó³rzêdna X na planszy
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\return Funkcja nic nie zwraca. */
bool checkNeighbours(chunk** board, int character, int r, int c, int rows, int cols);

/*! \fn void checkAttractiveness(chunk** board, int rows, int cols)
	\brief Funkcja wywo³uj¹ca sprawdzanie atrakcyjnoœci oraz aktualizacjê populacji na danym polu.
	\param board Plansza
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\return Funkcja nic nie zwraca. */
void checkAttractiveness(chunk** board, int rows, int cols);

/*! \fn double getTime(LARGE_INTEGER t1, int time)
	\brief Funkcja obliczaj¹ca ca³kowity czas gry.
	\param t1 Czas rozpoczêcia obecnej sesji gry
	\param time Czas gry z poprzednich sesji
	\return Ca³kowity czas gry */
double getTime(LARGE_INTEGER t1, int time);

/*! \fn int countPopulation(chunk** board, int rows, int cols)
	\brief Funkcja obliczaj¹ca populacjê miasta.
	\param board Plansza
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\return Ca³kowita populacja miasta */
int countPopulation(chunk** board, int rows, int cols);

/*! \fn void printMenu(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money, int population, int time)
	\brief Funkcja wypisuj¹ca dolne menu pod plansz¹.
	\param board Plansza
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\param t1 Czas rozpoczêcia obecnej sesji gry
	\param money Iloœæ posiadanych pieniêdzy
	\param population Populacja miasta
	\param time Czas gry z poprzednich sesji
	\return Funkcja nic nie zwraca. */
void printMenu(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money, int population, int time);

/*! \fn void renderBoard(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money)
	\brief Funkcja renderuj¹ca planszê.
	\param board Plansza
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\param t1 Czas rozpoczêcia obecnej sesji gry
	\param money Iloœæ posiadanych pieniêdzy
	\return Funkcja nic nie zwraca. */
void renderBoard(chunk** board, int rows, int cols, LARGE_INTEGER t1, int money);

/*! \fn void newWallet(int diff, budget** wallet)
	\brief Funkcja aktualicuj¹ca bud¿et zadan¹ wartoœci¹.
	\param diff Wartoœæ któr¹ nale¿y dodaæ/odj¹æ w bud¿ecie
	\param wallet Lista jednokierunkowa z bud¿etem
	\return Funkcja nic nie zwraca. */
void newWallet(int diff, budget** wallet);

/*! \fn void buildRoad(chunk** board, int x, int y, budget** wallet)
	\brief Funkcja buduj¹ca drogê na zadanym polu.
	\param board Plansza
	\param x Wspó³rzêdna X
	\param y Wspó³rzêdna Y
	\param wallet Lista jednokierunkowa z bud¿etem
	\return Funkcja nic nie zwraca. */
void buildRoad(chunk** board, int x, int y, budget** wallet);

/*! \fn void setZone(chunk** board, int x, int y, int c, budget** wallet)
	\brief Funkcja ustawiaj¹ca zadan¹ strefê na polu gry.
	\param board Plansza
	\param x Wspó³rzêdna X
	\param y Wspó³rzêdna Y
	\param c Zadana strefa lub jej brak
	\param wallet Lista jednokierunkowa z bud¿etem
	\return Funkcja nic nie zwraca. */
void setZone(chunk** board, int x, int y, int c, budget** wallet);

/*! \fn void calcTaxes(int population, budget** wallet)
	\brief Funkcja kalkuluj¹ca pobrane podatki.
	\param population Populacja miasta
	\param wallet Lista jednokierunkowa z bud¿etem
	\return Funkcja nic nie zwraca. */
void calcTaxes(int population, budget** wallet);

/*! \fn void roadCosts(chunk** board, int rows, int cols, budget** wallet)
	\brief Funkcja kalkuluj¹ca koszty utrzymania dróg.
	\param board Plansza
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\param wallet Lista jednokierunkowa z bud¿etem
	\return Funkcja nic nie zwraca. */
void roadCosts(chunk** board, int rows, int cols, budget** wallet);

/*! \fn int printStartingMenu();
	\brief Funkcja wyœwietlaj¹ca menu g³ówne.
	\return Wybrana przez u¿ytkownika opcja */
int printStartingMenu();

/*! \fn chunk** newGame(int* rows, int* cols, budget** wallet)
	\brief Funkcja tworz¹ca now¹ grê.
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\param wallet Lista jednokierunkowa z bud¿etem
	\return Zaalokowan¹ i wyzerowan¹ planszê */
chunk** newGame(int* rows, int* cols, budget** wallet);

/*! \fn void saveBudget(FILE** file, budget* wallet)
	\brief Funkcja zapisuj¹ca listê jednokierunkow¹ z bud¿etem do pliku.
	\param file Plik
	\param wallet Lista jednokierunkowa z bud¿etem
	\return Funkcja nic nie zwraca. */
void saveBudget(FILE** file, budget* wallet);

/*! \fn void getSaveName(char* saveName)
	\brief Funkcja pobieraj¹ca od u¿ytkownika nazwê pliku zapisu.
	\param saveName Pusty string
	\return Funkcja nic nie zwraca. */
void getSaveName(char* saveName);

/*! \fn void saveGame(chunk** board, int* rows, int* cols, budget* wallet, int* timeToSave)
	\brief Funkcja zapisuj¹ca stan gry do pliku.
	\param board Plansza
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\param wallet Lista jednokierunkowa z bud¿etem
	\param timeToSave Dotychczasowy czas gry do zapisania.
	\return Funkcja nic nie zwraca. */
void saveGame(chunk** board, int* rows, int* cols, budget* wallet, int* timeToSave);

/*! \fn bool validateFile(FILE** file)
	\brief Funkcja waliduj¹ca czy plik jest prawid³owy i czy zosta³ prawid³owo otwarty.
	\param file Plik
	\return True - je¿eli plik zosta³ otwarty i posiada string kontrolny; False - w przeciwnym wypadku */
bool validateFile(FILE** file);

/*! \fn chunk** loadGame(int* rows, int* cols, budget** wallet, int* time)
	\brief Funkcja wczytuj¹ca stan gry z pliku.
	\param rows Liczba rzêdów planszy
	\param cols Liczba kolumn planszy
	\param wallet Lista jednokierunkowa z bud¿etem
	\param time Odczytany czas gry z innych sesji
	\return Wczytana plansza */
chunk** loadGame(int* rows, int* cols, budget** wallet, int* time);

/*! \fn int exitGame()
	\brief Funkcja wyœwietlaj¹ca menu wyjœcia z gry.
	\return Wartoœæ liczbowa reprezentuj¹ca wybór u¿ytkownika */
int exitGame();

/*! \fn void freeBoard(chunk** board, int rows)
	\brief Funkcja zwalniaj¹ca planszê z pamiêci
	\param board Plansza
	\param rows Liczba rzêdów planszy
	\return Funkcja nic nie zwraca. */
void freeBoard(chunk** board, int rows);

/*! \fn void freeBudget(budget* wallet)
	\brief Funkcja zwalniaj¹ca listê jednokierunkow¹ z pamiêci
	\param wallet Lista jednokierunkowa z bud¿etem
	\return Funkcja nic nie zwraca. */
void freeBudget(budget* wallet);


/*! \fn void bankrupt(chunk** board, int rows, budget* wallet);
	\brief Funkcja obs³uguj¹ca bankructwo miasta
	\param board Plansza
	\param rows Liczba rzêdów planszy
	\param wallet Lista jednokierunkowa z bud¿etem
	\return Funkcja nic nie zwraca. */
void bankrupt(chunk** board, int rows, budget* wallet);

#endif

