/**
 * control.h
 * @source	control.c
 *
 * Das Library dass für die Behandlung des Spiels sorgt. (Zum Beispiel Menus)
 */

/* Spieler Info */
char *player_name;

/* Funktionen */
int menu();
void init_player();
int read_text_file(char *filename);
char* get_cwd();