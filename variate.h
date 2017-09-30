#include<stdio.h>
#include"color.h"
#include<math.h>
#include<pthread.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro5.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_color.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
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
    bool tip;
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
    bullet m[MAXSIZE];
    bool tip;
}plane;
ALLEGRO_TRANSFORM transform;
int word_size=72;//文字大小
float FPS=120;//帧数
int plane_time=0;//飞机出现时间
int bullet_time=0;//子弹出现时间
int screen_width=0;//屏幕宽度
int screen_height=0;//屏幕高度
int score_width=0;//记分板宽度
int score_height=0;//记分板高度
int game_width=0;//游戏屏幕宽度
int game_height=0;//游戏屏幕高度
int img_x=0;
int img_y=0;
bool key_up=false;
bool key_down=false;
bool key_left=false;
bool key_right=false;
