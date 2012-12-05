#include <stdio.h>

#include "game_launcher.h"
#include "console.h"
#include "control.h"
#include "highscore.h"

#include "game_21.h"
#include "game_catch.h"
#include "game_guess.h"

// Spiel starten
void game_launch(int *selected, int *points)
{
	int ch, n;
	item *p;

	switch(*selected)
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
			if(*selected==1)
				printf("\n # Wieviel Bots [1-5]: ");
			else
				printf("\n # Wieviel Spieler [1-4]: ");
			scanf("%d", &n);

			game_prepare2();

			// Spiel starten
			if(*selected==1)
				play_21(n, points);
			else
				play_21_multi(n);

			game_finish(*points);
			break;

		// 3: Catch Me
		case 3:
			game_prepare1("rules/catch.txt");

			printf("\n # Wieviel Bots [25-300]: ");
			scanf("%d", &n);

			game_prepare2();
			play_catch(n, points);
			game_finish(*points);
		break;

		// 4: Guess
		case 4:
			game_prepare1("rules/guess.txt");

			printf("\n # Schwierigkeitstufe [1-10]: ");
			scanf("%d", &n);

			game_prepare2();
			play_guess(n, points);
			game_finish(*points);
			break;

		// H: Hall of Fame
		case 'h':
			printf("\n\n # Spiele:\n");
			printf("\n [1] 21");
			printf("\n [2] Catch");
			printf("\n [3] Guess");
			printf("\n\n # Extras:\n");
			printf("\n [4] 21 loeschen");
			printf("\n [5] Catch loeschen");
			printf("\n [6] Guess loeschen");
			printf("\n\n # Funktion: ");

			do
			{
				n=read_key();
			} while(n<'1' || n>'6');
			
			switch(n)
			{
				case '1':
					display_highscore(HS_21, 0);
					break;
				case '2':
					display_highscore(HS_CATCH, 0);
					break;
				case '3':
					display_highscore(HS_GUESS, 0);
					break;
				case '4':
					clear_highscore(HS_21);
					break;
				case '5':
					clear_highscore(HS_CATCH);
					break;
				case '6':
					clear_highscore(HS_GUESS);
					break;
			}
			printf("\n\n");
			break;

		// Q: Beenden mit Bestätigung (durch j/return/esc/space Taste)
		case KEY_ESC:
			*selected='q';
		case 'q':
			printf("\n # Sind Sie sicher ([j]/n): ");
			ch=read_key();
			if(ch!='j' && ch!=KEY_RETURN && ch!=KEY_ESC && ch!=KEY_SPACE)
			{
				*selected=0;
				printf("\n");
			}
			break;
	}
}

// Auschreibt die Regel
void game_prepare1(char *rulefile)
{
	printf("\n ");
	set_color(RED, YELLOW);
	printf("# Die Regel:");
	set_color(BLACK, WHITE);
	printf("\n\n");
	read_text_file(rulefile);
}

// Wartet auf den Start, dann löscht das Ausgang
void game_prepare2()
{
	set_color(BLACK, GREY);
	printf("\n # Pressen Sie SPACE um das Spiel zu beginnen: ");
	do{ } while(read_key()!=KEY_SPACE);
	clear_screen();
}

// Spiel beenden
void game_finish(int points)
{
	int ch;

	set_color(BLACK, GREY);
	printf("\n\n # Druecken Sie ESC um zurueck zum Menu zu springen...");

	do{
		ch=read_key();
	} while(ch!=KEY_ESC);

	clear_screen();
	redraw_header(points);
}