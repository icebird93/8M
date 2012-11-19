#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "console.h"
#include "game_catch.h"
#include "highscore.h"

// Eine Struktur damit der Koordinaten der Gegner gespeichert werden
struct COORDINATES
{
	int x, y;
};

// Spiel Eintritt
void play_catch(int N, int *points)
{
	int i, x=0, y=0, new_x, new_y, key, caught=0, steps=0, points_new=0, pressed;
	struct COORDINATES *opp;

	if(N<0 || N>2000)
		N=100;

	set_color(BLACK, GREY);
	// Oben und unten
	for(i=1; i<get_width(); i++)
	{
		go_to(i, 0);
		printf("%c", MARK_BORDER);
		go_to(i, get_height());
		printf("%c", MARK_BORDER);
	}
	// Links und rechts
	for(i=1; i<get_height(); i++)
	{
		go_to(0, i);
		printf("%c", MARK_BORDER);
		go_to(get_width(), i);
		printf("%c", MARK_BORDER);
	}

	// Spieler Startposition
	move_player(&x, &y, get_width()/2, get_height()/2);

	// Gegner Startpositionen
	srand(time(0));
	opp=(struct COORDINATES*)calloc(N, sizeof(struct COORDINATES));
	set_color(BLACK, WHITE);
	for(i=0; i<N; i++)
	{
		do{
			new_x=2+(rand()%(get_width()-2));
			new_y=2+(rand()%(get_height()-2));
		} while(sqrt(pow(new_x-x, 2)+pow(new_y-y, 2))<10);
		move_opponent(&opp[i].x, &opp[i].y, new_x, new_y);
	}
	go_to(0, 0);

	// Spiel Schleife
	do
	{
		steps++;
		points_new+=log(steps)/log(2)*steps;
		key=read_key();
		switch(key)
		{
			case KEY_UP:
				move_player(&x, &y, 0, -1);
				break;
			case KEY_DOWN:
				move_player(&x, &y, 0, 1);
				break;
			case KEY_LEFT:
				move_player(&x, &y, -1, 0);
				break;
			case KEY_RIGHT:
				move_player(&x, &y, 1, 0);
				break;
			case KEY_ESC:
				caught=1;
				break;
		}

		if(!caught)
		{
			for(i=0; i<N; i++)
			{
				if(opp[i].x==x)
				{
					// Kollision und Bewegung
					if(fabs(opp[i].y-y)<=1)
						caught=1;
					move_opponent(&opp[i].x, &opp[i].y, 0, (opp[i].y>y)?-1:1);
				}
				else if(opp[i].y==y)
				{
					// Kollision und Bewegung
					if(fabs(opp[i].x-x)<=1)
						caught=1;
					move_opponent(&opp[i].x, &opp[i].y, (opp[i].x>x)?-1:1, 0);
				}
				else
				{
					// Bewegung
					if(rand()%2==0)
						move_opponent(&opp[i].x, &opp[i].y, 0, (opp[i].y>y)?-1:1);
					else
						move_opponent(&opp[i].x, &opp[i].y, (opp[i].x>x)?-1:1, 0);
					// Kollision
					if(opp[i].x==x && opp[i].y==y)
					{
						caught=1;
						break;
					}
				}
			}
		}

		go_to(0, 0);
	} while(!caught && key!=KEY_ESC);

	// Game Over
	set_color(YELLOW, RED);
	x=(get_width()-14)/2;
	y=(get_height()-5)/2;
	go_to(x, y);
	for(i=0; i<14; i++)
	{
		go_to(x+i, y);
		printf("#");
		go_to(x+i, y+4);
		printf("#");
	}
	for(i=0; i<5; i++)
	{
		go_to(x, y+i);
		printf("#");
		go_to(x+13, y+i);
		printf("#");
	}
	set_color(BLACK, RED);
	go_to(x+2, y+2);
	printf("GAME OVER!");
	go_to(0, 0);
	*points+=points_new;

	read_key();
	clear_screen();

	set_color(BLACK, RED);
	printf("\n # GAME OVER!\n");
	set_color(BLACK, WHITE);
	printf("\n # Sie haben sich %d-mal bewegt", steps);
	printf("\n # Punkten: %d\n", points_new);

	highscore(HS_CATCH, steps, N);
}

// Bewegt Spieler in die gegebene Position (wenn es richtig ist)
void move_player(int *x, int *y, const int move_x, const int move_y)
{
	int new_x=*x+move_x, new_y=*y+move_y;
	if(new_x==*x && new_y==*y)
		return;
	go_to(*x, *y);
	printf(" ");
	if(new_x>0 && new_x<get_width())
		*x+=move_x;
	if(new_y>0 && new_y<get_height())
		*y+=move_y;
	go_to(*x, *y);
	set_color(BLACK, GREEN);
	printf("%c", MARK_PLAYER);
}

// Bewegt Gegner in die gegebene Position (wenn es richtig ist)
void move_opponent(int *x, int *y, const int move_x, const int move_y)
{
	int new_x=*x+move_x, new_y=*y+move_y;
	if(new_x==*x && new_y==*y)
		return;
	go_to(*x, *y);
	printf(" ");
	if(new_x>0 && new_x<get_width())
		*x+=move_x;
	if(new_y>0 && new_y<get_height())
		*y+=move_y;
	go_to(*x, *y);
	set_color(BLACK, RED);
	printf("%c", MARK_OPPONENT);
}