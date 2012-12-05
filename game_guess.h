#ifndef GAME_GUESS_H
#define GAME_GUESS_H

/* Geheimzahl wird durch Basis^Schwierigkeit hergestellt */
#define SECRET_BASE 2.8

void play_guess(int difficulty, int *points);

#endif