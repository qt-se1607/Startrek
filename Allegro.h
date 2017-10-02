#include"variate.h"
void Init_Allegro(allegro n);
void Init_Display(allegro n);
void Destroy_Allegro(allegro n);
void Init_Queue(allegro n);
void Init_Display(allegro n);
bool al_start_game(allegro n);
bool al_join_game(allegro n);
bool al_end_game(allegro n);
void Init_Bullet(bullet *n);
void Init_Plane(plane *n);
void Draw_plane(plane n);
void Draw_Bullet(bullet n[MAXSIZE]);
void add_bullet(bullet n);
int Rand(int low,int high);
void is(plane *n, plane *m);
int Distance(int x1,int y1,int x2,int y2);
void al_draw_pic(ALLEGRO_BITMAP *n,int x,int y);
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
    img_x=0.5*screen_width;
    img_y=0.5*screen_height;
    al_draw_bitmap(n.bitmap,0,0,0);
}
bool al_start_game(allegro n)
{
            al_flip_display();
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
    return true;
}
bool al_join_game(allegro n)
{
    plane my,m[MAXSIZE];

    //my_airplane
    Init_Plane(&my);
    my.level=1;
    my.blood=1;
    Init_Bullet(my.m);
    my.tip=true;
    my.img=al_load_bitmap("../startrek/timg.png");
    my.size=al_get_bitmap_width(my.img);
    my.x1=0.5*game_width-my.size;
    my.y1=game_height-my.size;
    //my_airplane

    int plane_num=0,num_bullet=0,num_plane=0;
    bool time_t=false;
    for(int i=0;i<MAXSIZE;i++)Init_Plane(&m[i]);
    while(1){
        my.speed=my.level;
        plane_time=game_height/(5+2*my.level);
        bullet_time=game_height/(5+2*my.level);
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.type==ALLEGRO_EVENT_TIMER)time_t=true;
        if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE||ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)break;
        if(time_t&&al_is_event_queue_empty(n.event_queue)){
            //加入子弹
            if(num_bullet>=bullet_time){
                if(my.tip){
                    my.m[my.bullet_num].tip=true;
                    my.m[my.bullet_num].attack=1;
                    my.m[my.bullet_num].speed=2*my.speed;
                    my.m[my.bullet_num].img=al_load_bitmap("../startrek/ship.png");
                    my.m[my.bullet_num].x1=my.x1;
                    my.m[my.bullet_num].y1=my.y1;
                    my.bullet_num++;
                    if(my.bullet_num>=MAXSIZE)my.bullet_num=0;
                }
                for(int i=0;i<MAXSIZE;i++){
                    if(m[i].tip&&m[i].blood!=0){
                        m[i].m[m[i].bullet_num].attack=m[i].level;
                        m[i].m[m[i].bullet_num].tip=true;
                        m[i].m[m[i].bullet_num].img=al_load_bitmap("../startrek/b1.png");
                        m[i].m[m[i].bullet_num].speed=2*m[i].speed;
                        m[i].m[m[i].bullet_num].x1=m[i].x1;
                        m[i].m[m[i].bullet_num].y1=m[i].y1;
                        if(m[i].level<2){
                            m[i].m[m[i].bullet_num].x2=0;
                            m[i].m[m[i].bullet_num].y2=m[i].m[m[i].bullet_num].speed;
                        }
                        else{
                            int distance=pow(pow((m[i].y1-my.y1),2)+pow((m[i].x1-my.x1),2),0.5);
                            m[i].m[m[i].bullet_num].x2=m[i].m[m[i].bullet_num].speed*(my.x1-m[i].x1)/distance;
                            m[i].m[m[i].bullet_num].y2=m[i].m[m[i].bullet_num].speed*(my.y1-m[i].y1)/distance;
                        }
                        m[i].bullet_num++;
                        if(m[i].bullet_num>=MAXSIZE)m[i].bullet_num=0;
                    }
                 }
                 num_bullet=0;
            }
            num_bullet++;

            //加入飞机
            if(num_plane>=plane_time){
                m[plane_num].level=Rand(1,3);
                m[plane_num].blood=m[plane_num].level;
                if(m[plane_num].level==1)m[plane_num].img=al_load_bitmap("../startrek/p1.png");
                if(m[plane_num].level==2)m[plane_num].img=al_load_bitmap("../startrek/p2.png");
                if(m[plane_num].level==3)m[plane_num].img=al_load_bitmap("../startrek/p2.png");
                m[plane_num].tip=true;
                m[plane_num].speed=m[plane_num].level;
                m[plane_num].size=al_get_bitmap_width(m[plane_num].img);
                m[plane_num].x1=Rand(m[plane_num].size,game_width-m[plane_num].size);
                m[plane_num].y1=-0.5*m[plane_num].size;
                if(m[plane_num].level<2){
                    m[plane_num].x2=0;
                    m[plane_num].y2=m[plane_num].speed;
                }
                else{
                    int distance=Distance(m[plane_num].x1,m[plane_num].y1,my.x1,my.y1);
                    m[plane_num].x2=m[plane_num].speed*(my.x1-m[plane_num].x1)/distance;
                    m[plane_num].y2=m[plane_num].speed*(my.y1-m[plane_num].y1)/distance;
                }
                plane_num++;
                if(plane_num>=MAXSIZE)plane_num=0;
                num_plane=0;
            }
            num_plane++;

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
            for(int i=0;i<MAXSIZE;i++)if(my.m[i].tip)my.m[i].y1-=my.m[i].speed;
            img_y+=5;//背景滚动速度
            if(img_y>1.5*game_height)img_y=0.5*game_height;

            //判断事件
            is(&my,m);

            //显示
            al_draw_pic(n.bitmap,img_x,img_y);
            al_draw_pic(n.bitmap,img_x,img_y-game_height);
            al_draw_pic(my.img,my.x1,my.y1);
            for(int i=0;i<MAXSIZE;i++)if(my.m[i].tip)al_draw_pic(my.m[i].img,my.m[i].x1,my.m[i].y1);
            for(int i=0;i<MAXSIZE;i++){
                for(int a=0;a<MAXSIZE;a++)if(m[i].m[a].tip)al_draw_pic(m[i].m[a].img,m[i].m[a].x1,m[i].m[a].y1);
                if(m[i].tip&&m[i].blood!=0)al_draw_pic(m[i].img,m[i].x1,m[i].y1);
            }

            //爆炸效果
            for(int i=0;i<MAXSIZE;i++){
                if(m[i].blood==0&&m[i].tip){
                    al_draw_circle(m[i].x1,m[i].y1,my.size-m[i].size,
                                   al_map_rgb(Rand(0,255),Rand(0,255),Rand(0,255)),
                                   m[i].size);
                    m[i].size--;
                    if(m[i].size<=0)m[i].tip=false;
                }
            }
            al_flip_display();
            time_t=false;
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
        if(key_down){
            my.y1+=my.speed;
            if(my.y1>game_height-0.5*my.size)my.y1=game_height-0.5*my.size;
        }
        if(key_left){
            my.x1-=my.speed;
            if(my.x1<0.5*my.size)my.x1=0.5*my.size;
        }
        if(key_right){
            my.x1+=my.speed;
            if(my.x1>game_width-0.5*my.size)my.x1=game_width-0.5*my.size;
        }
        if(key_up){
            my.y1-=my.speed;
            if(my.y1<0.5*my.size)my.y1=0.5*my.size;
        }
    }
    return true;
}
void is(plane *n,plane *m)
{
    for(int a=0;a<MAXSIZE;a++){
        for(int b=0;b<MAXSIZE;b++){
            if(!m[a].m[b].tip)continue;
            if(m[a].m[b].x1<-0.5*al_get_bitmap_width(m[a].m[b].img))m[a].m[b].tip=false;
            else if(m[a].m[b].x1>game_width+0.5*al_get_bitmap_width(m[a].m[b].img))m[a].m[b].tip=false;
            else if(m[a].m[b].y1<-0.5*al_get_bitmap_height(m[a].m[b].img))m[a].m[b].tip=false;
            else if(m[a].m[b].y1>game_height+0.5*al_get_bitmap_height(m[a].m[b].img))m[a].m[b].tip=false;
        }
        if(!m[a].tip)continue;
        if(m[a].x1<-0.5*al_get_bitmap_width(m[a].img))m[a].tip=false;
        else if(m[a].x1>game_width+0.5*al_get_bitmap_width(m[a].img))m[a].tip=false;
        else if(m[a].y1<-0.5*al_get_bitmap_height(m[a].img))m[a].tip=false;
        else if(m[a].y1>game_height+0.5*al_get_bitmap_height(m[a].img))m[a].tip=false;
    }
    if(n->blood>0)
        for(int a=0;a<MAXSIZE;a++)
            for(int b=0;b<MAXSIZE;b++){
                if(!m[a].m[b].tip||n->blood==0)continue;
                if(Distance(m[a].m[b].x1,m[a].m[b].y1,n->x1,n->y1)<0.5*(n->size+al_get_bitmap_width(m[a].m[b].img))){
                    m[a].m[b].tip=false;
                    n->blood--;
                }
            }
    for(int a=0;a<MAXSIZE;a++){
        if(!n->m[a].tip)continue;
        for(int b=0;b<MAXSIZE;b++){
            if(m[b].tip&&m[b].blood!=0)
                if(Distance(n->m[a].x1,n->m[a].y1,m[b].x1,m[b].y1)<0.5*(m[b].size+al_get_bitmap_width(n->m[a].img))){
                    n->m[a].tip=false;
                    m[b].blood--;
                }
        }
    }
}

bool al_end_game(allegro n)
{
    ALLEGRO_EVENT ev;
    al_wait_for_event(n.event_queue,&ev);

    if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE||ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return true;
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
void Init_Bullet(bullet *n)
{
    for(int i=0;i<MAXSIZE;i++){
        n[i].tip=false;
        n[i].x1=0;
        n[i].x2=0;
        n[i].y1=0;
        n[i].y2=0;
        n[i].attack=0;
        n[i].speed=0;
    }
}
void Init_Plane(plane *n)
{
    n->tip=false;
    n->img=NULL;
    n->bullet_num=0;
    n->blood=10;
    n->level=0;
    n->x1=0;
    n->y1=0;
    n->x2=0;
    n->y2=0;
    Init_Bullet(n->m);
}
int Rand(int low,int high)
{
    int i=rand();
    float m=i/((float)RAND_MAX+1);
    m=m*(high-low+1)+low;
    return (int)m;
}
void al_draw_pic(ALLEGRO_BITMAP *n,int x,int y)
{
    al_identity_transform(&transform);
    al_translate_transform(&transform,x-0.5*al_get_bitmap_width(n),y-0.5*al_get_bitmap_height(n));
    al_use_transform(&transform);
    al_draw_bitmap(n,0,0,0);
    al_identity_transform(&transform);
}
int Distance(int x1,int y1,int x2,int y2)
{
    return pow(pow(x1-x2,2)+pow(y1-y2,2),0.5);
}
