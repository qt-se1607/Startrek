#ifndef VARIATE_H
#define VARIATE_H

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
    ALLEGRO_BITMAP *bitmap1;//主背景
    ALLEGRO_BITMAP *bitmap2;//load
    ALLEGRO_BITMAP *bitmap3;//list
    ALLEGRO_BITMAP *bitmap4;//setting
    ALLEGRO_SAMPLE *sample1;//触碰音效
    ALLEGRO_SAMPLE *sample2;//背景音乐
}allegro;

typedef struct MY_CIRCLE{
    float x;//初始位置
    float y;
    ALLEGRO_COLOR color;//颜色
    int size;//大小
    struct MY_CIRCLE *next;//下一个指针
}Circle,*circle;//圆圈特效

extern circle click;

#include"color.h"

#endif // VARIATE_H
