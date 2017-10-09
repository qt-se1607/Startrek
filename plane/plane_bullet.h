#ifndef PLANE_BULLET_H
#define PLANE_BULLET_H

#include "init.h"

void Init_Plane(plane *n);
bool Draw_plane_bullet(allegro *m);
void Init_enemyplane(plane n[MAXSIZE]);
void Init_Bullet(bullet n[]);
void boom(plane *n,plane *m);
int Rand(int low,int high);
int Distance(int x1,int y1,int x2,int y2);
void al_draw_pic(ALLEGRO_BITMAP *n,int x,int y);

#endif // PLANE_BULLET_H