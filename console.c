#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "console.h"

enum
{
    BLACK = 0,
    DARK_BLUE = 1,
    DARK_GREEN = 2,
    TEAL = 3,
    DARK_RED = 4,
    DARK_PURPLE = 5,
    GOLD = 6,
    GREY = 7,
    DARK_WHITE = 8,
    BLUE = 9,
    GREEN = 10,
    CYAN = 11,
    RED = 12,
    PURPLE = 13,
    YELLOW = 14,
    WHITE = 15
};

void clear_screen()
{
	system("cls");
	set_color(BLACK, WHITE);
}

void redraw_header()
{
	set_color(BLACK, YELLOW);

	printf("\n");
	printf(" ######  ###   ###  [8M: Die 8-Minuten Spiel]\n");
	printf(" ##  ##  #### ####\n");
	printf(" ######  ## ### ##  @Version: 1.0\n");
	printf(" ##  ##  ##     ##  @Build date: 2012\n");
	printf(" ######  ##     ##\n\n");

	set_color(BLACK, WHITE);
}

void set_color(const int background, const int foreground)
{    
    int color = foreground+(background * 16);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void go_to(const int x, const int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD position;
    position.X = x;
    position.Y = y;

    SetConsoleCursorPosition(hConsole, position);
}