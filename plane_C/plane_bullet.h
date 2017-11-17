#ifndef PLANE_BULLET_H
#define PLANE_BULLET_H

#include "init.h"

//读档
void Init_Plane(plane ,int );//初始化己方飞机
bool Draw_plane_bullet(allegro ,int );//游戏
void Init_enemyplane(plane *,int );//初始化敌方飞机
void Init_Bullet(bullet *,int );//初始化子弹
void Init_buff(buff *, int );//初始化buff

void boom(allegro , plane , plane *, buff *);//判断爆炸及无效节点
int Rand(int ,int );//产生随机数
float Distance(float ,float ,float ,float );//计算(x1,y1),(x2,y2)距离
void al_draw_pic(ALLEGRO_BITMAP *,float ,float );//绘制位图
void al_move(ALLEGRO_EVENT ,plane , int *);//飞机移动
void al_draw_protect(plane );//绘制buff效果
void al_draw_list();//修改排行榜
void al_join_bullet(bullet *, Plane );//添加子弹
void al_join_plane(plane  *, Plane );//添加飞机
void al_join_buff(buff *);//添加buff

#endif // PLANE_BULLET_H
