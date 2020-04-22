#include <stdio.h>
#include <conio.h>
#include <windows.h>


#define Width 20
#define Height 10

//tutaj mozna poczytac troche o buforach (ja tego nie czytalem i nie wymagam zeby Pan to tak robi³)
//https://docs.microsoft.com/en-us/windows/console/console-screen-buffers


void ShowConsoleCursor(int showFlag)
{
	CONSOLE_CURSOR_INFO cursorInfo;	
	cursorInfo.bVisible = showFlag; 
	cursorInfo.dwSize = 100;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}




void SimplePrintScreen(char screen[Height][Width])
{
	gotoxy(0, 0);
	
	for (int i = 0; i < Height; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			putc(screen[i][j], stdout);
			//Sleep(10); //moze Pan sobie tez to odkomentowac zeby zobaczyc jak sie te znaki pojawiaja
		}
		putc('\n', stdout);
	}
}


int main()
{
	ShowConsoleCursor(1);

	
	char values[Height][Width];

	for (int i = 0; i < Height; ++i)
		for (int j = 0; j < Width; ++j)
			values[i][j] = 'a' + (i * Height + j) % 26;
	int x = 0, y = 0;

	while(1)
	{
		SimplePrintScreen(values);

		gotoxy(x, y);

		//int ax = _kbhit(); // ta funkcja sie moze gdzies tez Panu przydac
		int c = _getch();
		
		//TUTAJ brakuje spradzenia czy nie wyjdziemy za ekran
		if (c == 0xE0) //arrow
		{
			c = _getch();
			switch (c)
			{
			case 0x4B:
				--x;
				break;
			case 0x4D:
				++x;
				break;
			case 0x48:
				--y;
				break;
			case 0x50:
				++y;
				break;
			default:
				break;
			}
		}
		else
			values[y][x] = c;
		

		

		
	}
	//gotoxy(10, 10);
}
