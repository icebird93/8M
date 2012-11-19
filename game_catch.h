// Spiel Charakter Einstellungen
#define MARK_BORDER '#'
#define MARK_PLAYER 06
#define MARK_OPPONENT 036

void play_catch(int N, int *points);
void move_player(int *x, int *y, const int move_x, const int move_y);
void move_opponent(int *x, int *y, const int move_x, const int move_y);