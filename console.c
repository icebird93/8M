/**
 * console.c
 * @header	control.h
 *
 * Console Bildschirm/Ausgang Behandlung: Quelle
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#include "console.h"

// Breite und H�che speichern
int console_width=0, console_height=0;

/**
 * @function	clear_screen
 * Console Ausgang l�schen
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
	printf(" ######  ###   ###  @8M: Das 8-Minuten Spiel\n");
	printf(" ##  ##  #### ####\n");
	printf(" ######  ## ### ##  @Version: 1.1\n");
	printf(" ##  ##  ##     ##  @Build date: 2012\n");
	printf(" ######  ##     ##\n\n");
	
	printf(" # Punkte: %7d\n\n", points);

	set_color(BLACK, WHITE);
}

/**
 * @function	init
 * @param	points	Wieviel Punkte der Spieler hat
 *
 * Initializiert das Console
 */
void init(int points, int width, int height)
{
	printf("Laden...\n");
	system("chcp 850");
	set_size(width, height);
	clear_screen();
	redraw_header(points);
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
 * @function	set_size_and_position (und set_size, set_position als "Alias")
 * @param	width	Neue Breite (in Spalten) des Consoles
 * @param	height	Neue H�che (in Zeilen) des Consoles
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

	if(width>MAX_COLS || width<50 || height>MAX_ROWS || height<20)
		return;

	console_width=width-CURSOR_POS_FIX;
	console_height=height-CURSOR_POS_FIX;

	sprintf(s, "mode %d,%d", width, height);
	system(s);

	MoveWindow(hWnd, x, y, width*CHAR_WIDTH, height*CHAR_HEIGHT, 1);

	size.X = width-CURSOR_POS_FIX+1;
	size.Y = height-CURSOR_POS_FIX+1;
	
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);
}
void set_size(const int width, const int height)
{
	set_size_and_position(width, height, 25, 25);
}
void set_position(const int x, const int y)
{
	set_size_and_position(console_width, console_height, x, y);
}

/**
 * @function	get_width, get_height
 * @result	int
 *
 * Gibt zur�ck die aktuelle Breite und H�che
 */
int get_width()
{
	return console_width;
}
int get_height()
{
	return console_height;
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
 * Liest eine Taste ein und wenn es ein Funktiontaste ist dann gebt zur�ck die virtuelle KEYCODE Konstante (wenn es existiert, sonst KEY_NULL),
 * sonst die ASCII Code 
 */
int read_key()
{
	int ch=getch();

	// Die gedr�ckte Taste ist ein ASCII Charakter, Return oder Funktionstaste (0 oder 224)
	switch(ch)
	{
		default:
			return tolower(ch);
		case 13:
			return KEY_RETURN;
		case 27:
			return KEY_ESC;
		case 32:
			return KEY_SPACE;
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
		default:
			if(DEBUG_MODE)
				printf("[F: %d]", ch);
			return KEY_UNKNOWN;
	}

	return KEY_NULL;
}