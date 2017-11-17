#include"variate.h"

int word_size=0;//文字大小
float FPS=120;//帧数
int game_width=0;//游戏屏幕宽度
int game_height=0;//游戏屏幕高度
int img_x=0;//屏幕大小
int img_y=0;

void Init_Allegro(allegro *n)
{
    srand((int)time(NULL));
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
    if(!al_install_audio()){
        fprintf(stderr,"Failed to initialize al_install_audio!");
        exit(1);
    }
    if(!al_init_acodec_addon()){
        fprintf(stderr,"Failed to initialize al_init_acodec_addon!");
        exit(1);
    }
    if(!al_reserve_samples(100)){
        fprintf(stderr,"Failed to initialize al_reserve_samples!");
        exit(1);
    }
    al_get_display_mode(0,&(n->display_date));
}

void Destroy_Allegro(allegro *n)
{
    al_destroy_timer(n->timer);
    al_destroy_display(n->display);
    al_destroy_event_queue(n->event_queue);
    al_destroy_font(n->font1);
    al_destroy_font(n->font2);
    al_destroy_bitmap(n->bitmap1);
    al_destroy_bitmap(n->bitmap2);
    al_destroy_bitmap(n->bitmap3);
    al_destroy_sample(n->sample1);
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
    n->bitmap1=NULL;
    n->bitmap2=NULL;
    n->bitmap3=NULL;
    n->display=NULL;
    n->event_queue=NULL;
    n->font1=NULL;
    n->font2=NULL;
    n->timer=NULL;
    word_size=0.05*game_height;
    /*
     * ALLEGRO_WINDOWED                     可窗口化
     * ALLEGRO_FULLSCREEN                   窗口内全屏
     * ALLEGRO_OPENGL                       图形处理
     * ALLEGRO_DIRECT3D_INTERNAL            内部3D构建
     * ALLEGRO_RESIZABLE                    可修改大小
     * ALLEGRO_FRAMELESS                    无边框
     * ALLEGRO_NOFRAME                      无边框
     * ALLEGRO_OPENGL_FORWARD_COMPATIBLE    兼容图形处理
     * ALLEGRO_FULLSCREEN_WINDOW            全屏窗口
     * ALLEGRO_MINIMIZED                    最小化
    */
    //al_set_new_display_flags(ALLEGRO_NOFRAME);
    n->display = al_create_display(game_width,game_height);
    if(!n->display){
        fprintf(stderr, "failed to create display!\n");
        Destroy_Allegro(n);
        exit(1);
    }
    n->event_queue = al_create_event_queue();
    if(!n->event_queue){
        fprintf(stderr, "failed to create event_queue!\n");
        Destroy_Allegro(n);
        exit(1);
    }
    n->timer=al_create_timer(1.0/FPS);
    if(!n->timer){
        fprintf(stderr, "failed to create timer!\n");
        Destroy_Allegro(n);
        exit(1);
    }
    n->font1=al_load_font("../UI/a.ttf",word_size,0);
    if(!n->font1){
        fprintf(stderr, "failed to create font1!\n");
        Destroy_Allegro(n);
        exit(1);
    }
    n->font2=al_load_font("../UI/a.ttf",2*word_size,0);
    if(!n->font2){
        fprintf(stderr, "failed to create font2!\n");
        Destroy_Allegro(n);
        exit(1);
    }
    Init_Queue(n);
}

/*bool judge_inside(ALLEGRO_EVENT ev,ALLEGRO_BITMAP *bitmap)
{
    int mouse_x = ev.mouse.x;
    int mouse_y = ev.mouse.y;
    int x = al_get_bitmap_x(bitmap);
    int y = al_get_bitmap_y(bitmap);
    int width = al_get_bitmap_width(bitmap);
    int height = al_get_bitmap_height(bitmap);
    if(mouse_x < x)return false;
    if(mouse_x > x + width)return false;
    if(mouse_y < y)return false;
    if(mouse_y > y + height)return false;
    return true;
}*/

int Rand(int low,int high)
{
    int i=rand();
    float m = i / ((float)RAND_MAX + 1);
    m=m * (high - low + 1) + low;
    return (int) m;
}

int Distance(int x1,int y1,int x2,int y2)
{
    return pow(pow(x1 - x2,2) + pow(y1 - y2,2),0.5);
}

bool judge_in(ALLEGRO_EVENT ev, int x1, int y1, int x2, int y2)
{
    int mouse_x = ev.mouse.x;
    int mouse_y = ev.mouse.y;
    if(mouse_x < x1)return false;
    if(mouse_x > x2)return false;
    if(mouse_y < y1)return false;
    if(mouse_y > y2)return false;
    return true;
}
