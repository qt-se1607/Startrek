#include "game.h"

bool screenflag = false;//全屏标志
float volume_num = 100.0;

int main(int argc,char *argv[])
{
    sscanf(argv[0],"%d",&screenflag);
    sscanf(argv[1],"%d",&screen_width);
    sscanf(argv[2],"%d",&screen_height);
    sscanf(argv[3],"%f",&volume_num);
    srand((int)time(NULL));
    allegro n;
    Init_Allegro();
    if(screenflag)
        al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    Init_Display(&n);
    Init_Queue(&n);

    char num[MAXSIZE];
    sprintf(num,"plane/bg_%d.jpg",screen_width);
    n.bitmap=al_load_bitmap(num);
    if(!n.bitmap){
        fprintf(stderr, "failed to create bitmap!\n");
        exit(1);
    }
    n.font1=al_load_ttf_font("a.ttf",word_size,128);
    if(!n.font1){
        fprintf(stderr, "failed to create font1!\n");
        exit(1);
    }
    n.font2=al_load_ttf_font("a.ttf",4*word_size,128);
    if(!n.font2){
        fprintf(stderr, "failed to create font2!\n");
        exit(1);
    }
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
