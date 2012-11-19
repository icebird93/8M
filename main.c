#include <stdlib.h>
#include <stdio.h>

#include "console.h"
#include "control.h"
#include "game_launcher.h"

// Programm Eintritt
int main(int argc, char *argv[])
{
	int selected, points=0;

	// STDOUT aufstellen
	init_player();
	init(points);

	// Mainmenu zeigen und Spiel starten
	do
	{
		selected=menu();
		game_launch(&selected, &points);
	} while(selected!='q');

	return 0;
}