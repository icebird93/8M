#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#include "console.h"

void clear_screen()
{
	system("cls");
	set_color(BLACK, WHITE);
}

void redraw_header(int points)
{
	set_color(BLACK, YELLOW);

	printf("\n");
	printf(" ######  ###   ###  @8M: Die 8-Minuten Spiel\n");
	printf(" ##  ##  #### ####\n");
	printf(" ######  ## ### ##  @Version: 1.0\n");
	printf(" ##  ##  ##     ##  @Build date: 2012\n");
	printf(" ######  ##     ##\n\n");
	
	printf(" # Punkte: %5d\n\n", points);

	set_color(BLACK, WHITE);
}

void set_color(const int background, const int foreground)
{    
    int color = foreground+(background * 16);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, color);
}

void set_size(const int width, const int height)
{
	HWND hWnd = GetConsoleWindow();
	COORD size;
	char s[13];

	if(width>MAX_COLS || height>MAX_ROWS)
		return;

	sprintf(s, "mode %d,%d", width, height);
	printf("%s", s);
	system(s);

	MoveWindow(hWnd, 10, 10, width*CHAR_WIDTH, height*CHAR_HEIGHT, 1);

	size.X = width-5;
	size.Y = height-5;
	
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);
}

void go_to(const int x, const int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;

    position.X = x;
    position.Y = y;

    SetConsoleCursorPosition(hConsole, position);
}

/**
 * read_key
 * @Return: char
 * @Params: keine
 *
 * Liest eine Taste ein und wenn es ein Funktiontaste ist dann gebt zur�ck die virtuelle KEYCODE Konstante (wenn es existiert, sonst KEY_NULL), sonst die ASCII Code 
 */
int read_key()
{
	int ch=getch();

	// Die gedr�ckte Taste ist ein ASCII Charakter, Return oder Funktionstaste (0 oder 224)
	switch(ch)
	{
		default:
			return ch;
		case 13:
			return KEY_RETURN;
		case 27:
			return KEY_ESC;
		case 0:
		case 224:
			break;
	}

	// Mit einem Trick machen wir Virtual Keycodes definiert in console.h
	ch=getch();
	switch(ch)
	{
		case 75:
			return KEY_LEFT;
		case 77:
			return KEY_RIGHT;
		case 72:
			return KEY_UP;
		case 80:
			return KEY_DOWN;
	}

	return KEY_NULL;
}