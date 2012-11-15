#include <stdlib.h>
#include <stdio.h>

#include "console.h"
#include "control.h"

#include "game_21.h"
#include "game_catch.h"
#include "game_guess.h"

// Globale Variabel
int points=0;

// Deklaration
void game_prepare1(char *rulefile);
void game_prepare2();
void game_finish();

// Programm Eintritt
int main(int argc, char *argv[])
{
	int selected, ch, n;

	// STDOUT aufstellen
	printf("Laden...\n");
	system("chcp 850");
	set_size(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	clear_screen();
	redraw_header(points);

	// Mainmenu zeigen
	do
	{
		selected=menu();

		switch(selected)
		{
			// Noch nicht definiert
			default:
				printf("\n # Dieses Funktion ist nicht erreichbar!\n");
				break;

			// 1,2: 21
			case 1:
			case 2:
				game_prepare1("rules/21.txt");

				// Spiel Einstellungen
				if(selected==1)
					printf("\n # Wieviel Bots [1-5]: ");
				else
					printf("\n # Wieviel Spieler [1-3]: ");
				scanf("%d", &n);

				game_prepare2();

				// Spiel starten
				if(selected==1)
					play_21(n, &points);
				else
					play_21_multi(n);

				game_finish();
				break;

			// 3: Catch Me
			case 3:
				game_prepare1("rules/catch.txt");
				game_prepare2();
				play_catch(&points);
				game_finish();
				break;

			// 4: Guess
			case 4:
				game_prepare1("rules/guess.txt");
				game_prepare2();
				play_guess(&points);
				game_finish();
				break;

			// Q: Beenden mit Bestätigung (durch j/return/esc/space Taste)
			case KEY_ESC:
				selected='q';
			case 'q':
				printf("\n # Sind Sie sicher ([j]/n): ");
				ch=read_key();
				if(ch!='j' && ch!=KEY_RETURN && ch!=KEY_ESC && ch!=KEY_SPACE)
				{
					selected=0;
					printf("\n");
				}
				break;
		}

	} while(selected!='q');

	return 0;
}

// Auschreibt die Regel
void game_prepare1(char *rulefile)
{
	printf("\n ");
	set_color(RED, YELLOW);
	printf("# Die Regel:\n\n");
	set_color(BLACK, WHITE);
	read_text_file(rulefile);
}

// Wartet auf den Start, dann löscht das Ausgang
void game_prepare2()
{
	set_color(BLACK, GREY);
	printf("\n # Pressen Sie eine Taste um das Spiel zu beginnen: ");
	read_key();
	clear_screen();
}

// Spiel beenden
void game_finish()
{
	redraw_header(points);
}