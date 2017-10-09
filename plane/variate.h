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
    int x1;
    int y1;
    int x2;
    int y2;
    ALLEGRO_BITMAP *img;
    int speed;
    int attack;
    int form;
    bool live;
}bullet;

typedef struct MY_PLANE{//飞机
    ALLEGRO_BITMAP *img;
    int x1;
    int y1;
    int x2;
    int y2;
    int level;
    int speed;
    int blood;
    int form;
    int size;
    int bullet_num;
    bullet bull[MAXSIZE];
    bool live;
}plane;

ALLEGRO_TRANSFORM transform;

extern int word_size;
//float FPS=120;//帧数
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


#endif // VARIATE_H