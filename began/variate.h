#ifndef ALLEGRO_H
#define ALLEGRO_H
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<stdbool.h>
#include"color.h"
#include<math.h>
#include<pthread.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro5.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_color.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#define MAXSIZE 32
typedef struct MY_ALLEGRO{
    ALLEGRO_DISPLAY_MODE display_date;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_FONT *font1;
    ALLEGRO_FONT *font2;
    ALLEGRO_BITMAP *bitmap1;
    ALLEGRO_BITMAP *bitmap2;
    ALLEGRO_BITMAP *bitmap3;
    ALLEGRO_BITMAP *bitmap4;
    ALLEGRO_BITMAP *bitmap5;
    ALLEGRO_SAMPLE *sample1;
    ALLEGRO_SAMPLE *sample2;
    ALLEGRO_TRANSFORM transform;
}allegro;
extern int word_size;//文字大小
extern float FPS;//帧数
extern int screen_width;//屏幕宽度
extern int screen_height;//屏幕高度
extern int game_width;//游戏屏幕宽度
extern int game_height;//游戏屏幕高度
extern int img_x;
extern int img_y;
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
void Init_Allegro(allegro *n);
void Destroy_Allegro(allegro *n);
void Init_Queue(allegro *n);
void Init_Display(allegro *n);
bool judge_inside(ALLEGRO_EVENT ev,ALLEGRO_BITMAP *bitmap);
int Rand(int low,int high);
int Distance(int x1,int y1,int x2,int y2);
bool judge_in(ALLEGRO_EVENT ev, int x1, int y1, int x2, int y2);
void al_draw_startboard(allegro n);
void al_setting(allegro n);
void al_load(allegro n, bool score);
void al_draw_settingboard(allegro n);
void al_draw_loadboard(allegro n);
void al_list(allegro n);
void al_draw_listboard(allegro n);
void al_turn(float x1,float y1,float x2,float y2,ALLEGRO_COLOR color);
void al_execl(int fp);
int al_wait();
void al_start(allegro n);
bool al_loadgame(int git, allegro n);
void al_archive(int git);
#endif // ALLEGRO_H
