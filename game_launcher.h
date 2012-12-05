#ifndef GAME_LAUNCHER_H
#define GAME_LAUNCHER_H

/* Spiel Handlung */
void game_launch(int *selected, int *points);
void game_prepare1(char *rulefile);
void game_prepare2();
void game_finish(int points);

#endif