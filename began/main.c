#include "variate.h"
int main()
{
    allegro n;
    Init_Allegro(&n);
    game_width =960;
    game_height =640;
    Init_Display(&n);
    n.bitmap1 = al_load_bitmap("../UI/welcome/bg.jpg");
    n.bitmap2 = al_load_bitmap("../UI/setting/bg.jpg");
    n.bitmap3 = al_load_bitmap("../UI/list/bg.jpg");
    n.bitmap4=al_load_bitmap("../UI/load/bg.jpg");
    n.sample1=al_load_sample("../UI/music/music1.wav");
    n.sample2=al_load_sample("../UI/music/music2.wav");
    bool event_timer = false;
    int checkout = 0.3*FPS;
    int git = checkout;
    int fp;
    if((fp=open("../UI/setting/setting",O_RDONLY))==-1){
        if((fp=open("../UI/setting/setting_R",O_RDONLY))==-1){
            screenflag=false;
            musicflag=true;
            volume_num=50.0;
            number=1;
            fp=open("../UI/setting/setting_R",O_CREAT|O_WRONLY);
            write(fp,&screenflag,sizeof(bool));
            write(fp,&number,sizeof(int));
            write(fp,&musicflag,sizeof(bool));
            write(fp,&volume_num,sizeof(int));
            close(fp);
            fp=open("../UI/setting/setting",O_CREAT|O_WRONLY);
            write(fp,&screenflag,sizeof(bool));
            write(fp,&number,sizeof(int));
            write(fp,&musicflag,sizeof(bool));
            write(fp,&volume_num,sizeof(int));
            close(fp);
            fp=open("../UI/setting/setting",O_RDONLY);
        }
    }
    read(fp,&screenflag,sizeof(bool));
    read(fp,&number,sizeof(int));
    read(fp,&musicflag,sizeof(bool));
    read(fp,&volume_num,sizeof(int));
    close(fp);
    if(number==1){
        img_x=1920;
        img_y=1080;
    }
    if(number==2){
        img_x=1600;
        img_y=900;
    }
    if(number==3){
        img_x=1280;
        img_y=720;
    }
    if(number==4){
        img_x=1024;
        img_y=576;
    }
    start=true;
    if(musicflag)al_play_sample(n.sample2,volume_num/100.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    al_start_timer(n.timer);
    char string[MAXSIZE];
    int p=2;
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.timer.type == ALLEGRO_EVENT_TIMER)event_timer = true;
        if(event_timer && al_is_event_queue_empty(n.event_queue)){
            al_clear_to_color(black);
            al_destroy_bitmap(n.bitmap1);
            sprintf(string,"../UI/photo/bg3/bg_%d.png",p/2);
            n.bitmap1=al_load_bitmap(string);
            p++;
            if(p>101)p=2;
            al_draw_startboard(n);
            event_timer=false;
        }
        if(git>=5*checkout){
            if(!quit&&musicflag)al_play_sample(n.sample1,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            quit=true;
            setting=false;
            load=false;
            list=false;
            start=false;
        }
        else if(git>=4*checkout){
            if(!setting&&musicflag)al_play_sample(n.sample1,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            setting=true;
            quit=false;
            load=false;
            list=false;
            start=false;
        }
        else if(git>=3*checkout){
            if(!list&&musicflag)al_play_sample(n.sample1,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            list=true;
            quit=false;
            setting=false;
            load=false;
            start=false;
        }
        else if(git>=2*checkout){
            if(!load&&musicflag)al_play_sample(n.sample1,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            load=true;
            quit=false;
            setting=false;
            list=false;
            start=false;
        }
        else if(git>=checkout){
            if(!start&&musicflag)al_play_sample(n.sample1,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            start=true;
            quit=false;
            setting=false;
            load=false;
            list=false;
        }
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_UP:key_up=true;break;
            case ALLEGRO_KEY_DOWN:key_down=true;break;
            }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_UP){
            int i=git%checkout;
            if(key_down)git=git-i+checkout;
            if(key_up)git-=i;
            if(git>=6*checkout)git=checkout;
            switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_UP:key_up=false;break;
            case ALLEGRO_KEY_DOWN:key_down=false;break;
            }
        }
        if(key_down)git++;
        if(key_up)git--;
        if(git<checkout)git=6*checkout;
        if(git>6*checkout)git=checkout;
        if(ev.type==ALLEGRO_EVENT_KEY_DOWN&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER){
            if(start){
                al_start(n);
                al_flip_display();
                n.sample2=al_load_sample("../UI/music/music2.wav");
                if(musicflag)al_play_sample(n.sample2,volume_num/100.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                else al_play_sample(n.sample2,0.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
            }
            else if(load){
                al_load(n,false);
                al_draw_startboard(n);
            }
            else if(list){
                al_list(n);
                al_draw_listboard(n);
            }
            else if(setting){
                al_setting(n);
                al_draw_startboard(n);
                n.sample2=al_load_sample("../UI/music/music2.wav");
                if(musicflag)al_play_sample(n.sample2,volume_num/100.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                else al_play_sample(n.sample2,0.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
            }
            else if(quit)break;
        }
        if(judge_in(ev,0.35*game_width,0.2*game_height,0.65*game_width,0.3*game_height)){
            git=checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_start(n);
                al_draw_startboard(n);
                n.sample2=al_load_sample("../UI/music/music2.wav");
                if(musicflag)al_play_sample(n.sample2,volume_num/100.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                else al_play_sample(n.sample2,0.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
            }
        }
        if(judge_in(ev,0.35*game_width,0.35*game_height,0.65*game_width,0.45*game_height)){
            git=2*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_startboard(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                al_load(n,false);
                al_draw_startboard(n);
            }
        }
        if(judge_in(ev,0.35*game_width,0.5*game_height,0.65*game_width,0.6*game_height)){
            git=3*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_startboard(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                al_list(n);
                al_draw_startboard(n);
            }
        }
        if(judge_in(ev,0.35*game_width,0.65*game_height,0.65*game_width,0.75*game_height)){
            git=4*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_startboard(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                al_setting(n);
                al_draw_startboard(n);
                n.sample2=al_load_sample("../UI/music/music2.wav");
                if(musicflag)al_play_sample(n.sample2,volume_num/100.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                else al_play_sample(n.sample2,0.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
            }
        }
        if(judge_in(ev,0.35*game_width,0.8*game_height,0.65*game_width,0.9*game_height)){
            git=5*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_startboard(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)break;
        }
    }
    Destroy_Allegro(&n);
    return 0;
}
