#include "game.h"

bool al_start_game(allegro n)
{
    ALLEGRO_BITMAP *p=NULL,*q=NULL;
    bool redraw=false;
    int i=85,bg_num=0,time_num=3;
    char num[255];
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)redraw=true;
        if(i==120){
            al_clear_to_color(black);
            sprintf(num,"%d",time_num--);
            al_draw_text(n.font2,white,0.5*game_width,0.5*game_height-2*word_size,ALLEGRO_ALIGN_CENTER,num);
            i=0;
            bg_num=0;
        }
        i++;
        if(redraw&&!al_is_event_queue_empty(n.event_queue)){
            al_flip_display();
            redraw=false;
        }
        if(i>85){
            if(time_num<=0)break;
            al_clear_to_color(black);
            bg_num++;
            if(bg_num>35)continue;
            sprintf(num,"../startrek/UI/photo/bg2/bg_%d.png",bg_num/6+1);
            if(p)al_destroy_bitmap(p);
            p=al_load_bitmap(num);
            sprintf(num,"../startrek/UI/photo/bg2/bg_%d.png",-(bg_num/6+1));
            if(q)al_destroy_bitmap(q);
            q=al_load_bitmap(num);
            al_draw_pic(p,0.5*(game_width-al_get_bitmap_width(p)),0.5*game_height);
            al_draw_pic(q,0.5*(game_width+al_get_bitmap_width(q)),0.5*game_height);
        }
    }
    al_destroy_bitmap(p);
    return true;
}

bool al_join_game(allegro n)
{
    Draw_plane_bullet(n);
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
