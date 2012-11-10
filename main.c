#include <stdlib.h>
#include <stdio.h>

#include "console.h"
#include "control.h"

#include "game_21.h"

int main(int argc, char *argv[])
{
	int selected, ch, points=0;

	// STDOUT aufstellen
	clear_screen();
	redraw_header();

	// Mainmenu zeigen
	do
	{
		selected=menu();

		switch(selected)
		{
			// Nocch nicht definiert
			default:
				printf("\n # Dieses Funktion ist nicht erreichbar!\n");
				break;

			// 1: 21
			case 1:
				printf("\n # Die Regel:\n");
				printf("\n # Sie spielt gegen einem Bot. \n");
				clear_screen();
				play_21(&points);
				redraw_header();
				break;

			// Q: Beenden
			case 'q':
				printf("\n # Sind Sie sicher ([j]/n): ");
				ch=read_key();
				if(ch!='j' && ch!=KEY_RETURN)
				{
					selected=0;
					printf("\n");
				}
				break;
		}

	} while(selected!='q');

	return 0;
}