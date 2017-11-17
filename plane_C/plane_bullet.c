#include "plane_bullet.h"
#include "game.h"

bool key_up=false;
bool key_down=false;
bool key_left=false;
bool key_right=false;
int score=0;
plane p=NULL;
bullet q=NULL;
buff r= NULL;
int effect_protection = 0;
int effect_craze=0;
int effect_speed=0;

int plane_space = 0;
int bullet_space = 0;
int buff_space = 0;
int enemy_space=0;
int enemy_rate=0;
int bullet_rate = 0;
int plane_rate = 0;
int buff_rate = 0;

int gate=1;

void al_draw_list()
{
    int fp;
    if((fp=open("../UI/list/list",O_RDONLY))==-1){
        fp=open("../UI/list/list",O_CREAT|O_WRONLY);
        time_t temp;
        temp=time(&temp);
        write(fp,&score,sizeof(int));
        sprintf(num,"%s",ctime(&temp));
        write(fp,num,sizeof(char)*MAXSIZE);
        for(int i=1;i<7;i++){
            int k=0;
            temp=time(&temp);
            write(fp,&k,sizeof(int));
            sprintf(num,"%s",ctime(&temp));
            write(fp,num,sizeof(char)*MAXSIZE);
        }
        close(fp);
    }
    else{
        time_t temp;
        temp=time(&temp);
        int score_num[7];
        char string[7][MAXSIZE];
        for(int i=0;i<7;i++){
            read(fp,&score_num[i],sizeof(int));
            read(fp,string[i],sizeof(char)*MAXSIZE);
        }
        for(int i=0;i<7;i++){
            if(score>score_num[i]){
                for(int a=7-1;a>i;a--){
                    score_num[a]=score_num[a-1];
                    sprintf(string[a],"%s",string[a-1]);
                }
                score_num[i]=score;
                sprintf(string[i],"%s",ctime(&temp));
                break;
            }
        }
        close(fp);
        fp=open("../UI/list/list",O_CREAT|O_WRONLY);
        for(int i=0;i<7;i++){
            write(fp,&score_num[i],sizeof(int));
            write(fp,string[i],sizeof(char)*MAXSIZE);
        }
        close(fp);
    }
}

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
        n->x2 = n->x1;
        n->y2 = n->y1;
        n->form=39;
        n->next=NULL;
        n->bull=NULL;
    }
}

void Init_Bullet(bullet *n,int file_num)
{
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
            if(m->x2)sprintf(num,"../UI/%d/enemy/b%d.png",screen_width,m->form);
            else sprintf(num,"../UI/%d/bullet_1/bullet_%d.png",screen_width,m->form);
            m->img=al_load_bitmap(num);
            m->next=NULL;
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
            read(file_num,&m->level,sizeof(int));
            read(file_num,&m->blood,sizeof(int));
            read(file_num,&m->form,sizeof(int));
            read(file_num,&m->live,sizeof(bool));
            m->speed =game_height/(5-gate)/FPS;
            m->x2=m->x2*m->speed;
            m->y2=m->y2*m->speed;
            sprintf(num,"../UI/%d/enemy/enemy%d.png",screen_width,m->level);
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
void Init_buff(buff *n,int file_num)
{
    int i=0;
    if(file_num){
        read(file_num,&i,sizeof(int));
        r=*n;
        while(i){
            buff m=(buff)malloc(sizeof(Buff));
            read(file_num,&m->x1,sizeof(float));
            m->x1=m->x1*game_width;
            read(file_num,&m->y1,sizeof(float));
            m->y1=m->y1*game_height;
            read(file_num,&m->x2,sizeof(float));
            read(file_num,&m->y2,sizeof(float));
            read(file_num,&m->speed,sizeof(float));
            read(file_num,&m->level,sizeof(int));
            read(file_num,&m->form,sizeof(int));
            read(file_num,&m->live,sizeof(bool));
            sprintf(num,"../UI/%d/buff_%d/buff_%d.png",screen_width,m->level,m->form/3);
            m->img = al_load_bitmap(num);
            if(!m->img)perror(num);
            m->size=al_get_bitmap_width(m->img);
            m->next=NULL;
            if(!*n){
                *n=m;
                r=*n;
            }
            else{
                r->next=m;
                r=r->next;
            }
            i--;
        }
    }
}

void al_join_bullet(bullet *n, Plane M)
{
    bullet m=(bullet)malloc(sizeof(Bullet));
    m->live = true;
    m->next=NULL;
    m->attack = gate;
    m->form = 0;
    m->x1=M.x1;
    m->y1=M.y1;
    m->x2=0;
    m->y2=0;
    m->speed=M.speed*4;
    if(!*n){
        *n=m;
        q=*n;
    }
    else{
        q=*n;
        while(q->next)q=q->next;
        q->next=m;
        q=q->next;
    }
}

void al_join_plane(plane *n, Plane M)
{
    plane m=(plane)malloc(sizeof(Plane));
    if(score<60*(4*gate-3))m->level=Rand(0,2);
    else if(score<60*(4*gate-2))m->level=Rand(3,5);
    else if(score<60*(4*gate-1))m->level=Rand(6,8);
    else m->level=9;
    m->next=NULL;
    m->bull=NULL;
    m->blood = gate*(m->level/3+1);
    sprintf(num,"../UI/%d/enemy/enemy%d.png",screen_width,m->level);
    m->img = al_load_bitmap(num);
    if(!m->img)printf("%s\n",num);
    m->live = true;
    m->form = 39;
    m->speed =game_height/(5-gate)/FPS;
    m->size=al_get_bitmap_height(m->img);
    m->x1= Rand(m->size,game_width-m->size);
    m->y1=-0.5*m->size;
    if(m->level <= 3){
        m->x2 = 0;
        m->y2 = m->speed;
    }
    else if(m->level<=8){
        float distance=Distance(m->x1,m->y1,M.x1,M.y1);
        m->x2=m->speed*(M.x1-m->x1)/distance;
        m->y2=m->speed*(M.y1-m->y1)/distance;
    }
    else if(m->level==9){
        m->x1=0;
        m->x2=1;
        m->y2=1;
        m->blood=gate*50;
    }
    if(!*n){
        *n=m;
        p=*n;
    }
    else{
        p=*n;
        while(p->next)p=p->next;
        p->next=m;
        p=p->next;
    }
}

void al_join_buff(buff *n)
{
    buff b=(buff)malloc(sizeof(Buff));
    b->level = Rand(1,4);
    if(b->level == 1)b->form = 29;
    if(b->level == 2)b->form = 50;
    if(b->level == 3)b->form = 59;
    if(b->level == 4)b->form = 38;
    b->live = true;
    b->next = NULL;
    sprintf(num,"../UI/%d/buff_%d/buff_0.png",screen_width,b->level);
    b->img = al_load_bitmap(num);
    if(!b->img)perror(num);
    b->size = al_get_bitmap_width(b->img);
    b->x1 = Rand(b->size,game_width-b->size);
    b->y1 = -0.5 * b->size;
    b->speed = game_height/(6-gate)/FPS;
    b->x2 = 0;
    b->y2 = b->speed;
    if(!*n){
        *n=b;
        r=*n;
    }
    else{
        r=*n;
        while(r->next)r=r->next;
        r->next=b;
        r=r->next;
    }
}

bool Draw_plane_bullet(allegro n,int file_num)
{
    al_stop_timer(n.timer);
    int k=0;
    img_x=0.5*game_width;
    img_y=game_height-0.5*al_get_bitmap_height(n.bitmap);
    Plane my;
    plane enemy_plane=NULL;
    buff my_buff=NULL;
    if(file_num){
        read(file_num,&score,sizeof(int));
        read(file_num,&gate,sizeof(int));
        read(file_num,&effect_protection,sizeof(int));
        read(file_num,&effect_craze,sizeof(int));
        read(file_num,&effect_speed,sizeof(int));
        read(file_num,&plane_rate,sizeof(int));
        read(file_num,&enemy_rate,sizeof(int));
        read(file_num,&bullet_rate,sizeof(int));
        read(file_num,&buff_rate,sizeof(int));
    }
    Init_Plane(&my,file_num);
    Init_enemyplane(&enemy_plane,file_num);
    Init_buff(&my_buff,file_num);
    bool redraw = false;
    al_play_sample(n.bg,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    al_start_timer(n.timer);
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
            r=my_buff;
            while(r){
                buff a=r;
                r=r->next;
                free(a);
            }
            al_draw_list();
            exit(0);
        }
        if(score>60*(4*gate)&&gate!=3)gate++;
        my.speed=game_height/(5-my.level)/FPS;
        plane_space = FPS / (my.level+2);
        bullet_space = (4-gate)*FPS/(gate+1);
        enemy_space = (1-0.2*gate)*FPS;
        buff_space = 6*FPS/gate;
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)redraw = true;
        if(ev.type==ALLEGRO_EVENT_KEY_DOWN&&ev.keyboard.keycode==ALLEGRO_KEY_SPACE)al_pause(n,&my,enemy_plane,my_buff);
        if(redraw && al_is_event_queue_empty(n.event_queue)){
            //加入子弹
            if(plane_rate>=plane_space&&my.live){
                al_play_sample(n.biu,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                for(int i=0;i<my.level;i++){
                    al_join_bullet(&my.bull,my);
                    sprintf(num,"../UI/%d/bullet_1/bullet_%d.png",screen_width,i/2);
                    q->img = al_load_bitmap(num);
                    if(my.level==1)q->y1-=0.5*al_get_bitmap_height(my.img);
                    if(my.level>1){
                        if(i==0)q->x1-=0.4*al_get_bitmap_width(my.img);
                        if(i==1)q->x1+=0.4*al_get_bitmap_width(my.img);
                        if(i==2)q->y1-=0.5*al_get_bitmap_height(my.img);
                    }
                }
                plane_rate=0;
            }
            //加入敌方飞机
            if(enemy_rate>=enemy_space){
                al_join_plane(&enemy_plane,my);
                enemy_rate = 0;
            }
            if(bullet_rate>=bullet_space){
                p=enemy_plane;
                while(p){
                    if(p->blood!=0&&p->live&&p->level!=0){
                        al_join_bullet(&p->bull,*p);
                        sprintf(num,"../UI/%d/enemy/b%d.png",screen_width,p->level);
                        q->img = al_load_bitmap(num);
                        if(p->level<2){
                            q->x2 = 0;
                            q->y2 = q->speed;
                            q->y1+=0.5*al_get_bitmap_height(p->img);
                        }
                        else{
                            float distance = pow(pow((q->y1-my.y1),2)+pow((q->x1-my.x1),2),0.5);
                            q->x2 = q->speed * (my.x1-q->x1) /distance;
                            q->y2 = q->speed * (my.y1-q->y1) /distance;
                            q->y1+=0.5*al_get_bitmap_height(p->img)* (my.y1-q->y1) /distance;
                            q->x1+=0.5*al_get_bitmap_width(p->img)* (my.x1-q->x1) /distance;
                        }
                    }
                    p=p->next;
                }
                bullet_rate = 0;
            }
            //加入buff
            if(buff_rate >= buff_space){
                al_join_buff(&my_buff);
                buff_rate = 0;
            }
            buff_rate++;
            enemy_rate++;
            bullet_rate++;
            plane_rate++;

            //计算路径
            p=enemy_plane;
            while(p){
                q=p->bull;
                while(q){
                    if(p->live&&p->level==9){
                        if(q->x1<=0.5*al_get_bitmap_width(q->img)||
                                q->x1>=game_width-0.5*al_get_bitmap_width(q->img))q->x2=-q->x2;
                        if(q->y1<=0.5*al_get_bitmap_height(q->img)||
                                q->y1>=game_height-0.5*al_get_bitmap_height(q->img))q->y2=-q->y2;
                    }
                    if(q->live){
                        q->x1 += q->x2;
                        q->y1 += q->y2;
                    }
                    q=q->next;
                }
                if(p->blood!=0&&p->live&&p->level!=9){
                    p->x1 += p->x2;
                    p->y1 += p->y2;
                }
                if(p->blood!=0&&p->live&&p->level==9){
                    p->x1 += p->x2;
                    p->y1=0.3*game_height+(0.3*game_height-0.5*al_get_bitmap_height(p->img))*sin(6.28*(p->x1/game_width));
                    if(p->x1>=game_width-0.5*al_get_bitmap_width(p->img)||
                            (p->x1<=0.5*al_get_bitmap_width(p->img)&&p->x2<0))p->x2=-p->x2;
                }
                if(p->level==9)enemy_rate--;
                p=p->next;
            }
            q=my.bull;
            while(q){
                if(q->live)q->y1-=q->speed;
                q=q->next;
            }
            r=my_buff;
            while(r){
                if(r->live){
                    r->x1 += r->x2;
                    r->y1 += r->y2;
                }
                r=r->next;
            }
            img_y+= 5;//背景滚动速度
            if(img_y>game_height+0.5*al_get_bitmap_height(n.bitmap))img_y=game_height-0.5*al_get_bitmap_height(n.bitmap);

            //判断事件
            boom(n,&my,&enemy_plane,&my_buff);
            //爆炸效果
            p=enemy_plane;
            while(p){
                if(p->blood==0&&p->live){
                    if(p->form==39)al_play_sample(n.shoot,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    sprintf(num,"../UI/%d/boom_01/boom_%d.png",screen_width,p->form/10);
                    if(p->img)al_destroy_bitmap(p->img);
                    p->img=al_load_bitmap(num);
                    //al_draw_pic(p->img,p->x1,p->y1);
                    p->form--;
                    if(p->form<0){
                        if(p->level==9)score+=60;
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
            //显示
            al_draw_pic(n.bitmap,img_x,img_y);
            al_draw_pic(n.bitmap,img_x,img_y-al_get_bitmap_height(n.bitmap));
            al_draw_pic(my.img,my.x1,my.y1);
            al_draw_protect(&my);
            r=my_buff;
            while(r){
                if(r->live){
                    if(r->form<0){
                        if(r->level==1)r->form=29;
                        if(r->level==2)r->form=50;
                        if(r->level==3)r->form=59;
                        if(r->level==4)r->form=38;
                    }
                    sprintf(num,"../UI/%d/buff_%d/buff_%d.png",screen_width,r->level,r->form/3);
                    if(r->img)al_destroy_bitmap(r->img);
                    r->img=al_load_bitmap(num);
                    al_draw_pic(r->img,r->x1,r->y1);
                    r->form--;
                }
                r=r->next;
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
                if(p->live)al_draw_pic(p->img,p->x1,p->y1);
                p=p->next;
            }
            al_draw_life(n,my);
            al_flip_display();
            redraw=false;
        }
        if(my.blood<=0&&my.live)continue;
        //飞机移动
        //mouse
        if(ev.mouse.x>0&&ev.mouse.x<game_width&&ev.mouse.y>0&&ev.mouse.y<game_height){
            if(Distance(my.x1,my.y1,ev.mouse.x,ev.mouse.y)>my.size){
                float distance = pow(pow((ev.mouse.y-my.y1),2)+pow((ev.mouse.x-my.x1),2),0.5);
                float dx=my.size*(ev.mouse.x-my.x1) /distance;
                float dy=my.size*(ev.mouse.y-my.y1) /distance;
                al_set_mouse_xy(n.display,my.x1+dx,my.y1+dy);
            }
            my.x2=ev.mouse.x;
            my.y2=ev.mouse.y;
        }
        if(my.x1!=my.x2||my.y1!=my.y2){
            float distance = pow(pow((my.y2-my.y1),2)+pow((my.x2-my.x1),2),0.5);
            float dx=2*my.speed * (my.x2-my.x1) /distance;
            float dy=2*my.speed * (my.y2-my.y1) /distance;
            my.x1+=dx;
            my.y1+=dy;
        }
        //keyboard
        al_move(ev,&my,&k);
    }
    return true;
}

void boom(allegro music,plane n,plane *m,buff *b)
{
    p=*m;
    while(p){
        if(p->live&&p->level==9){
            p=p->next;
            continue;
        }
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
    r = *b;
    while(r){
        if(r->x1<-0.5*al_get_bitmap_width(r->img))r->live=false;
        else if(r->x1>game_width+0.5*al_get_bitmap_width(r->img))r->live=false;
        else if(r->y1<-0.5*al_get_bitmap_height(r->img))r->live=false;
        else if(r->y1>game_height+0.5*al_get_bitmap_height(r->img))r->live=false;
        r = r->next;
    }

    if(n->blood>0){//判断子弹是否命中
        p=*m;
        while(p){
            q=p->bull;
            while(q){
                if(q->live&&n->blood!=0){
                    if(p->live&&p->level==9&&
                            Distance(q->x1,q->y1,p->x1,p->y1)<0.4*p->size)q->live=false;
                    if(Distance(q->x1,q->y1,n->x1,n->y1)<0.5*(n->size+al_get_bitmap_width(q->img))){
                        q->live=false;
                        if(effect_protection==0){
                            n->blood--;
                            n->level=1;
                            effect_craze=0;
                            effect_speed=0;
                        }
                        else effect_protection-=10*q->attack;
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
                    if(p->live&&p->blood!=0&&q->y1>0){
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
    if(n->blood>0){
        p=*m;
        while(p){
            if(p->blood!=0&&p->live){
                if(Distance(n->x1,n->y1,p->x1,p->y1)<0.5*(p->size+n->size)){
                    if(effect_protection==0){
                        n->blood--;
                        n->level=1;
                        effect_craze=0;
                        effect_speed=0;
                    }
                    else effect_protection-=10*p->blood;
                    if(p->level!=9)p->blood=0;
                }
            }
            p=p->next;
        }
    }
    if(n->blood>0){
        r = *b;
        while(r){
            if(r->live){
                if(Distance(n->x1,n->y1,r->x1,r->y1)<0.5*(r->size+n->size)){
                    al_play_sample(music.effect,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    if(r->level==1&&n->blood<10)n->blood++;
                    if(r->level == 2)effect_protection =360;
                    if(r->level==3)effect_craze=360;
                    if(r->level==4){
                        if(n->level<3)n->level++;
                        effect_speed=360;
                    }
                    r->live = false;
                }
            }
            r = r->next;
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
    if(p1){
        bullet q1=p1->bull,q2=NULL;
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
        if(p1->bull&&!p1->bull->live){
            bullet a=p1->bull;
            p1->bull=p1->bull->next;
            free(a);
        }
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
    buff r1=*b,r2 = NULL;
    if(r1)r2=r1->next;
    while(r2){
        if(!r2->live){
            r1->next=r2->next;
            buff a=r2;
            r2=NULL;
            free(a);
        }
        r1=r1->next;
        if(!r1)break;
        r2=r1->next;
    }
    if((*b)&&!(*b)->live){
        buff a=*b;
        (*b)=(*b)->next;
        free(a);
    }
}


void al_move(ALLEGRO_EVENT ev, plane my,int *plane_num)
{
    float dx=0,dy=0;
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
    if(key_down)dy=my->speed;
    if(key_left){
        if(k>-7)k--;
        sprintf(num,"../UI/%d/plane_01/plane_%d.png",screen_width,k);
        if(my->img)al_destroy_bitmap(my->img);
        my->img=al_load_bitmap(num);
        dx=-my->speed;
    }
    else{
        if(k<0)k++;
        sprintf(num,"../UI/%d/plane_01/plane_%d.png",screen_width,k);
        if(my->img)al_destroy_bitmap(my->img);
        my->img=al_load_bitmap(num);
    }
    if(key_right){
        if(k<7)k++;
        sprintf(num,"../UI/%d/plane_01/plane_%d.png",screen_width,k);
        if(my->img)al_destroy_bitmap(my->img);
        my->img=al_load_bitmap(num);
        dx=my->speed;
    }
    else{
        if(k>0)k--;
        sprintf(num,"../UI/%d/plane_01/plane_%d.png",screen_width,k);
        if(my->img)al_destroy_bitmap(my->img);
        my->img=al_load_bitmap(num);
    }
    if(key_up)dy=-my->speed;
    if(dx&&dy){
        dx=pow(2,0.5)*dx/2;
        dy=pow(2,0.5)*dy/2;
    }
    my->x1+=dx;
    my->y1+=dy;
    if(my->x1<0.5*my->size)my->x1=0.5*my->size;
    if(my->x1>game_width-0.5*my->size)my->x1=game_width-0.5*my->size;
    if(my->y1<0.5*my->size)my->y1=0.5*my->size;
    if(my->y1>game_height-0.5*my->size)my->y1=game_height-0.5*my->size;
    my->x2=my->x1;
    my->y2=my->y1;
    *plane_num=k;
}

int Rand(int low,int high)
{
    int i=rand();
    double m=i/((double)RAND_MAX+1);
    m=m*(high-low+1)+low;
    return (int)m;
}

void al_draw_pic(ALLEGRO_BITMAP *n,float x,float y)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform,x-0.5*al_get_bitmap_width(n),y-0.5*al_get_bitmap_height(n));
    al_use_transform(&transform);
    al_draw_bitmap(n,0,0,0);
    al_identity_transform(&transform);
    al_translate_transform(&transform,0,0);
    al_use_transform(&transform);
}

float Distance(float x1, float y1, float x2, float y2)
{
    return pow(pow(x1-x2,2)+pow(y1-y2,2),0.5);
}

void al_draw_protect(plane n)
{
    if(effect_protection>0){
        ALLEGRO_BITMAP *p=NULL;
        sprintf(num,"../UI/%d/buff_0/buff_%d.png",screen_width,effect_protection%60/6);
        p=al_load_bitmap(num);
        al_draw_pic(p,n->x1,n->y1);
        effect_protection--;
        al_destroy_bitmap(p);
    }
    if(effect_craze>0){
        plane_rate+=(0.01*gate+0.07)*plane_space;
        effect_craze--;
    }
    if(effect_speed>0){
        n->speed=(gate+1)*n->speed;
        effect_speed--;
        if(effect_speed==0)n->speed=n->speed/(gate+1);
    }
}
