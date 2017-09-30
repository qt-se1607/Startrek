#include"Allegro.h"
int main()
{
    allegro n;
    Init_Allegro(n);
    al_get_display_mode(0,&n.display_date);
    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    n.display=al_create_display(n.display_date.width,n.display_date.height);
    if(!n.display){
        fprintf(stderr, "failed to create display!\n");
        exit(1);
    }
    n.event_queue=al_create_event_queue();
    if(!n.event_queue){
        fprintf(stderr, "failed to create event_queue!\n");
        exit(1);
    }
    n.timer=al_create_timer(1.0/FPS);
    if(!n.timer){
        fprintf(stderr, "failed to create timer!\n");
        exit(1);
    }
    n.bitmap=al_load_bitmap("../startrek/img1.jpg");
    if(!n.bitmap){
        fprintf(stderr, "failed to create bitmap!\n");
        exit(1);
    }
    n.font1=al_load_ttf_font("../startrek/a.ttf",word_size,128);
    if(!n.font1){
        fprintf(stderr, "failed to create font1!\n");
        exit(1);
    }
    n.font2=al_load_ttf_font("../startrek/a.ttf",4*word_size,128);
    if(!n.font2){
        fprintf(stderr, "failed to create font2!\n");
        exit(1);
    }
    Init_Display(n);
    Init_Queue(n);
    al_start_timer(n.timer);
    while(1){
        if(al_start_game(n)){
            if(al_join_game(n))al_end_game(n);
        }
        else{
            Destroy_Allegro(n);
            break;
        }
    }
}
