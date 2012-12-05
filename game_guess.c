#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "console.h"
#include "game_guess.h"
#include "highscore.h"

// Spiel Eintritt
void play_guess(int difficulty, int *points)
{
	double secret, guess;
	int ch, i, steps=0, max=1000+(int)floor(pow(SECRET_BASE, difficulty));
	char s[16];

	/* Vorbereitungen */
	getchar();
	s[15]='\0';

	/* difficulty kontrollieren */
	if(difficulty<1 || difficulty>10)
		difficulty=5;

	/* Hinweis */
	set_color(BLACK, YELLOW);
	go_to(get_width()-53, 1);
	printf(" Schreiben Sie jederzeit Q um das Spiel zu beenden! #");
	go_to(0, 0);
	set_color(BLACK, WHITE);

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
				/* getchar is gebraucht wegen Input Buffer und der Ende */
				printf("\n # Nicht gueltig! Neuer Tipp: ");
			}
			fgets(s, 15, stdin);
			if(s[0]=='q' || s[0]=='Q')
				return;
			guess=(int)atoi(s);
		} while(guess<0);
		steps++;
		
		if(guess>secret)
		{
			printf("\n ");
			set_color(DARK_BLUE, WHITE);
			printf("# %.0lf ist ZU GROESS", guess);
			set_color(BLACK, WHITE);
			printf("\n");
		}
		else if(guess<secret)
		{
			printf("\n ");
			set_color(RED, WHITE);
			printf("# %.0lf ist ZU KLEIN", guess);
			set_color(BLACK, WHITE);
			printf("\n");
		}
	} while(guess!=secret);

	set_color(BLACK, GREEN);
	printf("\n # %.0lf ist die gedachte Zahl! Sie haben gewonnen in %d Schritten.\n", guess, steps);
	*points+=difficulty*1000;

	highscore(HS_GUESS, steps, difficulty);
}