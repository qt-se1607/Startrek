#ifndef ALLEGRO_H
#define ALLEGRO_H

#include"variate.h"

extern int word_size;//文字大小
extern float FPS;//帧数
extern int game_width;//游戏屏幕宽度
extern int game_height;//游戏屏幕高度
extern int img_x;//屏幕宽度
extern int img_y;//屏幕高度

void Init_Allegro(allegro *n);//初始化allegro
void Destroy_Allegro(allegro *n);//销毁
void Init_Queue(allegro *n);//添加事件
void Init_Display(allegro *n);//初始化屏幕
bool judge_in(ALLEGRO_EVENT ev, int x1, int y1, int x2, int y2);//判断鼠标是否在bitmap内
int Rand(int low,int high);//产生随机数
int Distance(int x1,int y1,int x2,int y2);//计算(x1,y1),(x2,y2)距离

#endif // ALLEGRO_H
