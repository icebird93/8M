#include <stdlib.h>
#include <stdio.h>

#include "console.h"
#include "control.h"

#include "game_21.h"

// Programm Eintritt
int main(int argc, char *argv[])
{
	int selected, ch, points=0, n;

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
				printf("\n ");
				set_color(RED, YELLOW);
				printf("# Die Regel:\n\n");
				set_color(BLACK, WHITE);
				read_text_file("rules/21.txt");

				if(selected==1)
					printf("\n # Wieviel Bots [1-5]: ");
				else
					printf("\n # Wieviel Spieler [1-3]: ");
				scanf("%d", &n);

				set_color(BLACK, GREY);
				printf("\n # Pressen Sie eine Taste um das Spiel zu beginnen: ");
				read_key();

				clear_screen();
				if(selected==1)
					play_21(n, &points);
				else
					play_21_multi(n);
				redraw_header(points);
				break;

			// Q: Beenden
			case KEY_ESC:
				selected='q';
			case 'q':
				printf("\n # Sind Sie sicher ([j]/n): ");
				ch=read_key();
				if(ch!='j' && ch!=KEY_RETURN && ch!=KEY_ESC)
				{
					selected=0;
					printf("\n");
				}
				break;
		}

	} while(selected!='q');

	return 0;
}