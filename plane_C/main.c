#include "game.h"

bool screenflag = false;//全屏标志
float volume_num = 100.0;
int file_num=0;

int main(int argc,char *argv[])
{
    sscanf(argv[0],"%d",&screenflag);
    sscanf(argv[1],"%d",&screen_width);
    sscanf(argv[2],"%d",&screen_height);
    sscanf(argv[3],"%f",&volume_num);
    if(argv[4])sscanf(argv[4],"%d",&file_num);
    /*screenflag=false;
    screen_width=1600;
    screen_height=900;
    volume_num=0;
    file_num=open("../UI/load/archive_1",O_RDONLY);*/
    srand((int)time(NULL));
    allegro n;
    Init_Allegro();
    Init_Display(&n);
    Init_Queue(&n);
    n.bitmap=al_load_bitmap(num);
    if(!n.bitmap){
        fprintf(stderr, "failed to create bitmap!\n");
        exit(1);
    }
    n.font1=al_load_ttf_font("../UI/a.ttf",word_size,128);
    if(!n.font1){
        fprintf(stderr, "failed to create font1!\n");
        exit(1);
    }
    n.font2=al_load_ttf_font("../UI/a.ttf",305,0);
    if(!n.font2){
        fprintf(stderr, "failed to create font2!\n");
        exit(1);
    }
    n.bg=al_load_sample("../UI/music/gamebg0.wav");
    if(!n.bg){
        fprintf(stderr, "failed to create bg!\n");
        exit(1);
    }
    n.shoot=al_load_sample("../UI/music/shoot.wav");
    if(!n.shoot){
        fprintf(stderr, "failed to create shoot!\n");
        exit(1);
    }
    n.effect=al_load_sample("../UI/music/effect.wav");
    if(!n.effect){
        fprintf(stderr, "failed to create effect!\n");
        exit(1);
    }
    n.biu=al_load_sample("../UI/music/touch.wav");
    if(!n.biu){
        fprintf(stderr, "failed to create biu!\n");
        exit(1);
    }
    al_start_timer(n.timer);
    if(al_start_game(n)){
        if(al_join_game(n,file_num)){
            al_end_game(n);
        }
    }
    Destroy_Allegro(&n);
    return 0;
}
