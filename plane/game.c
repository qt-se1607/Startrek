#include "game.h"

char num[MAXSIZE];

bool again = false;
bool save = false;
bool set_back = false;

bool al_start_game(allegro n)
{
    ALLEGRO_BITMAP *p=NULL,*q=NULL;
    bool redraw=false;
    int i=85,bg_num=0,time_num=3;
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)redraw=true;
        if(redraw&&al_is_event_queue_empty(n.event_queue)){
            if(i==120){
                al_clear_to_color(black);
                sprintf(num,"%d",time_num--);
                al_draw_text(n.font2,white,0.5*game_width,0.5*game_height-2*word_size,ALLEGRO_ALIGN_CENTER,num);
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

void pause_game(allegro n)
{


    bool redraw = false;

    int checkout = 0.3 * 120;
    int git = 3*checkout;

    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
            break;
        if(redraw && al_is_event_queue_empty(n.event_queue))
        {
            al_draw_display(n);
            redraw = false;
        }

        again = false;
        save = false;
        set_back = false;

        if(git>=3*checkout)
        {
            again=true;
            save = false;
            set_back = false;
        }
        else if(git>=2*checkout)
        {
            save=true;
            again = false;
            set_back =  false;
        }
        else if(git>=checkout)
        {
            set_back=true;
            again = false;
            save = false;
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


        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        if(judge_in(ev,0.4*game_width,0.3*game_height-0.2*word_size,
                    0.6*game_width,0.3*game_height+0.8*word_size)){
            git=3*checkout;
            al_draw_display(n);
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                break;
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                break;
        }

        if(judge_in(ev,0.4*game_width,0.5*game_height-0.2*word_size,
                    0.6*game_width,0.5*game_height+0.8*word_size)){
            git=2*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_display(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                exit(0);
        }
        if(judge_in(ev,0.4*game_width,0.7*game_height-0.2*word_size,
                    0.6*game_width,0.7*game_height+0.8*word_size)){
            git = checkout;
            al_draw_display(n);
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_display(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                exit(-1);
        }


    }

}


void al_draw_display(allegro n)
{

    if(again)
    {
        al_draw_filled_rounded_rectangle(0.4*screen_width,0.3*screen_height-0.2*word_size,
                                         0.6*screen_width,0.3*screen_height+0.8*word_size,
                                         0.2*word_size,0.2*word_size,al_map_rgb(64,224,205));
    }

    else{
        al_draw_filled_rounded_rectangle(0.4*screen_width,0.3*screen_height-0.2*word_size,
                                         0.6*screen_width,0.3*screen_height+0.8*word_size,
                                         0.2*word_size,0.2*word_size,al_map_rgb(0,0,0));
    }

    al_draw_text(n.font1, al_map_rgb(255,255,255), 0.5 * game_width,0.3*game_height,ALLEGRO_ALIGN_CENTRE, "继 续 游 戏");

    if(save)
    {
        al_draw_filled_rounded_rectangle(0.4*game_width,0.5*game_height-0.2*word_size,
                                         0.6*game_width,0.5*game_height+0.8*word_size,
                                         0.2*word_size,0.2*word_size,al_map_rgb(64,224,205));
    }

    else
    {
        al_draw_filled_rounded_rectangle(0.4*game_width,0.5*game_height-0.2*word_size,
                                         0.6*game_width,0.5*game_height+0.8*word_size,
                                         0.2*word_size,0.2*word_size,al_map_rgb(0,0,0));
    }

    al_draw_text(n.font1, al_map_rgb(255,255,255), 0.5 * game_width, 0.5*game_height,ALLEGRO_ALIGN_CENTRE, "存       档");

    if(set_back)
    {
        al_draw_filled_rounded_rectangle(0.4*game_width,0.7*game_height-0.2*word_size,
                                         0.6*game_width,0.7*game_height+0.8*word_size,
                                                 0.2*word_size,0.2*word_size,al_map_rgb(64,224,205));
    }
    else
    {
        al_draw_filled_rounded_rectangle(0.4*game_width,0.7*game_height-0.2*word_size,
                                         0.6*game_width,0.7*game_height+0.8*word_size,
                                                 0.2*word_size,0.2*word_size,al_map_rgb(0,0,0));
    }

    al_draw_text(n.font1,al_map_rgb(255,255,255),0.5*game_width,0.7*game_height,ALLEGRO_ALIGN_CENTER,"退 出 游 戏");

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
