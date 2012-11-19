#include <stdio.h>

/* Spiel Bestenlisten */
#define HS_21 "highscore/21.dat"
#define HS_CATCH "highscore/catch.dat"
#define HS_GUESS "highscore/guess.dat"

/* Einstellungen */
#define MAX_HIGHSCORE_ITEM 10

/*
 * Verkettete Liste Handlung
 */
typedef struct struct_highscore_item
{
	char name[32];
	unsigned int points;
	int difficulty;
	struct struct_highscore_item *next;
} item;

/* Funktionen */
void highscore(char *filename, int score, int difficulty);
void display_highscore(char *filename, int difficulty);
int update_highscore(item *head, item *i);
item* read_highscore(char *filename);
void write_highscore(char *filename, item *head);
int clear_highscore(char *filename);

/* Verkettete Liste Handlung */
item* create_item();
void add_item(item **head, item *i);
item* update_item(item *i, char *name, unsigned int points, int difficulty);
void remove_item(item **head, item **i);
int count_items(item *head);