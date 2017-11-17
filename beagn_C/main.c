#include"allegro.h"
#include"began.h"
#include"variate.h"

circle click=NULL;

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
            number=4;
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
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.timer.type == ALLEGRO_EVENT_TIMER)event_timer = true;
        if(event_timer&& al_is_event_queue_empty(n.event_queue)){
            al_draw_startboard(n,0,0);
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
            }
            else if(load){
                al_load(n,false);
                al_draw_startboard(n,0,0);
            }
            else if(list){
                al_list(n);
                al_draw_listboard(n,0,0);
            }
            else if(setting){
                al_setting(n);
                al_draw_startboard(n,0,0);
            }
            else if(quit)break;
        }
        if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if(musicflag)al_play_sample(n.sample1,volume_num/100,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            circle p=click;
            if(!p){
                click=(circle)malloc(sizeof(Circle));
                click->x=ev.mouse.x;
                click->y=ev.mouse.y;
                click->size=1;
                click->color=al_map_rgb(Rand(0,255),Rand(0,255),Rand(0,255));
                click->next=NULL;
            }
            else{
                while(p->next)p=p->next;
                p->next=(circle)malloc(sizeof(Circle));
                p=p->next;
                p->x=ev.mouse.x;
                p->y=ev.mouse.y;
                p->size=1;
                p->color=al_map_rgb(Rand(0,255),Rand(0,255),Rand(0,255));
                p->next=NULL;
            }
        }
        circle p1=click;
        circle p2=NULL;
        while(p2){
            if(p2->size>al_get_display_width(n.display)){
                p1->next=p2->next;
                circle a=p2;
                p2=NULL;
                free(a);
            }
            p1=p1->next;
            if(!p1)break;
            p2=p1->next;
        }
        if(click&&click->size>al_get_display_width(n.display))click=click->next;
        if(judge_in(ev,0.35*game_width,0.41*game_height,0.65*game_width,0.51*game_height)){
            git=checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_startboard(n,0,0);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                al_start(n);
                al_draw_startboard(n,0,0);
            }
        }
        if(judge_in(ev,0.35*game_width,0.52*game_height,0.65*game_width,0.62*game_height)){
            git=2*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_startboard(n,0,0);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                al_load(n,false);
                al_draw_startboard(n,0,0);
            }
        }
        if(judge_in(ev,0.35*game_width,0.63*game_height,0.65*game_width,0.73*game_height)){
            git=3*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_startboard(n,0,0);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                al_list(n);
                al_draw_startboard(n,0,0);
            }
        }
        if(judge_in(ev,0.35*game_width,0.74*game_height,0.65*game_width,0.84*game_height)){
            git=4*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_startboard(n,0,0);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                al_setting(n);
                al_draw_startboard(n,0,0);
            }
        }
        if(judge_in(ev,0.35*game_width,0.85*game_height,0.65*game_width,0.95*game_height)){
            git=5*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_startboard(n,0,0);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)break;
        }
    }
    Destroy_Allegro(&n);
    while(click){
        circle a=click;
        click=click->next;
        free(a);
    }
    return 0;
}
