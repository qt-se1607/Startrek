#ifndef BEGAN_H
#define BEGAN_H

#include"variate.h"

extern bool key_enter;
extern bool key_up;
extern bool key_down;
extern bool key_left;
extern bool key_right;
extern bool event_timer;
extern bool start;
extern bool load;
extern bool list;
extern bool setting;
extern bool quit;
extern bool screenflag;//全屏标志
extern bool musicflag;//音乐标志
extern bool screen;
extern bool resolution;
extern bool music;
extern bool volume;
extern bool save;
extern bool set_back;
extern bool recover;
extern float volume_num;
extern bool archive_1;
extern bool archive_2;
extern bool archive_3;
extern bool archive_4;
extern bool archive_5;
extern bool archive_6;
extern bool load_back;
extern int list_num;
extern char num[MAXSIZE];
extern int number;

void al_start(allegro n);//进入plane
void al_draw_startboard(allegro n, int x, int y);//绘制开始界面
void al_load(allegro n, bool score);//存档
void al_draw_loadboard(allegro n, int x, int y);//绘制存档界面
void al_list(allegro n);//排行榜
void al_draw_listboard(allegro n, int x, int y);//绘制排行榜界面
void al_setting(allegro n);//设置
void al_draw_settingboard(allegro n, int x, int y);//绘制设置界面
void al_execl(int fp);
int al_wait();//等待plane返回
bool al_loadgame(int git, allegro n);//读当进入游戏
void al_draw_wait(allegro n, bool T, int form);//切换效果
void al_archive(int git);//修改存档load为archive_*
void al_turn(float x1,float y1,float x2,float y2,ALLEGRO_COLOR color);//绘画三角

#endif // BEGAN_H
