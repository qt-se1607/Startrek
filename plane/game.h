#ifndef GAME_H
#define GAME_H

#include "plane_bullet.h"

bool al_start_game(allegro n);
bool al_join_game(allegro n);
bool al_end_game(allegro n);
void pause_game(allegro n);
void al_draw_display(allegro n);
bool judge_in(ALLEGRO_EVENT ev, int x1, int y1, int x2, int y2);
#endif // GAME_H
