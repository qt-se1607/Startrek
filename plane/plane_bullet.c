#include "plane_bullet.h"

int plane_space = 0;//飞机出现jian ge
int bullet_space = 0;//子弹出现时间
bool key_up=false;
bool key_down=false;
bool key_left=false;
bool key_right=false;

void Init_Plane(plane *n)
{
    n->live = false;
    n->img = NULL;
    n->bullet_num = 0;
    n->blood = 10;
    n->level = 0;
    n->x1 = 0;
    n->y1 = 0;
    n->x2 = 0;
    n->y2 = 0;
    Init_Bullet(n->bull);
}
void Init_Bullet(bullet n[])
{
    for(int i = 0;i < MAXSIZE;i++){
        n[i].live = false;
        n[i].x1 = 0;
        n[i].x2 = 0;
        n[i].y1 = 0;
        n[i].y2 = 0;
        n[i].attack = 0;
        n[i].speed = 0;
    }
}
void Init_enemyplane(plane n[MAXSIZE])
{
    for(int i = 0; i < MAXSIZE;i++)
    {
        n[i].live = false;
        n[i].img = NULL;
        n[i].bullet_num = 0;
        n[i].blood = 0;
        n[i].level = 0;
        n[i].x1 = 0;
        n[i].y1 = 0;
        n[i].x2 = 0;
        n[i].y2 = 0;
        Init_Bullet(n[i].bull);
    }
}
bool Draw_plane_bullet(allegro m)
{
    int k=0;
    img_x=0.5*game_width;
    img_y=game_height-0.5*al_get_bitmap_height(m.bitmap);
    plane n;
    plane enemy_plane[MAXSIZE];

    Init_Plane(&n);
    Init_enemyplane(enemy_plane);
    n.level = 1;
    n.blood = 10;
    n.live = true;
    sprintf(num,"../UI/plane_01/plane_%d.png",k);
    n.img=al_load_bitmap(num);
    n.size = 0.9*al_get_bitmap_width(n.img);
    n.x1 = 0.5 * game_width - n.size;
    n.y1 = game_height - n.size;
    int plane_num = 0;
    int bullet_num = 0;
    int plane_rate = 0;
    bool redraw = false;
    //al_set_mouse_xy(m.display,0.5*game_width,game_height+1);
    while(1){
        if(!n.live)exit(10);
        n.speed = n.level;
        plane_space = game_height / (5 + 2 * n.level);
        bullet_space = game_height / (5 + 2 * n.level);
        ALLEGRO_EVENT ev;
        al_wait_for_event(m.event_queue,&ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)redraw = true;
        if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE||ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)exit(99);
        if(redraw && al_is_event_queue_empty(m.event_queue)){
            //加入子弹
            if(bullet_num >= bullet_space){
                if(n.live){
                    n.bull[n.bullet_num].live = true;
                    n.bull[n.bullet_num].attack = 1;
                    n.bull[n.bullet_num].form = 0;
                    n.bull[n.bullet_num].speed = 2 * n.speed;
                    n.bull[n.bullet_num].img = al_load_bitmap("../UI/bullet_01/bullet_0.png");
                    n.bull[n.bullet_num].x1 = n.x1;
                    n.bull[n.bullet_num].y1 = n.y1;
                    n.bullet_num ++;
                    if(n.bullet_num >= MAXSIZE){
                        n.bullet_num = 0;
                    }
                }
                for(int i = 0;i < MAXSIZE;i++){
                    if(enemy_plane[i].live && enemy_plane[i].blood != 0){
                        enemy_plane[i].bull[enemy_plane[i].bullet_num].attack = enemy_plane[i].level;
                        enemy_plane[i].bull[enemy_plane[i].bullet_num].live = true;
                        enemy_plane[i].bull[enemy_plane[i].bullet_num].img = al_load_bitmap("../UI/enemy/b1.png");
                        enemy_plane[i].bull[enemy_plane[i].bullet_num].speed = 2 * enemy_plane[i].speed;
                        enemy_plane[i].bull[enemy_plane[i].bullet_num].x1 = enemy_plane[i].x1;
                        enemy_plane[i].bull[enemy_plane[i].bullet_num].y1 = enemy_plane[i].y1;
                        if(enemy_plane[i].level < 2){
                            enemy_plane[i].bull[enemy_plane[i].bullet_num].x2 = 0;
                            enemy_plane[i].bull[enemy_plane[i].bullet_num].y2 = enemy_plane[i].bull[enemy_plane[i].bullet_num].speed;
                        }
                        else{
                            int distance = pow(pow((enemy_plane[i].y1-n.y1),2)+pow((enemy_plane[i].x1-n.x1),2),0.5);
                            enemy_plane[i].bull[enemy_plane[i].bullet_num].x2 = enemy_plane[i].bull[enemy_plane[i].bullet_num].speed * (n.x1-enemy_plane[i].x1) /distance;
                            enemy_plane[i].bull[enemy_plane[i].bullet_num].y2 = enemy_plane[i].bull[enemy_plane[i].bullet_num].speed * (n.y1-enemy_plane[i].y1) /distance;
                        }
                        enemy_plane[i].bullet_num ++;
                        if(enemy_plane[i].bullet_num >= MAXSIZE){
                            enemy_plane[i].bullet_num = 0;
                        }
                    }
                 }
                 bullet_num = 0;
            }
            bullet_num ++;

            //加入di飞机
            if(plane_rate >= plane_space){
                enemy_plane[plane_num].level = Rand(1,3);
                enemy_plane[plane_num].blood = enemy_plane[plane_num].level;
                if(enemy_plane[plane_num].level == 1){
                    enemy_plane[plane_num].img = al_load_bitmap("../UI/enemy/enemy1.png");
                }
                if(enemy_plane[plane_num].level == 2){
                    enemy_plane[plane_num].img = al_load_bitmap("../UI/enemy/enemy1.png");
                }
                if(enemy_plane[plane_num].level == 3){
                    enemy_plane[plane_num].img = al_load_bitmap("../UI/enemy/enemy1.png");
                }
                enemy_plane[plane_num].live = true;
                enemy_plane[plane_num].form = 39;
                enemy_plane[plane_num].speed = enemy_plane[plane_num].level;
                enemy_plane[plane_num].size=al_get_bitmap_width(enemy_plane[plane_num].img);
                enemy_plane[plane_num].x1= Rand(enemy_plane[plane_num].size,game_width-enemy_plane[plane_num].size);
                enemy_plane[plane_num].y1=-0.5*enemy_plane[plane_num].size;
                if(enemy_plane[plane_num].level < 2){
                    enemy_plane[plane_num].x2 = 0;
                    enemy_plane[plane_num].y2 = enemy_plane[plane_num].speed;
                }
                else{
                    int distance=Distance(enemy_plane[plane_num].x1,enemy_plane[plane_num].y1,n.x1,n.y1);
                    enemy_plane[plane_num].x2=enemy_plane[plane_num].speed*(n.x1-enemy_plane[plane_num].x1)/distance;
                    enemy_plane[plane_num].y2=enemy_plane[plane_num].speed*(n.y1-enemy_plane[plane_num].y1)/distance;
                }
                plane_num ++;
                if(plane_num >= MAXSIZE){
                    plane_num = 0;
                }
                plane_rate = 0;
            }
            plane_rate++;

            //计算路径
            for(int i = 0;i < MAXSIZE;i++){
                for(int a = 0;a < MAXSIZE;a++){
                    if(!enemy_plane[i].bull[a].live)
                        continue;
                    enemy_plane[i].bull[a].x1 += enemy_plane[i].bull[a].x2;
                    enemy_plane[i].bull[a].y1 += enemy_plane[i].bull[a].y2;
                }
                if(!enemy_plane[i].live || enemy_plane[i].blood == 0)
                    continue;
                enemy_plane[i].x1 += enemy_plane[i].x2;
                enemy_plane[i].y1 += enemy_plane[i].y2;
            }
            for(int i=0;i<MAXSIZE;i++){
                if(!n.bull[i].live)continue;
                n.bull[i].y1-=n.bull[i].speed;
                sprintf(num,"../UI/bullet_01/bullet_%d.png",n.bull[i].form/5);
                al_destroy_bitmap(n.bull[i].img);
                n.bull[i].img=al_load_bitmap(num);
                n.bull[i].form++;
                if(n.bull[i].form>74)n.bull[i].form=5;
            }

            img_y += 5;//背景滚动速度
            if(img_y>game_height+0.5*al_get_bitmap_height(m.bitmap))img_y=game_height-0.5*al_get_bitmap_height(m.bitmap);

            //判断事件
            boom(&n,enemy_plane);

            //显示
            al_draw_pic(m.bitmap,img_x,img_y);
            al_draw_pic(m.bitmap,img_x,img_y-al_get_bitmap_height(m.bitmap));
            al_draw_pic(n.img,n.x1,n.y1);
            for(int i=0;i<MAXSIZE;i++)
                if(n.bull[i].live)
                    al_draw_pic(n.bull[i].img,n.bull[i].x1,n.bull[i].y1);
            for(int i=0;i<MAXSIZE;i++){
                for(int a=0;a<MAXSIZE;a++)
                    if(enemy_plane[i].bull[a].live)
                        al_draw_pic(enemy_plane[i].bull[a].img,enemy_plane[i].bull[a].x1,enemy_plane[i].bull[a].y1);
                if(enemy_plane[i].live&&enemy_plane[i].blood!=0)
                    al_draw_pic(enemy_plane[i].img,enemy_plane[i].x1,enemy_plane[i].y1);
            }

            //爆炸效果
            for(int i=0;i<MAXSIZE;i++){
                if(enemy_plane[i].blood==0 && enemy_plane[i].live){
                    sprintf(num,"../UI/boom_01/boom_%d.png",enemy_plane[i].form/10);
                    al_destroy_bitmap(enemy_plane[i].img);
                    enemy_plane[i].img=al_load_bitmap(num);
                    al_draw_pic(enemy_plane[i].img,enemy_plane[i].x1,enemy_plane[i].y1);
                    enemy_plane[i].form--;
                    if(enemy_plane[i].form<0){
                        enemy_plane[i].live=false;
                    }
                }
            }
            if(n.blood<=0&&n.live){
                sprintf(num,"../UI/boom_01/boom_%d.png",n.form/10);
                al_destroy_bitmap(n.img);
                n.img=al_load_bitmap(num);
                al_draw_pic(n.img,n.x1,n.y1);
                n.form--;
                if(n.form==0){
                    n.live=false;
                }
            }
            al_flip_display();
            redraw=false;
            }
        //飞机移动
        //mouse
        /*if(ev.type==ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){
            if(ev.mouse.x!=n.x1||ev.mouse.y!=n.y1)al_set_mouse_xy(m.display,n.x1,n.y1);
        }*/
        //keyboard
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
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
            n.y1+=n.speed;
            if(n.y1>game_height-0.5*n.size)n.y1=game_height-0.5*n.size;
        }
        if(key_left){
            if(k>-7)k--;
            sprintf(num,"../UI/plane_01/plane_%d.png",k);
            al_destroy_bitmap(n.img);
            n.img=al_load_bitmap(num);
            n.x1-=n.speed;
            if(n.x1<0.5*n.size)n.x1=0.5*n.size;
        }
        else{
            if(k<0)k++;
            sprintf(num,"../UI/plane_01/plane_%d.png",k);
            al_destroy_bitmap(n.img);
            n.img=al_load_bitmap(num);
        }
        if(key_right){
            if(k<7)k++;
            sprintf(num,"../UI/plane_01/plane_%d.png",k);
            al_destroy_bitmap(n.img);
            n.img=al_load_bitmap(num);
            n.x1+=n.speed;
            if(n.x1>game_width-0.5*n.size)n.x1=game_width-0.5*n.size;
        }
        else{
            if(k>0)k--;
            sprintf(num,"../UI/plane_01/plane_%d.png",k);
            al_destroy_bitmap(n.img);
            n.img=al_load_bitmap(num);
        }
        if(key_up){
            n.y1-=n.speed;
            if(n.y1<0.5*n.size)n.y1=0.5*n.size;
        }
    }
    return true;
}

void boom(plane *n,plane *m)
{
    for(int a=0;a<MAXSIZE;a++){
        for(int b=0;b<MAXSIZE;b++){//判断子弹是否出界
            if(!m[a].bull[b].live)continue;
            if(m[a].bull[b].x1<-0.5*al_get_bitmap_width(m[a].bull[b].img))m[a].bull[b].live=false;
            else if(m[a].bull[b].x1>game_width+0.5*al_get_bitmap_width(m[a].bull[b].img))m[a].bull[b].live=false;
            else if(m[a].bull[b].y1<-0.5*al_get_bitmap_height(m[a].bull[b].img))m[a].bull[b].live=false;
            else if(m[a].bull[b].y1>game_height+0.5*al_get_bitmap_height(m[a].bull[b].img))m[a].bull[b].live=false;
        }
        if(!m[a].live)continue;//判断敌机是否出界
        if(m[a].x1<-0.5*al_get_bitmap_width(m[a].img))m[a].live=false;
        else if(m[a].x1>game_width+0.5*al_get_bitmap_width(m[a].img))m[a].live=false;
        else if(m[a].y1<-0.5*al_get_bitmap_height(m[a].img))m[a].live=false;
        else if(m[a].y1>game_height+0.5*al_get_bitmap_height(m[a].img))m[a].live=false;
    }
    for(int a=0;a>MAXSIZE;a++){
        if(!n->bull[a].live)continue;
        if(n->bull[a].x1<-0.5*al_get_bitmap_width(n->bull[a].img))n->bull[a].live=false;
        else if(n->bull[a].x1>game_width+0.5*al_get_bitmap_width(n->bull[a].img))n->bull[a].live=false;
        else if(n->bull[a].y1<-0.5*al_get_bitmap_height(n->bull[a].img))n->bull[a].live=false;
        else if(n->bull[a].y1>game_height+0.5*al_get_bitmap_height(n->bull[a].img))n->bull[a].live=false;
    }
    if(n->blood>0){//判断子弹是否命中
        for(int a=0;a<MAXSIZE;a++){
            for(int b=0;b<MAXSIZE;b++){
                if(!m[a].bull[b].live||n->blood==0)continue;
                if(Distance(m[a].bull[b].x1,m[a].bull[b].y1,n->x1,n->y1)<0.5*(n->size+al_get_bitmap_width(m[a].bull[b].img))){
                    m[a].bull[b].live=false;
                    n->blood--;
                }
            }
        }
    }
    if(n->blood>0){
        for(int a=0;a<MAXSIZE;a++){//判断子弹是否击中敌机
            if(!n->bull[a].live)continue;
            for(int b=0;b<MAXSIZE;b++){
                if(m[b].live&&m[b].blood!=0){
                    if(Distance(n->bull[a].x1,n->bull[a].y1,m[b].x1,m[b].y1)<0.5*(m[b].size+al_get_bitmap_width(n->bull[a].img))){
                        n->bull[a].live=false;
                        m[b].blood--;
                    }
                }
            }
        }
    }
    if(n->blood>0){
        for(int a=0;a<MAXSIZE;a++){
            if(!m[a].live)continue;
            if(Distance(n->x1,n->y1,m[a].x1,m[a].y1)<0.5*(m[a].size+n->size)){
                n->blood--;
                m[a].blood=0;
            }
        }
    }
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
    al_translate_transform(&transform,0,0);
    al_use_transform(&transform);
}

int Distance(int x1,int y1,int x2,int y2)
{
    return pow(pow(x1-x2,2)+pow(y1-y2,2),0.5);
}


