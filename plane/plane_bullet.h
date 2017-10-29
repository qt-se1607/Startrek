#ifndef PLANE_BULLET_H
#define PLANE_BULLET_H

#include "init.h"

void Init_Plane(plane n, int file_num);
bool Draw_plane_bullet(allegro m, int file_num);
void Init_enemyplane(plane *n, int file_num);
void Init_Bullet(bullet *n, int file_num);
void Init_buff(Buff b);
void boom(plane n, plane *m, Buff *b);
int Rand(int low,int high);
int Distance(int x1,int y1,int x2,int y2);
void al_draw_pic(ALLEGRO_BITMAP *n, float x, float y);
void al_move(ALLEGRO_EVENT ev, plane my, int *plane_num);
void al_draw_protect(Plane n,bool effect);

#endif // PLANE_BULLET_H
