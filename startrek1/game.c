#include "game.h"

bool al_start_game(allegro *n)
{
            al_flip_display();
            al_clear_to_color(black);
            al_draw_text(n->font2,white,0.5*screen_width,0.5*screen_height-2*word_size,ALLEGRO_ALIGN_CENTER,"3");
            al_flip_display();
            al_rest(1);
            al_clear_to_color(black);
            al_draw_text(n->font2,white,0.5*screen_width,0.5*screen_height-2*word_size,ALLEGRO_ALIGN_CENTER,"2");
            al_flip_display();
            al_rest(1);
            al_clear_to_color(black);
            al_draw_text(n->font2,white,0.5*screen_width,0.5*screen_height-2*word_size,ALLEGRO_ALIGN_CENTER,"1");
            al_flip_display();
            al_rest(1);
    return true;
}

bool al_join_game(allegro *n)
{
    Draw_plane_bullet(n);
    return true;
}

bool al_end_game(allegro *n)
{
    ALLEGRO_EVENT ev;
    al_wait_for_event(n->event_queue,&ev);

    if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE||ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return true;
    return false;
}
