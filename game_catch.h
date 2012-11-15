// Spiel Charakter Einstellungen
#define MARK_BORDER '#'
#define MARK_PLAYER 06
#define MARK_OPPONENT 036

// Anzahl der "Gegner"
#define N 50

void play_catch(int *points);
void move_player(int *x, int *y, const int move_x, const int move_y);
void move_opponent(int *x, int *y, const int move_x, const int move_y);