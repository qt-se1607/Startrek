#include"variate.h"
void Init_Allegro(allegro n);
void Init_Display(allegro n);
void Destroy_Allegro(allegro n);
void Init_Queue(allegro n);
void Init_Display(allegro n);
bool al_start_game(allegro n);
bool al_join_game(allegro n);
void al_end_game(allegro n);
void Init_Bullet(bullet n[MAXSIZE]);
void Init_Plane(plane n);
void Draw_plane(plane n);
void Draw_Bullet(bullet n[MAXSIZE]);
void add_bullet(bullet n);
int Rand(int low,int high);
bool judge_inside(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *bitmap, int dx, int dy);
void Init_Allegro(allegro n)
{
    n.display=NULL;
    n.event_queue=NULL;
    n.timer=NULL;
    n.font1=NULL;
    n.font2=NULL;
    n.bitmap=NULL;
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
void Destroy_Allegro(allegro n)
{
    al_destroy_timer(n.timer);
    al_destroy_display(n.display);
    al_destroy_event_queue(n.event_queue);
    al_destroy_font(n.font1);
    al_destroy_font(n.font2);
    al_destroy_bitmap(n.bitmap);
}
void Init_Queue(allegro n)
{
    al_register_event_source(n.event_queue,al_get_display_event_source(n.display));
    al_register_event_source(n.event_queue,al_get_timer_event_source(n.timer));
    al_register_event_source(n.event_queue,al_get_mouse_event_source());
    al_register_event_source(n.event_queue,al_get_keyboard_event_source());
}
void Init_Display(allegro n)
{
    screen_width=n.display_date.width;
    screen_height=n.display_date.height;
    game_width=0.8*screen_width;
    game_height=screen_height;
    score_width=0.2*screen_width;
    score_height=screen_height;
    al_draw_bitmap(n.bitmap,0,0,0);
}
bool al_start_game(allegro n)
{
    ALLEGRO_BITMAP *bitmap=NULL;
    bitmap=al_create_bitmap(0.3*screen_width,0.2*screen_height);
    al_set_target_bitmap(bitmap);
    al_clear_to_color(green_yellow);
    al_set_target_bitmap(al_get_backbuffer(n.display));
    al_draw_bitmap(bitmap,0.5*(screen_width-al_get_bitmap_width(bitmap)),0.5*(screen_height-al_get_bitmap_height(bitmap)),0);
    al_draw_text(n.font1,white,0.5*screen_width,0.5*(screen_height-word_size),ALLEGRO_ALIGN_CENTER,"开 始 游 戏");
    al_flip_display();
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.mouse.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN&&judge_inside(ev,bitmap,0.5*(screen_width-al_get_bitmap_width(bitmap)),0.5*(screen_height-al_get_bitmap_height(bitmap)))){
            al_clear_to_color(black);
            al_draw_text(n.font2,white,0.5*screen_width,0.5*screen_height-2*word_size,ALLEGRO_ALIGN_CENTER,"3");
            al_flip_display();
            al_rest(1);
            al_clear_to_color(black);
            al_draw_text(n.font2,white,0.5*screen_width,0.5*screen_height-2*word_size,ALLEGRO_ALIGN_CENTER,"2");
            al_flip_display();
            al_rest(1);
            al_clear_to_color(black);
            al_draw_text(n.font2,white,0.5*screen_width,0.5*screen_height-2*word_size,ALLEGRO_ALIGN_CENTER,"1");
            al_flip_display();
            al_rest(1);
            break;
        }
        if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE||ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)return false;
        if(ev.type==ALLEGRO_EVENT_TIMER)al_flip_display();
    }
    return true;
}
bool al_join_game(allegro n)
{
    srand((int)time(NULL));
    int plane_num=0;
    bool time_t=false;
    plane my,m[MAXSIZE];
    //my_airplane
    Init_Plane(my);
    my.level=1;
    my.blood=10;
    Init_Bullet(my.m);
    my.tip=true;
    my.speed=5;
    my.img=al_load_bitmap("timg.png");
    my.size=al_get_bitmap_width(my.img);
    my.x1=0.5*game_width-my.size;
    my.y1=game_height-my.size;
    //my_airplane
    for(int i=0;i<MAXSIZE;i++)Init_Plane(m[i]);
    ALLEGRO_TIMER *bullet_timer=NULL,*plane_timer=NULL;
    bullet_timer=al_create_timer(bullet_time);
    plane_timer=al_create_timer(plane_time);
    al_start_timer(bullet_timer);
    al_start_timer(plane_timer);
    while(1){
        ALLEGRO_EVENT ev,ev_bullet,ev_plane;
        al_wait_for_event(n.event_queue,&ev);
        al_wait_for_event(n.event_queue,&ev_bullet);
        al_wait_for_event(n.event_queue,&ev_plane);
        //加入子弹
        if(ev_bullet.type==ALLEGRO_EVENT_TIMER){
            if(my.tip){
                int c=my.bullet_num;
                my.m[c].tip=true;
                my.m[c].speed=0;
                my.bullet_num++;
                if(my.bullet_num>=MAXSIZE)my.bullet_num=0;
            }
            for(int i=0;i<MAXSIZE;i++)
                if(m[i].tip&&m[i].blood!=0){
                    int a=m[i].bullet_num;
                    m[i].m[a].attack=m[i].level;
                    m[i].bullet_num++;
                    if(m[i].bullet_num>=MAXSIZE)m[i].bullet_num=0;
                }
        }
        //加入飞机
        if(ev_plane.type==ALLEGRO_EVENT_TIMER){
            plane i=m[plane_num];
            i.level=Rand(1,3);
            i.blood=i.level;
            if(i.level==1)i.img=al_load_bitmap("p1");
            if(i.level==2)i.img=al_load_bitmap("p2");
            if(i.level==3)i.img=al_load_bitmap("p3");
            i.tip=true;
            i.size=al_get_bitmap_width(i.img);
            i.x1=Rand(i.size,game_width-i.size);
            i.y1=0;
        }
        if(ev.type==ALLEGRO_EVENT_TIMER)time_t=true;
        if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE||ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
            Destroy_Allegro(n);
            break;
        }
        if(time_t&&al_is_event_queue_empty(n.event_queue)){
            //计算路径
            for(int i=0;i<MAXSIZE;i++){
                for(int a=0;a<MAXSIZE;a++){
                    if(!m[i].m[a].tip)continue;
                    m[i].m[a].x1+=m[i].m[a].x2;
                    m[i].m[a].y1+=m[i].m[a].y2;
                }
                if(!m[i].tip||m[i].blood==0)continue;
                m[i].x1+=m[i].x2;
                m[i].y1+=m[i].y2;
            }
            //显示
            for(int i=0;i<MAXSIZE;i++){
                for(int a=0;a<MAXSIZE;a++){
                    if(!m[i].m[a].tip)continue;
                    al_draw_bitmap(m[i].m[a].img,m[i].m[a].x1,m[i].m[a].y1,0);
                }
                if(!m[i].tip||m[i].blood==0)continue;
                al_draw_bitmap(m[i].img,m[i].x1,m[i].y1,0);
            }
            //爆炸效果
            for(int i=0;i<MAXSIZE;i++){
                if(m[i].blood==0&&m[i].tip){
                    if(m[i].size<=0)m[i].tip=false;
                    al_draw_circle(m[i].x1,m[i].y1,my.size-m[i].size,al_map_rgb(Rand(0,255),Rand(0,255),Rand(0,255)),m[i].size);
                    m[i].size--;
                }
            }
            //飞机移动
            if(ev.type==ALLEGRO_EVENT_KEY_DOWN){
                switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_W:key_up=true;break;
                case ALLEGRO_KEY_S:key_down=true;break;
                case ALLEGRO_KEY_A:key_left=true;break;
                case ALLEGRO_KEY_D:key_right=true;break;
                case ALLEGRO_KEY_LEFT:key_left=true;break;
                case ALLEGRO_KEY_RIGHT:key_right=true;break;
                case ALLEGRO_KEY_UP:key_up=true;break;
                case ALLEGRO_KEY_DOWN:key_down=true;break;
                }
            }
            if(ev.type==ALLEGRO_EVENT_KEY_UP){
                switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_W:key_up=false;break;
                case ALLEGRO_KEY_S:key_down=false;break;
                case ALLEGRO_KEY_A:key_left=false;break;
                case ALLEGRO_KEY_D:key_right=false;break;
                case ALLEGRO_KEY_LEFT:key_left=false;break;
                case ALLEGRO_KEY_RIGHT:key_right=false;break;
                case ALLEGRO_KEY_UP:key_up=false;break;
                case ALLEGRO_KEY_DOWN:key_down=false;break;
                }
            }
            al_draw_bitmap(n.bitmap,0,0,0);
            al_draw_bitmap(my.img,my.x1,my.y1,0);
            al_flip_display();
            time_t=false;
        }
    }
    return true;
}
void al_end_game(allegro n)
{
    al_draw_bitmap(n.bitmap,0,0,0);
    al_flip_display();
}
bool judge_inside(ALLEGRO_EVENT ev,ALLEGRO_BITMAP *bitmap,int dx,int dy)
{
    int a=ev.mouse.x;
    int b=ev.mouse.y;
    if(a<dx)return false;
    if(a>dx+al_get_bitmap_width(bitmap))return false;
    if(b<dy)return false;
    if(b>dy+al_get_bitmap_height(bitmap))return false;
    return true;
}
void Init_Bullet(bullet n[MAXSIZE])
{
    for(int i=0;i<MAXSIZE;i++){
        n[i].tip=false;
        n[i].x1=0;
        n[i].x2=0;
        n[i].y1=0;
        n[i].y2=0;
    }
}
void Init_Plane(plane n)
{
    n.tip=false;
    n.img=NULL;
    n.bullet_num=0;
    n.blood=10;
    Init_Bullet(n.m);
}
void Draw_Plane(plane n)
{
    if(n.tip)al_draw_bitmap(n.img,n.x1,n.y1,0);
    Draw_Bullet(n.m);
}
void Draw_Bullet(bullet n[MAXSIZE])
{
    for(int i=0;i<MAXSIZE;i++){
        if(n[i].tip)al_draw_bitmap(n[i].img,n[i].x1,n[i].y1,0);
    }
}
int Rand(int low,int high)
{
    int i=rand();
    float m=i/((float)RAND_MAX+1);
    m=m*(high-low+1)+low;
    return (int)m;
}
