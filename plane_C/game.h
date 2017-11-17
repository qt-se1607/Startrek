#ifndef GAME_H
#define GAME_H

#include "plane_bullet.h"

bool al_start_game(allegro );//开始游戏
bool al_join_game(allegro ,int );//进行游戏
bool al_end_game(allegro );//结束游戏
void al_pause(allegro ,plane ,plane ,buff );//暂停
void al_draw_pauseboard(allegro );//绘制暂停界面
bool judge_in(ALLEGRO_EVENT ,int ,int ,int ,int );//判断鼠标是否在bitmap内
void al_archive(plane ,plane ,buff );//存档至load
void al_draw_life(allegro , Plane );//绘制飞机相关属性及分数

#endif // GAME_H
