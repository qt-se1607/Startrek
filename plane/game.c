#include "game.h"

char num[MAXSIZE];
bool again = false;
bool save = false;
bool set_back = false;

bool al_start_game(allegro n)
{
    al_stop_timer(n.timer);
    ALLEGRO_BITMAP *p=NULL,*q=NULL;
    ALLEGRO_SAMPLE *music=NULL;
    music=al_load_sample("../UI/music/time.wav");
    bool redraw=false;
    int i=85,bg_num=0,time_num=3;
    al_start_timer(n.timer);
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)redraw=true;
        if(redraw&&al_is_event_queue_empty(n.event_queue)){
            if(i==120){
                al_clear_to_color(black);
                sprintf(num,"%d",time_num--);
                al_draw_text(n.font2,white,0.5*game_width,0.5*game_height-150,ALLEGRO_ALIGN_CENTER,num);
                al_play_sample(music,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                i=0;
                bg_num=0;
            }
            i++;
            if(i>85){
                if(time_num<=0)break;
                al_clear_to_color(black);
                bg_num++;
                if(bg_num>35)continue;
                sprintf(num,"../UI/photo/bg2/bg_%d.png",bg_num/6+1);
                if(p)al_destroy_bitmap(p);
                p=al_load_bitmap(num);
                sprintf(num,"../UI/photo/bg2/bg_%d.png",-(bg_num/6+1));
                if(q)al_destroy_bitmap(q);
                q=al_load_bitmap(num);
                al_draw_pic(p,0.5*(game_width-al_get_bitmap_width(p)),0.5*game_height);
                al_draw_pic(q,0.5*(game_width+al_get_bitmap_width(q)),0.5*game_height);
            }
            al_flip_display();
            redraw=false;
        }
    }
    al_destroy_sample(music);
    al_destroy_bitmap(p);
    return true;
}

bool al_join_game(allegro n,int file_num)
{
    Draw_plane_bullet(n,file_num);
    return true;
}

bool al_end_game(allegro n)
{
    ALLEGRO_EVENT ev;
    al_wait_for_event(n.event_queue,&ev);

    if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE||ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return true;
    return false;
}

void al_pause(allegro n,plane my,plane enemy,buff my_buff)
{
    al_stop_samples();
    al_stop_timer(n.timer);
    int checkout = 0.3 *FPS;
    int git = 3*checkout;
    bool redraw=false;
    al_start_timer(n.timer);
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)redraw=true;
        if(redraw && al_is_event_queue_empty(n.event_queue)){
            al_draw_pauseboard(n);
            redraw = false;
        }
        if(git>=3*checkout){
            again=true;
            save =false;
            set_back =false;
        }
        else if(git>=2*checkout){
            save=true;
            again =false;
            set_back =false;
        }
        else if(git>=checkout){
            set_back=true;
            again=false;
            save=false;
        }
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_UP:key_up=true;break;
            case ALLEGRO_KEY_DOWN:key_down=true;break;
            }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_UP){
            int i=git%checkout;
            if(key_down)git-=i;
            if(key_up)git=git-i+checkout;
            if(git>=4*checkout)git=checkout;
            switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_UP:key_up=false;break;
            case ALLEGRO_KEY_DOWN:key_down=false;break;
            }
        }
        if(key_down)git--;
        if(key_up)git++;
        if(git<checkout)git=4*checkout;
        if(git>4*checkout)git=checkout;

        if(ev.type==ALLEGRO_EVENT_KEY_DOWN&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER){
            if(again)break;
            if(save){
                al_archive(my,enemy,my_buff);
                p=enemy;
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
                q=my->bull;
                while(q){
                    bullet a=q;
                    q=q->next;
                    free(a);
                }
                r=my_buff;
                while(r){
                    buff a=r;
                    r=r->next;
                    free(a);
                }
                exit(9);
            }
            if(set_back){
                p=enemy;
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
                q=my->bull;
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
                exit(0);
            }
        }
        if(judge_in(ev,0.4*game_width,0.3*game_height-0.6*word_size,0.6*game_width,0.4*game_height+0.6*word_size)){
            git=3*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_pauseboard(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)break;
        }
        if(judge_in(ev,0.4*game_width,0.5*game_height-0.6*word_size,0.6*game_width,0.5*game_height+0.6*word_size)){
            git=2*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_pauseboard(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                al_archive(my,enemy,my_buff);
                p=enemy;
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
                q=my->bull;
                while(q){
                    bullet a=q;
                    q=q->next;
                    free(a);
                }
                r=my_buff;
                while(r){
                    buff a=r;
                    r=r->next;
                    free(a);
                }
                exit(9);
            }
        }
        if(judge_in(ev,0.4*game_width,0.7*game_height-0.6*word_size,0.6*game_width,0.7*game_height+0.6*word_size)){
            git = checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_pauseboard(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                p=enemy;
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
                q=my->bull;
                while(q){
                    bullet a=q;
                    q=q->next;
                    free(a);
                }
                r=my_buff;
                while(r){
                    buff a=r;
                    r=r->next;
                    free(a);
                }
                exit(0);
            }
        }
    }
    al_play_sample(n.bg,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
}

void al_archive(plane n, plane m,buff my_buff)
{
    int fp;
    float i=0;
    int g=0;
    fp=open("../UI/load/load",O_CREAT|O_WRONLY);
    write(fp,&score,sizeof(int));
    write(fp,&gate,sizeof(int));
    write(fp,&effect_protection,sizeof(int));
    write(fp,&effect_craze,sizeof(int));
    write(fp,&effect_speed,sizeof(int));
    write(fp,&plane_rate,sizeof(int));
    write(fp,&enemy_rate,sizeof(int));
    write(fp,&bullet_rate,sizeof(int));
    write(fp,&buff_rate,sizeof(int));
    i=n->x1/game_width;
    write(fp,&i,sizeof(float));
    i=n->y1/game_height;
    write(fp,&i,sizeof(float));
    write(fp,&n->x2,sizeof(float));
    write(fp,&n->y2,sizeof(float));
    write(fp,&n->speed,sizeof(float));
    write(fp,&n->level,sizeof(int));
    write(fp,&n->blood,sizeof(int));
    write(fp,&n->form,sizeof(int));
    write(fp,&n->live,sizeof(bool));
    q=n->bull;
    g=0;
    while(q){
        g++;
        q=q->next;
    }
    write(fp,&g,sizeof(int));
    q=n->bull;
    while(q){
        i=q->x1/game_width;
        write(fp,&i,sizeof(float));
        i=q->y1/game_height;
        write(fp,&i,sizeof(float));
        write(fp,&q->x2,sizeof(float));
        write(fp,&q->y2,sizeof(float));
        write(fp,&q->speed,sizeof(float));
        write(fp,&q->attack,sizeof(int));
        write(fp,&q->form,sizeof(int));
        write(fp,&q->live,sizeof(bool));
        q=q->next;
    }
    p=m;
    g=0;
    while(p){
        g++;
        p=p->next;
    }
    write(fp,&g,sizeof(int));
    p=m;
    while(p){
        i=p->x1/game_width;
        write(fp,&i,sizeof(float));
        i=p->y1/game_height;
        write(fp,&i,sizeof(float));
        i=p->x2/p->speed;
        write(fp,&i,sizeof(float));
        i=p->y2/p->speed;
        write(fp,&i,sizeof(float));
        write(fp,&p->level,sizeof(int));
        write(fp,&p->blood,sizeof(int));
        write(fp,&p->form,sizeof(int));
        write(fp,&p->live,sizeof(bool));
        q=p->bull;
        g=0;
        while(q){
            g++;
            q=q->next;
        }
        write(fp,&g,sizeof(int));
        q=p->bull;
        while(q){
            i=q->x1/game_width;
            write(fp,&i,sizeof(float));
            i=q->y1/game_height;
            write(fp,&i,sizeof(float));
            write(fp,&q->x2,sizeof(float));
            write(fp,&q->y2,sizeof(float));
            write(fp,&q->speed,sizeof(float));
            write(fp,&q->attack,sizeof(int));
            write(fp,&p->level,sizeof(int));
            write(fp,&q->live,sizeof(bool));
            q=q->next;
        }
        p=p->next;
    }
    r=my_buff;
    g=0;
    while(r){
        r=r->next;
        g++;
    }
    write(fp,&g,sizeof(int));
    r=my_buff;
    while(r){
        i=r->x1/game_width;
        write(fp,&i,sizeof(float));
        i=r->y1/game_height;
        write(fp,&i,sizeof(float));
        write(fp,&r->x2,sizeof(float));
        write(fp,&r->y2,sizeof(float));
        write(fp,&r->speed,sizeof(float));
        write(fp,&r->level,sizeof(int));
        write(fp,&r->form,sizeof(int));
        write(fp,&r->live,sizeof(bool));
        r=r->next;
    }
    close(fp);
}

void al_draw_pauseboard(allegro n)
{
    al_clear_to_color(black);
    if(again){
        al_draw_filled_rounded_rectangle(0.5*game_width-3*word_size,0.3*game_height-0.6*word_size,
                                         0.5*game_width+3*word_size,0.3*game_height+0.6*word_size,
                                         0.2*word_size,0.2*word_size,green_cyan);
    }
    else{
        al_draw_filled_rounded_rectangle(0.4*game_width,0.3*game_height-0.6*word_size,
                                         0.6*game_width,0.3*game_height+0.6*word_size,
                                         0.2*word_size,0.2*word_size,black);
    }
    al_draw_text(n.font1,white,0.5*game_width,0.3*game_height-0.6*word_size,ALLEGRO_ALIGN_CENTRE,"继 续 游 戏");
    if(save){
        al_draw_filled_rounded_rectangle(0.4*game_width-1*word_size,0.5*game_height-0.6*word_size,
                                         0.6*game_width+1*word_size,0.5*game_height+0.6*word_size,
                                         0.2*word_size,0.2*word_size,green_cyan);
    }
    else{
        al_draw_filled_rounded_rectangle(0.4*game_width,0.5*game_height-0.6*word_size,
                                         0.6*game_width,0.5*game_height+0.6*word_size,
                                         0.2*word_size,0.2*word_size,black);
    }
    al_draw_text(n.font1,white,0.5*game_width,0.5*game_height-0.6*word_size,ALLEGRO_ALIGN_CENTRE,"存      档");
    if(set_back){
        al_draw_filled_rounded_rectangle(0.4*game_width-1*word_size,0.7*game_height-0.6*word_size,
                                         0.6*game_width+1*word_size,0.7*game_height+0.6*word_size,
                                         0.2*word_size,0.2*word_size,green_cyan);
    }
    else{
        al_draw_filled_rounded_rectangle(0.4*game_width,0.7*game_height-0.6*word_size,
                                         0.6*game_width,0.7*game_height+0.6*word_size,
                                         0.2*word_size,0.2*word_size,black);
    }
    al_draw_text(n.font1,white,0.5*game_width,0.7*game_height-0.6*word_size,ALLEGRO_ALIGN_CENTER,"退 出 游 戏");
    al_flip_display();
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

void al_draw_life(allegro n,Plane m)
{
    ALLEGRO_BITMAP *life = NULL;
    sprintf(num,"../UI/%d/life/life.png",screen_width);
    life = al_load_bitmap(num);
    for(int i = 0;i<m.blood;i++)
        al_draw_pic(life,al_get_bitmap_width(life)*(i%5+1),al_get_bitmap_height(life)*(i/5+1));
    sprintf(num,"%10d",score);
    al_draw_text(n.font1,white,al_get_bitmap_width(life)*5,al_get_bitmap_height(life)*3,ALLEGRO_ALIGN_RIGHT,num);
    al_destroy_bitmap(life);
}
