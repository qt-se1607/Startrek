#ifndef VARIATE_H
#define VARIATE_H

#include <stdio.h>
#include "color.h"
#include <math.h>
#include <pthread.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define background red_indian
#define MAXSIZE 32

typedef struct MY_ALLEGRO{
    ALLEGRO_DISPLAY_MODE display_date;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_FONT *font1;
    ALLEGRO_FONT *font2;
    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_SAMPLE *bg;
    ALLEGRO_SAMPLE *shoot;
    ALLEGRO_SAMPLE *effect;
    ALLEGRO_SAMPLE *biu;
}allegro;

typedef struct MY_BULLET{//子弹
    float x1;//自身坐标
    float y1;
    float x2;//目的坐标
    float y2;
    ALLEGRO_BITMAP *img;
    float speed;
    int attack;
    int form;
    bool live;
    struct MY_BULLET *next;
}Bullet,*bullet;

typedef struct MY_PLANE{//飞机
    ALLEGRO_BITMAP *img;
    float x1;//自身坐标
    float y1;
    float x2;//目的坐标
    float y2;
    float speed;
    int level;
    int blood;
    int form;
    int size;
    int kind;//类型
    bullet bull;
    bool live;
    struct MY_PLANE *next;
}Plane,*plane;

typedef struct MY_BUFF{//buff
    ALLEGRO_BITMAP *img;
    float x1;//自身坐标
    float y1;
    float x2;//目的坐标
    float y2;
    float speed;
    bool live;
    int size;
    int form;
    int level;//类型
    struct MY_BUFF *next;
}Buff,*buff;

extern int score;//分数
extern int word_size;//字体大小
extern const float FPS;//帧数
extern int screen_width;//屏幕宽度
extern int screen_height;//屏幕高度
extern int score_width;//记分板宽度
extern int score_height;//记分板高度
extern int game_width;//游戏屏幕宽度
extern int game_height;//游戏屏幕高度
extern int img_x;//实际屏幕大小
extern int img_y;

extern bool key_up;
extern bool key_down;
extern bool key_left;
extern bool key_right;

extern bool screenflag;//全屏标志
extern float volume_num;//音量

extern int file_num;//读档文件流
extern char num[MAXSIZE];
extern bool again;//继续
extern bool save;//存档
extern bool set_back;//退出

extern plane p;//全局指针
extern bullet q;
extern buff r;

extern int effect_protection;//保护罩
extern int effect_craze;//狂热
extern int effect_speed;//加速

extern int plane_space;//飞机发射子弹间隔
extern int enemy_space;//敌机出现间隔
extern int bullet_space;//敌机发射子弹间隔
extern int buff_space;//buff出现间隔

extern int enemy_rate;//添加敌机计时
extern int bullet_rate;//添加敌方子弹计时
extern int plane_rate;//添加己方子弹计时
extern int buff_rate;//添加buff计时

extern int gate;//关卡

#endif // VARIATE_H
