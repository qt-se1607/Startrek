#ifndef PLANE_BULLET_H
#define PLANE_BULLET_H

#include "init.h"

void Init_Plane(plane ,int );
bool Draw_plane_bullet(allegro ,int );
void Init_enemyplane(plane *,int );
void Init_Bullet(bullet *,int );
void Init_buff(buff *);
void boom(plane ,plane *,buff *);
int Rand(int ,int );
float Distance(float ,float ,float ,float );
void al_draw_pic(ALLEGRO_BITMAP *,float ,float );
void al_move(ALLEGRO_EVENT ,plane , int *);
void al_draw_protect(plane );
void al_draw_list();
void al_join_bullet(bullet *, Plane );
void al_join_plane(plane  *, Plane );
void al_join_buff(buff *);

#endif // PLANE_BULLET_H
