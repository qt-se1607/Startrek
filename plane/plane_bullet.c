#include "plane_bullet.h"
#include"game.h"

int plane_space = 0;//飞机出现jian ge
int bullet_space = 0;//子弹出现时间
bool key_up=false;
bool key_down=false;
bool key_left=false;
bool key_right=false;
int score=0;
bool effect = false;
int effect_time = 0;

void Init_Plane(plane *n,int file_num)
{
    float k=0;
    if(file_num){
        read(file_num,&k,sizeof(float));
        n->x1=k*game_width;
        read(file_num,&k,sizeof(float));
        n->y1=k*game_height;
        read(file_num,&n->x2,sizeof(int));
        read(file_num,&n->y2,sizeof(int));
        read(file_num,&n->level,sizeof(int));
        read(file_num,&n->speed,sizeof(int));
        read(file_num,&n->blood,sizeof(int));
        read(file_num,&n->form,sizeof(int));
        read(file_num,&n->size,sizeof(int));
        read(file_num,&n->bullet_num,sizeof(int));
        read(file_num,&n->live,sizeof(bool));
        n->img =al_load_bitmap("../UI/plane_01/plane_0.png");
    }
    else{
        n->level = 1;
        n->blood = 10;
        n->live = true;
        sprintf(num,"../UI/plane_01/plane_0.png");
        n->img=al_load_bitmap(num);
        n->size = 0.9*al_get_bitmap_width(n->img);
        n->x1 = 0.5 * game_width - n->size;
        n->y1 = game_height - n->size;
        n->bullet_num = 0;
        n->x2 = 0;
        n->y2 = 0;
    }
    Init_Bullet(n->bull,file_num);
}
void Init_Bullet(bullet n[MAXSIZE],int file_num)
{
    float k=0;
    if(file_num){
        for(int i = 0;i < MAXSIZE;i++){
            n[i].img=al_load_bitmap("../UI/bullet_01/bullet_0.png");
            read(file_num,&k,sizeof(float));
            n[i].x1=k*game_width;
            read(file_num,&k,sizeof(float));
            n[i].y1=k*game_height;
            read(file_num,&n[i].x2,sizeof(int));
            read(file_num,&n[i].y2,sizeof(int));
            read(file_num,&n[i].speed,sizeof(int));
            read(file_num,&n[i].attack,sizeof(int));
            read(file_num,&n[i].form,sizeof(int));
            read(file_num,&n[i].live,sizeof(bool));
        }
    }
    else{
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
}
void Init_enemyplane(plane n[MAXSIZE],int file_num)
{
    float k=0;
    if(file_num){
        for(int i = 0; i < MAXSIZE;i++){
            read(file_num,&k,sizeof(float));
            n[i].x1=k*game_width;
            read(file_num,&k,sizeof(float));
            n[i].y1=k*game_height;
            read(file_num,&n[i].x2,sizeof(int));
            read(file_num,&n[i].y2,sizeof(int));
            read(file_num,&n[i].level,sizeof(int));
            read(file_num,&n[i].speed,sizeof(int));
            read(file_num,&n[i].blood,sizeof(int));
            read(file_num,&n[i].form,sizeof(int));
            read(file_num,&n[i].size,sizeof(int));
            read(file_num,&n[i].bullet_num,sizeof(int));
            read(file_num,&n[i].live,sizeof(bool));
            n[i].img=al_load_bitmap("../UI/enemy/enemy1.png");
            Init_Bullet(n[i].bull,file_num);
        }
    }
    else{
        for(int i = 0; i < MAXSIZE;i++){
            n[i].live = false;
            n[i].img = NULL;
            n[i].bullet_num = 0;
            n[i].blood = 0;
            n[i].level = 0;
            n[i].x1 = 0;
            n[i].y1 = 0;
            n[i].x2 = 0;
            n[i].y2 = 0;
            Init_Bullet(n[i].bull,file_num);
        }
    }
}
void Init_buff(bullet buff[MAXSIZE])
{
    for(int i = 0;i < MAXSIZE;i++){
        buff[i].attack = 0;
        buff[i].img = NULL;
        buff[i].live = false;
        buff[i].form = 0;
        buff[i].x1 = 0;
        buff[i].y1 = 0;
        buff[i].x2 = 0;
        buff[i].y2 = 0;
        buff[i].speed = 0;
    }
}

bool Draw_plane_bullet(allegro m,int file_num)
{
    int k=0;
    img_x=0.5*game_width;
    img_y=game_height-0.5*al_get_bitmap_height(m.bitmap);
    plane n;
    plane enemy_plane[MAXSIZE];
    bullet buff[MAXSIZE];

    if(file_num)read(file_num,&score,sizeof(int));
    Init_Plane(&n,file_num);
    Init_enemyplane(enemy_plane,file_num);
    Init_buff(buff);
    int buff_space;
    int plane_num = 0;
    int bullet_num = 0;
    int plane_rate = 0;
    int buff_rate = 0;
    int buff_num = 0;
    bool redraw = false;
    //al_set_mouse_xy(m.display,0.5*game_width,game_height+1);
    while(1){
        if(!n.live)exit(score);
        n.speed = n.level;
        plane_space = game_height / (5 + 2 * n.level);
        bullet_space = game_height / (5 + 2 * n.level);
        buff_space = 500;
        ALLEGRO_EVENT ev;
        al_wait_for_event(m.event_queue,&ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)redraw = true;
        if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE){
            al_pause(m,n,enemy_plane);
        }
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

            //join buff;
            if(buff_rate >= buff_space){
                buff[buff_num].attack = Rand(1,2);
                if(buff[buff_num].attack == 1)buff[buff_num].form = 2;
                if(buff[buff_num].attack == 2)buff[buff_num].form = 50;
                buff[buff_num].live = true;
                printf("aaa\n");
                sprintf(num,"../UI/buff_%d/buff_0.png",buff[buff_num].attack);
                buff[buff_num].img = al_load_bitmap(num);
                buff[buff_num].size = al_get_bitmap_width(buff[buff_num].img);
                buff[buff_num].x1 = Rand(buff[buff_num].size,game_width-buff[buff_num].size);
                buff[buff_num].y1 = -0.5 * buff[buff_num].size;
                printf("%d---------%d\n",buff[buff_num].attack,buff[buff_num].x1);
                buff[buff_num].speed = 1;
                buff[buff_num].x2 = 0;
                buff[buff_num].y2 = buff[buff_num].speed;
                buff_num++;
                if(buff_num >= MAXSIZE){
                    buff_num = 0;
                }
                buff_rate = 0;
            }
            buff_rate++;

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

            for(int i = 0;i<MAXSIZE;i++)
            {
                buff[i].x1 += buff[i].x2;
                buff[i].y1 += buff[i].y2;
            }

            img_y += 5;//背景滚动速度
            if(img_y>game_height+0.5*al_get_bitmap_height(m.bitmap))img_y=game_height-0.5*al_get_bitmap_height(m.bitmap);

            //判断事件
            if(effect){
                effect_time+=5;
                if(effect_time>=800){
                    effect_time = 0;
                    effect = false;
                }
            }
            boom(&n,enemy_plane,buff);

            //显示
            al_draw_pic(m.bitmap,img_x,img_y);
            al_draw_pic(m.bitmap,img_x,img_y-al_get_bitmap_height(m.bitmap));
            al_draw_pic(n.img,n.x1,n.y1);
            al_draw_life(n);

            for(int i=0;i<MAXSIZE;i++){
                if(!buff[i].live)continue;
                buff[i].form--;
                if(buff[i].form<0){
                    if(buff[i].attack==1)buff[i].form=2;
                    if(buff[i].attack==2)buff[i].form=50;
                }
                sprintf(num,"../UI/buff_%d/buff_%d.png",buff[i].attack,buff[i].form/3);
                buff[i].img = al_load_bitmap(num);
                al_draw_pic(buff[i].img,buff[i].x1,buff[i].y1);

            }

            sprintf(num,"%4d",score);
            al_draw_text(m.font1,white,0.05*game_width,
                         0.02*game_height,ALLEGRO_ALIGN_CENTER,num);
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
                        score += 10;
                    }
                }
            }
            if(n.blood<=0&&n.live){
                sprintf(num,"../UI/boom_01/boom_%d.png",n.form/10);
                if(n.img)al_destroy_bitmap(n.img);
                n.img=al_load_bitmap(num);
                al_draw_pic(n.img,n.x1,n.y1);
                n.form--;
                if(n.form<=0){
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

void boom(plane *n,plane *m,bullet *buff)
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

        if(!buff[a].live)continue;//判断buff是否出界
        if(buff[a].x1<-0.5*al_get_bitmap_width(buff[a].img))buff[a].live=false;
        else if(buff[a].x1>game_width
                +0.5*al_get_bitmap_width(buff[a].img))buff[a].live=false;
        else if(buff[a].y1<-0.5*al_get_bitmap_height(buff[a].img))buff[a].live=false;
        else if(buff[a].y1>game_height
                +0.5*al_get_bitmap_height(buff[a].img))buff[a].live=false;
    }
    for(int a=0;a>MAXSIZE;a++){
        if(!n->bull[a].live)continue;
        if(n->bull[a].x1<-0.5*al_get_bitmap_width(n->bull[a].img))n->bull[a].live=false;
        else if(n->bull[a].x1>game_width+0.5*al_get_bitmap_width(n->bull[a].img))n->bull[a].live=false;
        else if(n->bull[a].y1<-0.5*al_get_bitmap_height(n->bull[a].img))n->bull[a].live=false;
        else if(n->bull[a].y1>game_height+0.5*al_get_bitmap_height(n->bull[a].img))n->bull[a].live=false;
    }
    if(n->blood>0 && !effect){//判断子弹是否命中
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
    if(n->blood>0 && !effect){
        for(int a=0;a<MAXSIZE;a++){
            if(!m[a].live)continue;
            if(Distance(n->x1,n->y1,m[a].x1,m[a].y1)<0.5*(m[a].size+n->size)){
                n->blood--;
                m[a].blood=0;
            }
        }
    }
    if(n->blood>0){
        for(int a = 0;a < MAXSIZE;a++){
            if(!buff[a].live)continue;
            if(Distance(n->x1,n->y1,buff[a].x1,buff[a].y1)<0.5*(buff[a].size+n->size)){
                if(buff[a].attack == 1){
                    n->blood++;
                }
                if(buff[a].attack == 2){
                    effect = true;
                }
                buff[a].live = false;
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


