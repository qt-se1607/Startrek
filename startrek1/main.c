#include "game.h"
//const int FPS = 120;

int main()
{
    allegro n;
    Init_Allegro();
//    al_get_display_mode(0,&n.display_date);
//    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
//    n.display=al_create_display(n.display_date.width,n.display_date.height);

    Init_Display(&n);
    Init_Queue(&n);
    al_start_timer(n.timer);
    while(1){
        al_start_game(&n);
        al_join_game(&n);
        if(al_end_game(&n))
            break;
    }
    Destroy_Allegro(&n);
    return 0;
}
