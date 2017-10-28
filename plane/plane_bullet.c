#include "plane_bullet.h"
#include"game.h"

int plane_space = 0;//飞机出现jian ge
int bullet_space = 0;//子弹出现时间
int buff_space = 0;
bool key_up=false;
bool key_down=false;
bool key_left=false;
bool key_right=false;
int score=0;
plane p=NULL;
bullet q=NULL;
Buff z = NULL;
bool effect = false;
int effect_time = 0;

void Init_Plane(plane n,int file_num)
{
    if(file_num){
        read(file_num,&n->x1,sizeof(float));
        n->x1=n->x1*screen_width;
        read(file_num,&n->y1,sizeof(float));
        n->y1=n->y1*screen_height;
        read(file_num,&n->x2,sizeof(float));
        read(file_num,&n->y2,sizeof(float));
        read(file_num,&n->speed,sizeof(float));
        read(file_num,&n->level,sizeof(int));
        read(file_num,&n->blood,sizeof(int));
        read(file_num,&n->form,sizeof(int));
        read(file_num,&n->live,sizeof(bool));
        sprintf(num,"../UI/%d/plane_01/plane_0.png",screen_width);
        n->img =al_load_bitmap(num);
        n->size=al_get_bitmap_width(n->img);
        n->bull=NULL;
        Init_Bullet(&n->bull,file_num);
    }
    else{
        n->level = 1;
        n->blood = 10;
        n->live = true;
        sprintf(num,"../UI/%d/plane_01/plane_0.png",screen_width);
        n->img=al_load_bitmap(num);
        n->size = 0.9*al_get_bitmap_width(n->img);
        n->x1 = 0.5 * game_width - n->size;
        n->y1 = game_height - n->size;
        n->x2 = 0;
        n->y2 = 0;
        n->form=39;
        n->next=NULL;
        n->bull=NULL;
    }
}
void Init_Bullet(bullet *n,int file_num)
{
    char k[MAXSIZE];
    int i=0;
    if(file_num){
        q=*n;
        read(file_num,&i,sizeof(int));
        while(i){
            bullet m=(bullet)malloc(sizeof(Bullet));
            read(file_num,&m->x1,sizeof(float));
            m->x1=m->x1*game_width;
            read(file_num,&m->y1,sizeof(float));
            m->y1=m->y1*game_height;
            read(file_num,&m->x2,sizeof(float));
            read(file_num,&m->y2,sizeof(float));
            read(file_num,&m->speed,sizeof(float));
            read(file_num,&m->attack,sizeof(int));
            read(file_num,&m->form,sizeof(int));
            read(file_num,&m->live,sizeof(bool));
            read(file_num,k,sizeof(char)*MAXSIZE);
            m->next=NULL;
            sprintf(num,"../UI/%d/%s",screen_width,k);
            m->img=al_load_bitmap(num);
            if(!*n){
                *n=m;
                q=*n;
            }
            else{
                q->next=m;
                q=q->next;
            }
            i--;
        }
    }
}
void Init_enemyplane(plane *n,int file_num)
{
    int i=0;
    char k[MAXSIZE];
    if(file_num){
        read(file_num,&i,sizeof(int));
        p=*n;
        while(i){
            plane m=(plane)malloc(sizeof(Plane));
            read(file_num,&m->x1,sizeof(float));
            m->x1=m->x1*game_width;
            read(file_num,&m->y1,sizeof(float));
            m->y1=m->y1*game_height;
            read(file_num,&m->x2,sizeof(float));
            read(file_num,&m->y2,sizeof(float));
            read(file_num,&m->speed,sizeof(float));
            read(file_num,&m->level,sizeof(int));
            read(file_num,&m->blood,sizeof(int));
            read(file_num,&m->form,sizeof(int));
            read(file_num,&m->live,sizeof(bool));
            read(file_num,k,sizeof(char)*MAXSIZE);
            sprintf(num,"../UI/%d/%s",screen_width,k);
            m->img=al_load_bitmap(num);
            m->size=al_get_bitmap_width(m->img);
            m->bull=NULL;
            m->next=NULL;
            Init_Bullet(&m->bull,file_num);
            if(!*n){
                *n=m;
                p=*n;
            }
            else{
                p->next=m;
                p=p->next;
            }
            i--;
        }
    }
}
bool Draw_plane_bullet(allegro n,int file_num)
{
    int k=0;
    img_x=0.5*game_width;
    img_y=game_height-0.5*al_get_bitmap_height(n.bitmap);
    Plane my;
    plane enemy_plane=NULL;
    Buff buff=NULL;
    if(file_num)read(file_num,&score,sizeof(int));
    Init_Plane(&my,file_num);
    Init_enemyplane(&enemy_plane,file_num);
//    Init_buff(buff);
    int bullet_num = 0;
    int plane_rate = 0;
    int buff_rate = 0;
    bool redraw = false;
    while(1){
        if(!my.live){
            p=enemy_plane;
            while(p){
                q=p->bull;
                while(q){
                    bullet a=q;
                    q=q->next;
                    free(a);
                }
                plane b=p;
                p=p->next;
                free(b);
            }
            q=my.bull;
            while(q){
                bullet a=q;q=q->next;
                free(a);
            }
            z=buff;
            while(z){
                Buff a = z;
                z=z->next;
                free(a);
            }
            exit(score);
        }
        my.speed = my.level;
        plane_space = game_height / (5 + 2 * my.level);
        bullet_space = game_height / (5 + 2 * my.level);
        buff_space = 500;
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)redraw = true;
        if(ev.keyboard.keycode==ALLEGRO_KEY_SPACE)al_pause(n,&my,enemy_plane);
        if(redraw && al_is_event_queue_empty(n.event_queue)){
            //加入子弹
            if(bullet_num >= bullet_space/4){
                if(my.live){
                    bullet m=(bullet)malloc(sizeof(Bullet));
                    m->live = true;
                    m->next=NULL;
                    m->attack = 1;
                    m->form = 0;
                    m->speed =4*my.speed;
                    sprintf(num,"../UI/%d/bullet_1/bullet_0.png",screen_width);
                    m->img = al_load_bitmap(num);
                    m->x1 = my.x1;
                    m->y1 = my.y1;
                    m->x2=0;
                    m->y2=0;
                    if(!my.bull)my.bull=m;
                    else{
                        q=my.bull;
                        while(q->next)q=q->next;
                        q->next=m;
                    }
                }
                p=enemy_plane;
                while(p){
                    if(p->blood!=0&&p->live){
                        bullet m=(bullet)malloc(sizeof(Bullet));
                        m->attack = p->level;
                        m->next=NULL;
                        m->live = true;
                        sprintf(num,"../UI/%d/enemy/b1.png",screen_width);
                        m->img = al_load_bitmap(num);
                        m->speed = 4*p->speed;
                        m->x1 = p->x1;
                        m->y1 = p->y1;
                        if(p->level<2){
                            m->x2 = 0;
                            m->y2 = m->speed;
                        }
                        else{
                            int distance = pow(pow((p->y1-my.y1),2)+pow((p->x1-my.x1),2),0.5);
                            m->x2 = m->speed * (my.x1-m->x1) /distance;
                            m->y2 = m->speed * (my.y1-m->y1) /distance;
                        }
                        if(!p->bull)p->bull=m;
                        else{
                            q=p->bull;
                            while(q->next)q=q->next;
                            q->next=m;
                        }
                    }
                    p=p->next;
                 }
                 bullet_num = 0;
            }
            bullet_num ++;
            //加入di飞机
            if(plane_rate>= plane_space){
                plane m=(plane)malloc(sizeof(Plane));
                m->level = Rand(1,3);
                m->next=NULL;
                m->bull=NULL;
                m->blood = m->level;
                sprintf(num,"../UI/%d/enemy/enemy%d.png",screen_width,m->level);
                m->img = al_load_bitmap(num);
                m->live = true;
                m->form = 39;
                m->speed =m->level;
                m->size=al_get_bitmap_width(m->img);
                m->x1= Rand(m->size,game_width-m->size);
                m->y1=-0.5*al_get_bitmap_height(m->img);
                if(m->level < 2){
                    m->x2 = 0;
                    m->y2 = m->speed;
                }
                else{
                    int distance=Distance(m->x1,m->y1,my.x1,my.y1);
                    m->x2=m->speed*(my.x1-m->x1)/distance;
                    m->y2=m->speed*(my.y1-m->y1)/distance;
                }
                if(!enemy_plane)enemy_plane=m;
                else{
                    p=enemy_plane;
                    while(p->next)p=p->next;
                    p->next=m;
                }
                plane_rate = 0;
            }
            plane_rate++;

            //join buff
            if(buff_rate >= buff_space){
                Buff b = (Buff)malloc(sizeof(BUFF));
                b->level = Rand(1,2);
                if(b->level == 1)b->form = 2;
                if(b->level== 2)b->form = 50;
                b->live = true;
                b->next = NULL;
                sprintf(num,"../UI/%d/buff_%d/buff_0.png",screen_width,b->level);
                b->img = al_load_bitmap(num);
                b->size = al_get_bitmap_width(b->img);
                b->x1 = Rand(b->size,game_width-b->size);
                b->y1 = -0.5 * b->size;
                b->speed = 1;
                b->x2 = 0;
                b->y2 = b->speed;

                if(!buff){
                    buff=b;
                }
                else{
                    z=buff;
                    while(z->next){
                        z=z->next;
                    }
                    z->next=b;
                }
                buff_rate = 0;
            }
            buff_rate++;

            //计算路径
            p=enemy_plane;
            while(p){
                q=p->bull;
                while(q){
                    if(q->live){
                        q->x1 += q->x2;
                        q->y1 += q->y2;
                    }
                    q=q->next;
                }
                if(p->blood!=0&&p->live){
                    p->x1 += p->x2;
                    p->y1 += p->y2;
                }
                p=p->next;
            }
            q=my.bull;
            while(q){
                if(q->live){
                    q->y1-=q->speed;
                    sprintf(num,"../UI/%d/bullet_1/bullet_%d.png",screen_width,q->form/5);
                    if(q->img)al_destroy_bitmap(q->img);
                    q->img=al_load_bitmap(num);
                    q->form++;
                    if(q->form>74)q->form=5;
                }
                q=q->next;
            }
            z=buff;
            while(z){
                if(z->live){
                    z->x1 += z->x2;
                    z->y1 += z->y2;
                }
                z=z->next;
            }

            img_y+= 5;//背景滚动速度
            if(img_y>game_height+0.5*al_get_bitmap_height(n.bitmap))img_y=game_height-0.5*al_get_bitmap_height(n.bitmap);

            //判断事件
            if(effect){
                effect_time+=5;
                if(effect_time>=800){
                    effect_time = 0;
                    effect = false;
                }
            }
            boom(&my,&enemy_plane,&buff);
            //显示
            al_draw_pic(n.bitmap,img_x,img_y);
            al_draw_pic(n.bitmap,img_x,img_y-al_get_bitmap_height(n.bitmap));
            al_draw_pic(my.img,my.x1,my.y1);
            al_draw_life(my);
            sprintf(num,"%4d",score);
            al_draw_text(n.font1,white,0.02*game_width,
                         0.01*game_height,ALLEGRO_ALIGN_RIGHT,num);
            z=buff;
            while(z){
                if(z->live){
                    if(z->form<0){
                        if(z->level==1)z->form=2;
                        if(z->level==2)z->form=50;
                    }
                    sprintf(num,"../UI/%d/buff_%d/buff_%d.png",screen_width,z->level,z->form/3);
                    z->img=al_load_bitmap(num);
//                    if(z->img)al_destroy_bitmap(z->img);
                    al_draw_pic(z->img,z->x1,z->y1);
                    z->form--;
                }
                z=z->next;
            }
            q=my.bull;
            while(q){
                if(q->live)al_draw_pic(q->img,q->x1,q->y1);
                q=q->next;
            }
            p=enemy_plane;
            while(p){
                q=p->bull;
                while(q){
                    if(q->live)al_draw_pic(q->img,q->x1,q->y1);
                    q=q->next;
                }
                if(p->blood!=0&&p->live)al_draw_pic(p->img,p->x1,p->y1);
                p=p->next;
            }

            //爆炸效果
            p=enemy_plane;
            while(p){
                if(p->blood==0&&p->live){
                    sprintf(num,"../UI/%d/boom_01/boom_%d.png",screen_width,p->form/10);
                    if(p->img)al_destroy_bitmap(p->img);
                    p->img=al_load_bitmap(num);
                    al_draw_pic(p->img,p->x1,p->y1);
                    p->form--;
                    if(p->form<0){
                        score+=10;
                        p->live=false;
                    }
                }
                p=p->next;
            }
            if(my.blood<=0&&my.live){
                sprintf(num,"../UI/%d/boom_01/boom_%d.png",screen_width,my.form/10);
                if(my.img)al_destroy_bitmap(my.img);
                my.img=al_load_bitmap(num);
                al_draw_pic(my.img,my.x1,my.y1);
                my.form--;
                if(my.form<0){
                    my.live=false;
                }
            }
            al_flip_display();
            redraw=false;
            }
        //飞机移动
        //mouse
        if(ev.mouse.x>0.5*al_get_bitmap_width(my.img)&&ev.mouse.x<game_width-0.5*al_get_bitmap_width(my.img)&&
                ev.mouse.y>0.5*al_get_bitmap_height(my.img)&&ev.mouse.y<game_height-0.5*al_get_bitmap_height(my.img)){
            if(Distance(my.x1,my.y1,ev.mouse.x,ev.mouse.y)>my.size)al_set_mouse_xy(n.display,my.x1,my.y1);
            else{
                my.x1=ev.mouse.x;
                my.y1=ev.mouse.y;
            }
        }
        //keyboard
        al_move(ev,&my,&k);
    }
    return true;
}

void boom(plane n,plane *m,Buff *b)
{
    p=*m;
    while(p){
        //判断子弹是否出界
        q=p->bull;
        while(q){
            if(q->x1<-0.5*al_get_bitmap_width(q->img))q->live=false;
            else if(q->x1>game_width+0.5*al_get_bitmap_width(q->img))q->live=false;
            else if(q->y1<-0.5*al_get_bitmap_height(q->img))q->live=false;
            else if(q->y1>game_height+0.5*al_get_bitmap_height(q->img))q->live=false;
            q=q->next;
        }
        //判断敌机是否出界
        if(p->x1<-0.5*al_get_bitmap_width(p->img))p->live=false;
        else if(p->x1>game_width+0.5*al_get_bitmap_width(p->img))p->live=false;
        else if(p->y1<-0.5*al_get_bitmap_height(p->img))p->live=false;
        else if(p->y1>game_height+0.5*al_get_bitmap_height(p->img))p->live=false;
        p=p->next;

    }
    q=n->bull;
    while(q){
        if(q->x1<-0.5*al_get_bitmap_width(q->img))q->live=false;
        else if(q->x1>game_width+0.5*al_get_bitmap_width(q->img))q->live=false;
        else if(q->y1<-0.5*al_get_bitmap_height(q->img))q->live=false;
        else if(q->y1>game_height+0.5*al_get_bitmap_height(q->img))q->live=false;
        q=q->next;
    }

    //判断buff是否出界
    z = *b;
    while(z){
        if(z->x1<-0.5*al_get_bitmap_width(z->img))z->live=false;
        else if(z->x1>game_width
                +0.5*al_get_bitmap_width(z->img))z->live=false;
        else if(z->y1<-0.5*al_get_bitmap_height(z->img))z->live=false;
        else if(z->y1>game_height
                +0.5*al_get_bitmap_height(z->img))z->live=false;
        z = z->next;
    }

    if(n->blood>0&&!effect){//判断子弹是否命中
        p=*m;
        while(p){
            q=p->bull;
            while(q){
                if(q->live&&n->blood!=0){
                    if(Distance(q->x1,q->y1,n->x1,n->y1)<0.5*(n->size+al_get_bitmap_width(q->img))){
                        q->live=false;
                        n->blood--;
                    }
                }
                q=q->next;
            }
            p=p->next;
        }
    }
    if(n->blood>0){
        q=n->bull;
        while(q){
            if(q->live){//判断子弹是否击中敌机
                p=*m;
                while(p){
                    if(p->live&&p->blood!=0){
                        if(Distance(q->x1,q->y1,p->x1,p->y1)<0.5*(p->size+al_get_bitmap_width(q->img))){
                            q->live=false;
                            p->blood--;
                        }
                    }
                    p=p->next;
                }
            }
            q=q->next;
        }
    }
    if(n->blood>0&& !effect){
        p=*m;
        while(p){
            if(p->blood!=0&&p->live){
                if(Distance(n->x1,n->y1,p->x1,p->y1)<0.5*(p->size+n->size)){
                    n->blood--;
                    p->blood=0;
                }
            }
            p=p->next;
        }
    }
    if(n->blood>0){
        z = *b;
        while(z){
            if(z->live){
                if(Distance(n->x1,n->y1,z->x1,z->y1)<0.5*(z->size+n->size)){
                    if(z->level == 1){
                        n->blood++;
                    }
                    if(z->level == 2){
                        effect = true;
                    }
                    z->live = false;
                }
            }
           z = z->next;
        }
    }
    p=*m;
    plane p1=*m;
    plane p2=NULL;
    if(p1)p2=p1->next;
    while(p2){
        bullet q1=p2->bull,q2=NULL;
        if(q1)q2=q1->next;
        while(q2){
            if(!q2->live){
                q1->next=q2->next;
                bullet a=q2;
                q2=NULL;
                free(a);
            }
            q1=q1->next;
            if(!q1)break;
            q2=q1->next;
        }
        if(p2->bull&&!p2->bull->live){
            bullet a=p2->bull;
            p2->bull=p2->bull->next;
            free(a);
        }
        if(!p2->live&&!p2->bull){
            p1->next=p2->next;
            plane a=p2;
            p2=NULL;
            free(a);
        }
        p1=p1->next;
        if(!p1)break;
        p2=p1->next;
    }
    if((*m)&&!(*m)->live&&!(*m)->bull){
        plane a=*m;
        *m=(*m)->next;
        free(a);
    }
    bullet q1=n->bull,q2=NULL;
    if(q1)q2=q1->next;
    while(q2){
        if(!q2->live){
            q1->next=q2->next;
            bullet a=q2;
            q2=NULL;
            free(a);
        }
        q1=q1->next;
        if(!q1)break;
        q2=q1->next;
    }
    if(n->bull&&!n->bull->live){
        bullet a=n->bull;
        n->bull=n->bull->next;
        free(a);
    }
}
void al_move(ALLEGRO_EVENT ev, plane my,int *plane_num)
{
    int k=*plane_num;
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
        my->y1+=my->speed;
        if(my->y1>game_height-0.5*my->size)my->y1=game_height-0.5*my->size;
    }
    if(key_left){
        if(k>-7)k--;
        sprintf(num,"../UI/%d/plane_01/plane_%d.png",screen_width,k);
        al_destroy_bitmap(my->img);
        my->img=al_load_bitmap(num);
        my->x1-=my->speed;
        if(my->x1<0.5*my->size)my->x1=0.5*my->size;
    }
    else{
        if(k<0)k++;
        sprintf(num,"../UI/%d/plane_01/plane_%d.png",screen_width,k);
        al_destroy_bitmap(my->img);
        my->img=al_load_bitmap(num);
    }
    if(key_right){
        if(k<7)k++;
        sprintf(num,"../UI/%d/plane_01/plane_%d.png",screen_width,k);
        al_destroy_bitmap(my->img);
        my->img=al_load_bitmap(num);
        my->x1+=my->speed;
        if(my->x1>game_width-0.5*my->size)my->x1=game_width-0.5*my->size;
    }
    else{
        if(k>0)k--;
        sprintf(num,"../UI/%d/plane_01/plane_%d.png",screen_width,k);
        al_destroy_bitmap(my->img);
        my->img=al_load_bitmap(num);
    }
    if(key_up){
        my->y1-=my->speed;
        if(my->y1<0.5*my->size)my->y1=0.5*my->size;
    }
    *plane_num=k;
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


