/*! \file
	\brief Plik zawiera definicje struktur*/
#ifndef STRUKTURY_H

#define STRUKTURY_H

#include <stdbool.h>

/*! \struct chunk
	\brief Struktura reprezentuj¹ca pojedyncze pole na planszy*/
typedef struct chunk {
	int c; /*!< Reprezentacja pola przez kod ascii */
	int population; /*!< Populacja pola*/
	int attractiveness; /*!< Wspó³czynnik atrakcyjnoœci pola*/

}chunk;

/*! \struct budget
	\brief Element listy jednokierunkowej reprezentuj¹cej bud¿et */
typedef struct budget {
	int money; /*!< Iloœæ pieniêdzy w bud¿ecie */
	struct budget* next; /*!< WskaŸnik do nastêpnego elementu. */
}budget;

#endif