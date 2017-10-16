#ifndef GAME_H
#define GAME_H

#include "plane_bullet.h"

bool al_start_game(allegro n);
bool al_join_game(allegro n, int file_num);
bool al_end_game(allegro n);
void al_pause(allegro n,plane my,plane enemy[MAXSIZE]);
void al_draw_pauseboard(allegro n);
bool judge_in(ALLEGRO_EVENT ev, int x1, int y1, int x2, int y2);
void al_archive(plane n,plane m[MAXSIZE]);
#endif // GAME_H
