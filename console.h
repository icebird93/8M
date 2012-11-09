/**
 * Console Bildschirm Behandlung
 * @File: control.c
*/

/**
 * Sammlung der Farben durch Konstanten
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
 * Sammlung der Farben durch Konstanten
 */
enum KEYCODES
{
	KEY_NULL = -1,
	KEY_RETURN = -2,
	KEY_ESC = -3,
	KEY_LEFT = -4,
	KEY_RIGHT = -5,
	KEY_UP = -6,
	KEY_DOWN = -7
};

/**
 * Meine Funktionen für Behandlung des STDOUT
 */
void clear_screen();
void redraw_header();
void set_color(const int background, const int foreground);
void go_to(const int x, const int y);
int read_key();