#ifndef GAME_H
#define GAME_H

#include "plane_bullet.h"

bool al_start_game(allegro );
bool al_join_game(allegro ,int );
bool al_end_game(allegro );
void al_pause(allegro ,plane ,plane ,buff );
void al_draw_pauseboard(allegro );
bool judge_in(ALLEGRO_EVENT ,int ,int ,int ,int );
void al_archive(plane ,plane ,buff );
void al_draw_life(Plane );

#endif // GAME_H
