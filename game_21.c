#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "console.h"
#include "game_21.h"
#include "highscore.h"

// Spiel Eintritt (1 Spieler, N Bots)
void play_21(int N, int *points)
{
	int i, my=0, selected, player_max=0, player_max_i, points_new=0, current;
	int *player;

	// N kontrollieren
	if(N<1 || N>5)
		N=3;

	// "Seed": random einstellen
	srand(time(0));
	rand();

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
		// Neue Karte
		printf("\n ");
		current=get_card();
		printf("\n");
		if(current==11 && my>10)
			current=1;
		my+=current;

		// Aktuelle Punkte ausschreiben
		printf(" # Aktuelle Summe: ");
		set_color(BLACK, YELLOW);
		printf("%2d", my);
		set_color(BLACK, WHITE);
		if(my<21)
		{
			printf("\n # Mehr? ([j]/n): ");		
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
	set_color(BLACK, CYAN);
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
	
		highscore(HS_21, points_new, N);
	}
	else
	{
		set_color(BLACK, RED);
		if(player_max==0)
			printf("\n\n # Huhh. Alle Spieler haben mehr als 21 Punkten...");
		else
			printf("\n\n # Spieler %d hat gewonnen!", player_max_i+1);
	}
}


// Spiel Eintritt (N_MULTI Spieler)
void play_21_multi(int N_MULTI)
{
	int i, *my, my_max=0, *my_stop, my_stopped=0, *my_max_i, my_max_count=0, selected, current, x, y, y_player, max_y=0;

	// N_MULTI kontrollieren
	if(N_MULTI<1 || N_MULTI>4)
		N_MULTI=2;

	// RAM allokieren mit 0
	my=(int*)calloc(N_MULTI, sizeof(int));
	my_max_i=(int*)calloc(N_MULTI, sizeof(int));
	my_stop=(int*)calloc(N_MULTI, sizeof(int));

	// "Seed": random einstellen
	srand(time(0));
	rand();

	// Spieler
	max_y=1;
	do
	{
		y_player=max_y;
		for(i=0; i<N_MULTI; i++)
		{
			if(my_stop[i])
				continue;

			x=i*get_width()/N_MULTI+1;
			y=y_player;
			switch(i)
			{
				case 0:
					set_color(DARK_GREEN, WHITE);
					break;
				case 1:
					set_color(DARK_BLUE, WHITE);
					break;
				case 2:
					set_color(DARK_PURPLE, WHITE);
					break;
				case 3:
					set_color(DARK_RED, WHITE);
					break;
				default:
					set_color(BLACK, WHITE);
					break;
			}
			go_to(x, y);
			printf("# Spieler %d:", i+1);
			y+=2;
			set_color(BLACK, WHITE);
	
			go_to(x, y);
			current=get_card();
			y++;
			if(current==11 && my[i]>10)
				current=1;
			my[i]+=current;

			go_to(x, y);
			printf("# Aktuelle Summe: ");
			set_color(BLACK, YELLOW);
			printf("%2d", my[i]);
			set_color(BLACK, WHITE);
			y++;
			if(my[i]<21)
			{
				go_to(x, y);
				printf("# Mehr? ([j]/n): ");
				y+=2;
				selected=read_key();
			}
			if(my[i]>=21 || selected=='n')
			{
				my_stop[i]=1;
				my_stopped++;
			}
	
			// Letze Zeile speichern
			if(y>max_y)
				max_y=y;
		}
	} while(my_stopped<N_MULTI);

	// Punkte der Spieler
	for(i=0; i<N_MULTI; i++)
	{
		x=i*get_width()/N_MULTI+1;
		y=max_y+3;

		// Spieler "Name" und seine Punkte
		go_to(x, y);
		switch(i)
		{
			case 0:
				set_color(DARK_GREEN, WHITE);
				break;
			case 1:
				set_color(DARK_BLUE, WHITE);
				break;
			case 2:
				set_color(DARK_PURPLE, WHITE);
				break;
			case 3:
				set_color(DARK_RED, WHITE);
				break;
			default:
				set_color(BLACK, WHITE);
				break;
		}
		printf("# Spieler %d: %d", i+1, my[i]);
		set_color(BLACK, WHITE);
		y++;

		if(my[i]>21)
		{
			go_to(x, y);
			printf("# Game Over! Mehr als 21.");
			y++;
		}
		else if(my[i]==21)
		{
			go_to(x, y);
			set_color(BLACK, YELLOW);
			printf("# Black Jack!");
			set_color(BLACK, WHITE);
			y++;
		}

		// Punkte vergleichen um das Maximum zu finden. Wenn es gleich ist, dann speichern wir den Spieler Index.
		if(my[i]>my_max && my[i]<=21)
		{
			my_max=my[i];
			my_max_i[0]=i;
			my_max_count=1;
		}
		else if(my[i]==my_max)
		{
			my_max_i[my_max_count]=i;
			my_max_count++;
		}
	}

	go_to(1, max_y+8);
	if(my_max_count>0)
	{
		set_color(BLACK, GREEN);
		printf("# Spieler %d", my_max_i[0]+1);
		for(i=1; i<my_max_count; i++)
			printf(", %d", my_max_i[i]+1);
		printf(" %s gewonnen!", (my_max_count>1)?"haben":"hat");
	}
	else
	{
		set_color(BLACK, RED);
		printf("# Huhh. Alle Spieler haben mehr als 21 Punkten...");
	}
}

/**
 * @function	get_card
 * @result	int
 *
 * Zufällig gibt zurück eine "Karte" (Wert) von 1-11
 */
int get_card()
{
	int card;
	unsigned long int time_current;
	static unsigned long int time_prev;

	// "Seed": random einst ellen
	time_current=time(0);
	while(time_prev && time_prev>=time_current)
		time_current+=10;
	srand(time_current);
	time_prev=time_current;

	// "Karte"
	rand();
	card=rand()%13+1;

	printf("# Karte: ");

	// Farbe
	set_color(BLACK, CYAN);
	switch(1+rand()%4)
	{
		case 1:
			printf("%c ", HEART);
			break;
		case 2:
			printf("%c ", DIAMOND);
			break;
		case 3:
			printf("%c ", CLUB);
			break;
		case 4:
			printf("%c ", SPADE);
			break;
	}
	set_color(BLACK, YELLOW);
	switch(card)
	{
		default:
			printf("%d", card);
			set_color(BLACK, WHITE);
			return card;
		// A
		case 1:
			printf("A");
			set_color(BLACK, WHITE);
			return 11;
		// J,Q,K
		case 11:
			printf("J");
			set_color(BLACK, WHITE);
			return 10;
		case 12:
			printf("Q");
			set_color(BLACK, WHITE);
			return 10;
		case 13:
			printf("K");
			set_color(BLACK, WHITE);
			return 10;
	}
}