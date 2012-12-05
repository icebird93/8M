/**
 * console.h
 * @source	control.c
 *
 * Console Bildschirm/Ausgang Behandlung
*/

#ifndef CONSOLE_H
#define CONSOLE_H

#include <conio.h>

/**
 * Maximale Dimension des Consoles
 */
#define MAX_COLS 240
#define MAX_ROWS 120
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 12

#define DEBUG_MODE 0

/**
 * Voreingestellte Console Breite und Höhe
 */
#define DEFAULT_HEIGHT 60
#define DEFAULT_WIDTH 120

/**
 * Cursor Position Fix
 */
#define CURSOR_POS_FIX 6

/**
 * Sammlung der Farben durch Konstanten
 * für set_color
 */
enum COLORS
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

/**
 * Sammlung der eigenen Funktiontasten durch Konstanten
 */
enum KEYCODES
{
	KEY_NULL = -1,
	KEY_UNKNOWN = -2,
	KEY_RETURN = -3,
	KEY_ESC = -4,
	KEY_SPACE = -5,
	KEY_LEFT = -10,
	KEY_RIGHT = -11,
	KEY_UP = -12,
	KEY_DOWN = -13
};

/**
 * Meine Funktionen für Behandlung des STDOUT
 * (Beschreibungen in .c File bei der Funktionen)
 */
void clear_screen();
void redraw_header(int points);
void init(int points);
void set_color(const int background, const int foreground);
void set_size_and_position(const int width, const int height, const int x, const int y);
void set_size(const int width, const int height);
void set_position(const int x, const int y);
int get_width();
int get_height();
void go_to(const int x, const int y);
int read_key();

#endif