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
#define background red_indian
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
int word_size=0;//文字大小
float FPS=120;//帧数
int plane_time=0;//飞机出现时间
int bullet_time=0;//子弹出现时间
int screen_width=0;//屏幕宽度
int screen_height=0;//屏幕高度
int game_width=0;//游戏屏幕宽度
int game_height=0;//游戏屏幕高度
int img_x=0;
int img_y=0;
bool key_enter=false;
bool key_up=false;
bool key_down=false;
bool key_left=false;
bool key_right=false;
bool event_timer=false;
bool start=false;
bool load=false;
bool list=false;
bool setting=false;
bool quit=false;
bool screenflag=false;//全屏标志
bool musicflag=true;//音乐标志
bool screen=false;
bool resolution=false;
bool music=false;
bool volume=false;
bool save=false;
bool set_back=false;
bool recover=false;
float volume_num=100.0;
bool archive_1=false;
bool archive_2=false;
bool archive_3=false;
bool archive_4=false;
bool archive_5=false;
bool archive_6=false;
bool load_back=false;
int list_num=7;
char num[MAXSIZE];
int number=0;
