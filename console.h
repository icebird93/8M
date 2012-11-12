/**
 * Console Bildschirm/Ausgang Behandlung
 * @source: control.c
*/

/**
 * Maximale Dimension des Consoles
 */
#define MAX_COLS 240
#define MAX_ROWS 120
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 12

/**
 * Voreingestellte Console Breite und Höhe
 */
#define DEFAULT_HEIGHT 60
#define DEFAULT_WIDTH 120

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
void redraw_header(int points);
void set_color(const int background, const int foreground);
void set_size(const int width, const int height);
void set_size_and_position(const int width, const int height, const int x, const int y);
void go_to(const int x, const int y);
int read_key();