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
    ALLEGRO_TRANSFORM transform;
}allegro;

typedef struct MY_BULLET{//子弹
    float x1;
    float y1;
    float x2;
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
    float x1;
    float y1;
    float x2;
    float y2;
    float speed;
    int level;
    int blood;
    int form;
    int size;
    int kind;
    bullet bull;
    bool live;
    struct MY_PLANE *next;
}Plane,*plane;

typedef struct MY_BUFF{
    ALLEGRO_BITMAP *img;
    float x1;
    float y1;
    float x2;
    float y2;
    float speed;
    bool live;
    int size;
    int form;
    int level;
    struct MY_BUFF *next;
}Buff,*buff;

ALLEGRO_TRANSFORM transform;

extern int score;
extern int word_size;
extern const float FPS;//帧数
extern int plane_space;//飞机出现jian ge
extern int bullet_space;//子弹出现时间
extern int screen_width;//屏幕宽度
extern int screen_height;//屏幕高度
extern int score_width;//记分板宽度
extern int score_height;//记分板高度
extern int game_width;//游戏屏幕宽度
extern int game_height;//游戏屏幕高度
extern int img_x;
extern int img_y;
extern bool key_up;
extern bool key_down;
extern bool key_left;
extern bool key_right;
extern bool screenflag;//全屏标志
extern float volume_num;
extern int file_num;
extern char num[MAXSIZE];
extern bool again;
extern bool save;
extern bool set_back;
extern plane p;
extern bullet q;
extern buff r;
extern int effect_protection;
extern int effect_time;

#endif // VARIATE_H
