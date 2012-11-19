#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "console.h"
#include "game_guess.h"

// Spiel Eintritt
void play_guess(int difficulty, int *points)
{
	double secret, guess;
	int ch, i, steps=0, max=1000+(int)floor(pow(SECRET_BASE, difficulty));

	/* difficulty kontrollieren */
	if(difficulty<1 || difficulty>10)
		difficulty=5;

	/* Rand einstellen */
	srand(time(0));
	rand();

	/* heimliche Zahl */
	secret=rand() % max;

	do{
		printf("\n # Ihr Tipp: ");
		i=0;
		do
		{
			i++;
			if(i>1)
			{
				/* getchar is gebraucht wegen Input Buffer */
				getchar();
				printf(" # Nicht gueltig! Neuer Tipp: ");
			}
			scanf("%lf", &guess);
		} while(guess<0);
		steps++;
		
		if(guess>secret)
		{
			set_color(BLACK, CYAN);
			printf("\n # %.0lf ist groesser als die gedachte Zahl\n", guess);
		}
		else if(guess<secret)
		{
			set_color(BLACK, RED);
			printf("\n # %.0lf ist kleiner als die gedachte Zahl\n", guess);
		}

		set_color(BLACK, WHITE);
	} while(guess!=secret);

	set_color(BLACK, GREEN);
	printf("\n # %.0lf ist die gedachte Zahl! Sie haben gewonnen in %d Schritte.\n", guess, steps);
	*points+=difficulty*1000;

	set_color(BLACK, GREY);
	printf("\n # Druecken Sie Esc um zurueck zum Menu zu springen...");

	do{
		ch=read_key();
	} while(ch!=KEY_ESC);

	clear_screen();
}