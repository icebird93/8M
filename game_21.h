#ifndef GAME_21_H
#define GAME_21_H

// Schwierigkeit: nur Werte zwischen 1-5
#define DIFFICULTY 5

// Kartenfarben
#define HEART 03
#define DIAMOND 04
#define CLUB 05
#define SPADE 06

// Funktionen
void play_21(int N, int *points);
void play_21_multi(int N_MULTI);

#endif