#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "console.h"
#include "game_21.h"

// Anzahl der Spieler
#define N 3
// Schwierigkeit: nur Werte zwischen 1-5
#define DIFFICULTY 5
// Kartenfarben
#define HEART 03
#define DIAMOND 04
#define CLUB 05
#define SPADE 06

// Spiel Eintritt
void play_21(int *points)
{
	int i, my=0, selected, player_max=0, player_max_i, points_new=0, current;
	int *player;

	// "Seed": random einstellen
	srand(time(0));

	player=(int*)malloc(N*sizeof(int));

	// Punkte der Gegner einstellen
	for(i=0; i<N; i++)
	{
		// Game Over losen
		if(floor(2*DIFFICULTY*rand()/(float)RAND_MAX)==0)
			player[i]=22+(int)floor(5*rand()/(float)RAND_MAX);
		else
			player[i]=DIFFICULTY*3+(int)floor((21-DIFFICULTY*3)*rand()/(float)RAND_MAX);
		if(player_max<player[i] && player[i]<=21)
		{
			player_max=player[i];
			player_max_i=i;
		}
	}

	do
	{
		current=get_card();
		if(current==11 && my>10)
			current=1;
		my+=current;

		printf(" # Aktuelle Summe: ");
		set_color(BLACK, YELLOW);
		printf("%2d", my);
		set_color(BLACK, WHITE);
		if(my<21)
		{
			printf("\n # Mehr? (<j>/n): ");		
			selected=read_key();
			printf("\n");
		}
	} while(selected!='n' && my<21);

	printf("\n\n # Sie: %d\n", my);
	if(my>21)
		printf(" # Game Over! Sie haben mehr als 21.\n");
	else if(my==21)
	{
		set_color(BLACK, YELLOW);
		printf(" # Black Jack!\n");
		set_color(BLACK, WHITE);
	}

	// Punkte der Gegner
	set_color(BLACK, PURPLE);
	for(i=0; i<N; i++)
		printf("\n # Spieler %d: %2d", i+1, player[i]);

	if(my>=player_max && my<=21)
	{
		points_new+=N*DIFFICULTY*100+(my-player_max)*300;
		if(my==21)
			points_new+=5000;
		set_color(BLACK, GREEN);
		printf("\n\n # Sie haben gewonnen! (%d Punkten)", points_new);
		*points+=points_new;
	}
	else
	{
		set_color(BLACK, RED);
		printf("\n\n # Spieler %d hat gewonnen!", player_max_i+1);
	}

	read_key();
	clear_screen();
}

/**
 * @function	get_card
 * @result	int
 *
 * Zufällig gibt zurück eine "Karte" (Wert) von 1-11
 */
int get_card()
{
	// "Karte"
	int card=1+(int)floor(13*rand()/(float)RAND_MAX);

	printf("\n # Karte: ");

	// Farbe
	set_color(BLACK, YELLOW);
	switch(1+(int)floor(4*rand()/(RAND_MAX-1.0)))
	{
		case 1:
			printf("%c", HEART);
			break;
		case 2:
			printf("%c", DIAMOND);
			break;
		case 3:
			printf("%c", CLUB);
			break;
		case 4:
			printf("%c", SPADE);
			break;
	}
	switch(card)
	{
		default:
			printf("%d\n", card);
			set_color(BLACK, WHITE);
			return card;
		// A
		case 1:
			printf("A\n");
			set_color(BLACK, WHITE);
			return 11;
		// J,Q,K
		case 11:
			printf("J\n");
			set_color(BLACK, WHITE);
			return 10;
		case 12:
			printf("Q\n");
			set_color(BLACK, WHITE);
			return 10;
		case 13:
			printf("K\n");
			set_color(BLACK, WHITE);
			return 10;
	}
}