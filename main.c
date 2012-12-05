#include <stdlib.h>
#include <stdio.h>

#include "console.h"
#include "control.h"
#include "game_launcher.h"

// Programm Eintritt
int main(int argc, char *argv[])
{
	int selected, points=0, width, height;

	// Größe einstellen
	switch(argc)
	{
		default:
			width=DEFAULT_WIDTH;
			height=DEFAULT_HEIGHT;
			break;
		case 2:
			width=height=atoi(argv[1]);
			break;
		case 3:
			width=atoi(argv[1]);
			height=atoi(argv[2]);
			break;
	}

	// STDOUT aufstellen
	init_player();
	init(points, width, height);

	// Mainmenu zeigen und Spiel starten
	do
	{
		selected=menu();
		game_launch(&selected, &points);
	} while(selected!='q');

	return 0;
}