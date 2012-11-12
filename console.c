/**
 * Console Bildschirm/Ausgang Behandlung: Quelle
 * @header: control.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#include "console.h"

/**
 * @function	clear_screen
 * Console Ausgang löschen
 */
void clear_screen()
{
	system("cls");
	set_color(BLACK, WHITE);
}

/**
 * @function	redraw_header
 * @param	points	Wieviel Punkte der Spieler hat
 *
 * Spiel "header" ausschreiben durch ASCII Buchstaben
 */
void redraw_header(int points)
{
	set_color(BLACK, YELLOW);

	printf("\n");
	printf(" ######  ###   ###  @8M: Die 8-Minuten Spiel\n");
	printf(" ##  ##  #### ####\n");
	printf(" ######  ## ### ##  @Version: 1.0\n");
	printf(" ##  ##  ##     ##  @Build date: 2012\n");
	printf(" ######  ##     ##\n\n");
	
	printf(" # Punkte: %6d\n\n", points);

	set_color(BLACK, WHITE);
}

/**
 * @function	set_color
 * @param	background	Die Konstante oder int der Farbe des Hintergrundes
 * @param	foreground	Die Konstante oder int der Farbe des Vorgrundes
 *
 * Modifiziert die Ausgangsfarbe
 */
void set_color(const int background, const int foreground)
{    
    int color = foreground+(background * 16);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, color);
}

/**
 * @function	set_size_and_position (und set_size als "Alias")
 * @param	width	Neue Breite (in Spalten) des Consoles
 * @param	height	Neue Höche (in Zeilen) des Consoles
 * @param	x	Wo die Console gelegt werden soll (X Koordinate in pixel)
 * @param	y	Wo die Console gelegt werden soll (Y Koordinate in pixel)
 *
 * Legt das Programm in (x,y) mit der Dimension (width,height)
 */
void set_size_and_position(const int width, const int height, const int x, const int y)
{
	HWND hWnd = GetConsoleWindow();
	COORD size;
	char s[13];

	if(width>MAX_COLS || height>MAX_ROWS)
		return;

	sprintf(s, "mode %d,%d", width, height);
	system(s);

	MoveWindow(hWnd, x, y, width*CHAR_WIDTH, height*CHAR_HEIGHT, 1);

	size.X = width-5;
	size.Y = height-5;
	
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);
}
void set_size(const int width, const int height)
{
	set_size_and_position(width, height, 25, 25);
}

/**
 * @function	go_to
 * @param	x	Legt den Cursor in der x-ten "Spalte"
 * @param	Y	Legt den Cursor in der y-ten "Zeile"
 *
 * Bewegt den Blinker in (x,y)
 */
void go_to(const int x, const int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;

    position.X = x;
    position.Y = y;

    SetConsoleCursorPosition(hConsole, position);
}

/**
 * @function	read_key
 * @result	int
 *
 * Liest eine Taste ein und wenn es ein Funktiontaste ist dann gebt zurück die virtuelle KEYCODE Konstante (wenn es existiert, sonst KEY_NULL),
 * sonst die ASCII Code 
 */
int read_key()
{
	int ch=getch();

	// Die gedrückte Taste ist ein ASCII Charakter, Return oder Funktionstaste (0 oder 224)
	switch(ch)
	{
		default:
			return tolower(ch);
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