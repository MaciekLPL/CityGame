/*! \file
	\brief Plik zawiera definicje struktur*/
#ifndef STRUKTURY_H

#define STRUKTURY_H

#include <stdbool.h>

/*! \struct chunk
	\brief Struktura reprezentuj�ca pojedyncze pole na planszy*/
typedef struct chunk {
	int c; /*!< Reprezentacja pola przez kod ascii */
	int population; /*!< Populacja pola*/
	int attractiveness; /*!< Wsp�czynnik atrakcyjno�ci pola*/

}chunk;

/*! \struct budget
	\brief Element listy jednokierunkowej reprezentuj�cej bud�et */
typedef struct budget {
	int money; /*!< Ilo�� pieni�dzy w bud�ecie */
	struct budget* next; /*!< Wska�nik do nast�pnego elementu. */
}budget;

#endif