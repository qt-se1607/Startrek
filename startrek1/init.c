#include "init.h"

const int FPS = 120;
int word_size =72;//文字大小
int screen_width=0;//屏幕宽度
int screen_height=0;//屏幕高度
int score_width=0;//记分板宽度
int score_height=0;//记分板高度
int game_width=0;//游戏屏幕宽度
int game_height=0;//游戏屏幕高度
int img_x=0;
int img_y=0;

void Init_Allegro()
{
    if(!al_init()){
       fprintf(stderr, "failed to initialize allegro!\n");
       exit(1);
    }
    if(!al_install_mouse()){
        printf("failed to initialize the mouse\n");
        exit(1);
    }

    if(!al_install_keyboard()){
        printf("failed to initialize the keyboard\n");
        exit(1);
    }
    if(!al_init_font_addon()){
        printf("failed to initialize the font_addon\n");
        exit(1);
    }
    if(!al_init_ttf_addon()){
        printf("failed to initialize the ttf_addon\n");
        exit(1);
    }
    if(!al_init_image_addon()){
        fprintf(stderr,"Failed to initialize al_init_image_addon!");
        exit(1);
    }
}

void Destroy_Allegro(allegro *n)
{
    al_destroy_timer(n->timer);
    al_destroy_display(n->display);
    al_destroy_event_queue(n->event_queue);
    al_destroy_font(n->font1);
    al_destroy_font(n->font2);
    al_destroy_bitmap(n->bitmap);
}

void Init_Queue(allegro *n)
{
    al_register_event_source(n->event_queue,al_get_display_event_source(n->display));
    al_register_event_source(n->event_queue,al_get_timer_event_source(n->timer));
    al_register_event_source(n->event_queue,al_get_mouse_event_source());
    al_register_event_source(n->event_queue,al_get_keyboard_event_source());
}

void Init_Display(allegro *n)
{
    al_get_display_mode(0,&(n->display_date));
    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    n->display=al_create_display(n->display_date.width,n->display_date.height);


    if(!n->display){
        fprintf(stderr, "failed to create display!\n");
        exit(1);
    }
    n->event_queue=al_create_event_queue();
    if(!n->event_queue){
        fprintf(stderr, "failed to create event_queue!\n");
        exit(1);
    }
    n->timer=al_create_timer(1.0/FPS);
    if(!n->timer){
        fprintf(stderr, "failed to create timer!\n");
        exit(1);
    }
    n->bitmap=al_load_bitmap("../startrek1/img1.jpg");
    if(!n->bitmap){
        fprintf(stderr, "failed to create bitmap!\n");
        exit(1);
    }
    n->font1=al_load_ttf_font("../startrek1/a.ttf",word_size,128);
    if(!n->font1){
        fprintf(stderr, "failed to create font1!\n");
        exit(1);
    }
    n->font2=al_load_ttf_font("../startrek1/a.ttf",4*word_size,128);
    if(!n->font2){
        fprintf(stderr, "failed to create font2!\n");
        exit(1);
    }
    screen_width = n->display_date.width;
    screen_height = n->display_date.height;
    game_width = screen_width;
    game_height = screen_height;
    score_width = 0.2*screen_width;
    score_height = screen_height;
    img_x = 0.5*screen_width;
    img_y = 0.5*screen_height;
    al_draw_bitmap(n->bitmap,0,0,0);
}
