#include <Allegro.h>
void al_draw_startboard(allegro n);
void al_setting(allegro n);
void al_load(allegro n);
void al_draw_settingboard(allegro n);
void al_draw_loadboard(allegro n);
void al_list(allegro n);
void al_draw_listboard(allegro n);
void al_turn(float x1,float y1,float x2,float y2,ALLEGRO_COLOR color);
char *int_to_string(int i);
void al_start(allegro n);
int main()
{
    allegro n;
    Init_Allegro(&n);
    game_width = 0.5 * screen_width;
    game_height = 0.6 * screen_height;
    img_x = 0.5 * screen_width;
    img_y = 0.5 * screen_height;
    Init_Display(&n);
    n.bitmap1 = al_load_bitmap("bg1.jpg");
    n.bitmap2 = al_load_bitmap("bg2.jpg");
    n.bitmap3 = al_load_bitmap("bg3.jpg");
    bool event_timer = false;
    int checkout = 0.3*FPS;
    int git = checkout;
    al_start_timer(n.timer);
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.timer.type == ALLEGRO_EVENT_TIMER)event_timer = true;
        if(event_timer && al_is_event_queue_empty(n.event_queue)){
            al_draw_startboard(n);
            event_timer=false;
        }
        quit=false;
        setting=false;
        load=false;
        list=false;
        start=false;
        if(git>=5*checkout)quit=true;
        else if(git>=4*checkout)setting=true;
        else if(git>=3*checkout)list=true;
        else if(git>=2*checkout)load=true;
        else if(git>=checkout)start=true;
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
                al_load(n);
                al_draw_startboard(n);
            }
            else if(list){
                al_list(n);
                al_draw_listboard(n);
            }
            else if(setting){
                al_setting(n);
                al_draw_startboard(n);
            }
            else if(quit)break;
        }
        if(judge_in(ev,0.35*game_width,0.2*game_height,0.65*game_width,0.3*game_height)){
            git=checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_start(n);
                al_draw_startboard(n);
            }
        }
        if(judge_in(ev,0.35*game_width,0.35*game_height,0.65*game_width,0.45*game_height)){
            git=2*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_startboard(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                al_load(n);
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
void al_start(allegro n)
{
    switch(fork()){
    case -1:perror("fork");break;
    case 0:execl("../build-plane-C_C_Application_gcc_7_1_1-Debug/plane",NULL);break;
    default:wait(NULL);break;
    }
}
void al_load(allegro n)
{
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.timer.type == ALLEGRO_EVENT_TIMER)event_timer = true;
        if(event_timer && al_is_event_queue_empty(n.event_queue)){
            al_draw_loadboard(n);
            event_timer=false;
        }
        if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)break;
    }
}
void al_draw_loadboard(allegro n)
{
    al_draw_bitmap(n.bitmap3,0,0,0);
    al_flip_display();
}
void al_setting(allegro n)
{
    setting=false;
    int fp,number=0;
    if((fp=open("./setting",O_RDONLY))==-1){
        if((fp=open("./setting_R",O_RDONLY))==-1){
            screenflag=false;
            musicflag=false;
            volume_num=0;
            number=1;
            fp=open("./setting_R",O_CREAT|O_WRONLY);
            write(fp,&screenflag,sizeof(bool));
            write(fp,&number,sizeof(int));
            write(fp,&musicflag,sizeof(bool));
            write(fp,&volume_num,sizeof(int));
            close(fp);
            fp=open("./setting",O_CREAT|O_WRONLY);
            write(fp,&screenflag,sizeof(bool));
            write(fp,&number,sizeof(int));
            write(fp,&musicflag,sizeof(bool));
            write(fp,&volume_num,sizeof(int));
            close(fp);
            fp=open("./setting",O_RDONLY);
        }
    };
    read(fp,&screenflag,sizeof(bool));
    read(fp,&number,sizeof(int));
    read(fp,&musicflag,sizeof(bool));
    read(fp,&volume_num,sizeof(int));
    close(fp);
    if(number==1)string="1920 x 1080";
    if(number==2)string="1600 x 900";
    if(number==3)string="1280 x 720";
    if(number==4)string="1024 x 576";
    int checkout = 0.3*FPS;
    int git = 7*checkout;
    bool event_timer = false;
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.timer.type == ALLEGRO_EVENT_TIMER)event_timer = true;
        if(event_timer && al_is_event_queue_empty(n.event_queue)){
            al_draw_settingboard(n);
            event_timer=false;
        }
        screen=false;
        resolution=false;
        music=false;
        volume=false;
        save=false;
        set_back=false;
        recover=false;
        if(git>=7*checkout)screen=true;
        else if(git>=6*checkout)resolution=true;
        else if(git>=5*checkout)music=true;
        else if(git>=4*checkout)volume=true;
        else if(git>=3*checkout)save=true;
        else if(git>=2*checkout)recover=true;
        else if(git>=checkout)set_back=true;
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_UP:key_up=true;break;
            case ALLEGRO_KEY_DOWN:key_down=true;break;
            case ALLEGRO_KEY_LEFT:key_left=true;break;
            case ALLEGRO_KEY_RIGHT:key_right=true;break;
            case ALLEGRO_KEY_ENTER:key_enter=true;break;
            }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_UP){
            int i=git%checkout;
            if(key_up)git=git-i+checkout;
            if(key_down)git-=i;
            if(git>=8*checkout)git=checkout;
            switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_UP:key_up=false;break;
            case ALLEGRO_KEY_DOWN:key_down=false;break;
            case ALLEGRO_KEY_LEFT:key_left=false;break;
            case ALLEGRO_KEY_RIGHT:key_right=false;break;
            case ALLEGRO_KEY_ENTER:key_enter=false;break;
            }
        }
        if(key_enter){
            if(save){
                int fd;
                fd=open("./setting",O_CREAT|O_WRONLY);
                write(fd,&screenflag,sizeof(bool));
                write(fd,&number,sizeof(int));
                write(fd,&musicflag,sizeof(bool));
                write(fd,&volume_num,sizeof(int));
                close(fd);
            }
            if(set_back||save)break;
            if(recover){
                int fd;
                fd=open("./setting_R",O_RDONLY);
                read(fd,&screenflag,sizeof(bool));
                read(fd,&number,sizeof(int));
                read(fd,&musicflag,sizeof(bool));
                read(fd,&volume_num,sizeof(int));
                close(fd);
                fd=open("./setting",O_CREAT|O_WRONLY);
                write(fd,&screenflag,sizeof(bool));
                write(fd,&number,sizeof(int));
                write(fd,&musicflag,sizeof(bool));
                write(fd,&volume_num,sizeof(int));
                close(fd);
            }
        }
        if(key_up)git++;
        if(key_down)git--;
        if(git<checkout)git=8*checkout;
        if(git>8*checkout)git=checkout;
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN&&key_left){
            if(screen)screenflag=!screenflag;
            if(resolution){
                number--;
                if(number<1)number=4;
                if(number==1)string="1920 x 1080";
                if(number==2)string="1600 x 900";
                if(number==3)string="1280 x 720";
                if(number==4)string="1024 x 576";
            }
            if(music){
                musicflag=!musicflag;
                if(musicflag)volume_num=50;
                if(!musicflag)volume_num=0;
            }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN&&key_right){
            if(screen)screenflag=!screenflag;
            if(resolution){
                number++;
                if(number>4)number=1;
                if(number==1)string="1920 x 1080";
                if(number==2)string="1600 x 900";
                if(number==3)string="1280 x 720";
                if(number==4)string="1024 x 576";
            }
            if(music){
                musicflag=!musicflag;
                if(musicflag)volume_num=50;
                if(!musicflag)volume_num=0;
            }
        }
        if(key_left&&musicflag&&volume&&volume_num>=0)volume_num-=0.3;
        if(key_right&&musicflag&&volume&&volume_num<=100)volume_num+=0.3;

        if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(judge_in(ev,0.6*game_width-word_size,0.25*game_height-0.1*word_size,0.6*game_width,0.25*game_height+1.1*word_size)||
                    judge_in(ev,0.8*game_width,0.25*game_height-0.1*word_size,0.8*game_width+word_size,0.25*game_height+1.1*word_size)){
                screenflag=!screenflag;
            }
            if(judge_in(ev,0.6*game_width-word_size,0.35*game_height-0.1*word_size,0.6*game_width,0.35*game_height+1.1*word_size)){
                number--;
                if(number<1)number=4;
                if(number==1)string="1920 x 1080";
                if(number==2)string="1600 x 900";
                if(number==3)string="1280 x 720";
                if(number==4)string="1024 x 576";
            }
            if(judge_in(ev,0.8*game_width,0.35*game_height-0.1*word_size,0.8*game_width+word_size,0.35*game_height+1.1*word_size)){
                number++;
                if(number>4)number=1;
                if(number==1)string="1920 x 1080";
                if(number==2)string="1600 x 900";
                if(number==3)string="1280 x 720";
                if(number==4)string="1024 x 576";
            }
            if(judge_in(ev,0.6*game_width-word_size,0.45*game_height-0.1*word_size,0.6*game_width,0.45*game_height+1.1*word_size)||
                    judge_in(ev,0.8*game_width,0.45*game_height-0.1*word_size,0.8*game_width+word_size,0.45*game_height+1.1*word_size)){
                musicflag=!musicflag;
                if(musicflag)volume_num=50;
                else volume_num=0;
            }
            if(musicflag&&
                    judge_in(ev,0.6*game_width-word_size,0.55*game_height-0.1*word_size,0.6*game_width,0.55*game_height+1.1*word_size)){
                volume_num-=10;
                if(volume_num<0)volume_num=0;
            }
            if(musicflag&&
                    judge_in(ev,0.8*game_width,0.55*game_height-0.1*word_size,0.8*game_width+word_size,0.55*game_height+1.1*word_size)){
                volume_num+=10;
                if(volume_num>100)volume_num=100;
            }
            if(judge_in(ev,0.6*game_width,0.55*game_height-0.1*word_size,0.8*game_width,0.55*game_height+1.1*word_size)){
                volume_num=(ev.mouse.x-0.6*game_width)/(0.2*game_width/100);
            }
        }

        //screen
        if(judge_in(ev,0.2*game_width,0.25*game_height-0.1*word_size,
                    0.8*game_width+word_size,0.25*game_height+1.1*word_size))git=7*checkout;

        //resolution
        if(judge_in(ev,0.2*game_width,0.35*game_height-0.1*word_size,
                    0.8*game_width+word_size,0.35*game_height+1.1*word_size))git=6*checkout;

        //music
        if(judge_in(ev,0.2*game_width,0.45*game_height-0.1*word_size,
                    0.8*game_width+word_size,0.45*game_height+1.1*word_size))git=5*checkout;

        //volume
        if(judge_in(ev,0.2*game_width,0.55*game_height-0.1*word_size,
                    0.8*game_width+word_size,0.55*game_height+1.1*word_size))git=4*checkout;

        //save
        if(judge_in(ev,0.4*game_width,0.65*game_height-0.1*word_size,0.6*game_width,0.65*game_height+1.1*word_size)){
            git=3*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_settingboard(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                int fd;
                fd=open("./setting",O_CREAT|O_WRONLY);
                write(fd,&screenflag,sizeof(bool));
                write(fd,&number,sizeof(int));
                write(fd,&musicflag,sizeof(bool));
                write(fd,&volume_num,sizeof(int));
                close(fd);
                break;
            }
        }
        //recover
        if(judge_in(ev,0.4*game_width,0.75*game_height-0.1*word_size,0.6*game_width,0.75*game_height+1.1*word_size)){
            git=2*checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_settingboard(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                int fd;
                fd=open("./setting_R",O_RDONLY);
                read(fd,&screenflag,sizeof(bool));
                read(fd,&number,sizeof(int));
                read(fd,&musicflag,sizeof(bool));
                read(fd,&volume_num,sizeof(int));
                close(fd);
                fd=open("./setting",O_CREAT|O_WRONLY);
                write(fd,&screenflag,sizeof(bool));
                write(fd,&number,sizeof(int));
                write(fd,&musicflag,sizeof(bool));
                write(fd,&volume_num,sizeof(int));
                close(fd);
            }
        }
        //set_back
        if(judge_in(ev,0.4*game_width,0.85*game_height-0.1*word_size,0.6*game_width,0.85*game_height+1.1*word_size)){
            git=checkout;
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_draw_settingboard(n);
            }
            if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)break;
        }
    }
}
void al_draw_settingboard(allegro n)
{
    al_draw_bitmap(n.bitmap2,0,0,0);
    al_draw_text(n.font2,white,0.5*game_width,word_size,ALLEGRO_ALIGN_CENTER,"设   置");

    //screen
    al_draw_text(n.font1,white,0.2*game_width,0.25*game_height,ALLEGRO_ALIGN_LEFT,"全     屏");
    if(screen)al_turn(0.6*game_width,0.25*game_height-0.1*word_size,0.8*game_width,0.25*game_height+1.1*word_size,yellow_pink);
    al_draw_filled_rectangle(0.6*game_width,0.25*game_height-0.1*word_size,0.8*game_width,0.25*game_height+1.1*word_size,green_cyan);
    if(screenflag)al_draw_text(n.font1,white,0.7*game_width,0.25*game_height,ALLEGRO_ALIGN_CENTER,"开   启");
    else al_draw_text(n.font1,white,0.7*game_width,0.25*game_height,ALLEGRO_ALIGN_CENTER,"关   闭");

    //resolution
    al_draw_text(n.font1,white,0.2*game_width,0.35*game_height,ALLEGRO_ALIGN_LEFT,"分 辨 率");
    if(resolution)al_turn(0.6*game_width,0.35*game_height-0.1*word_size,0.8*game_width,0.35*game_height+1.1*word_size,yellow_pink);
    al_draw_filled_rectangle(0.6*game_width,0.35*game_height-0.1*word_size,0.8*game_width,0.35*game_height+1.1*word_size,green_cyan);
    al_draw_text(n.font1,white,0.7*game_width,0.35*game_height,ALLEGRO_ALIGN_CENTER,string);

    //music
    al_draw_text(n.font1,white,0.2*game_width,0.45*game_height,ALLEGRO_ALIGN_LEFT,"音   乐");
    if(music)al_turn(0.6*game_width,0.45*game_height-0.1*word_size,0.8*game_width,0.45*game_height+1.1*word_size,yellow_pink);
    al_draw_filled_rectangle(0.6*game_width,0.45*game_height-0.1*word_size,0.8*game_width,0.45*game_height+1.1*word_size,green_cyan);
    if(musicflag)al_draw_text(n.font1,white,0.7*game_width,0.45*game_height,ALLEGRO_ALIGN_CENTER,"开   启");
    else al_draw_text(n.font1,white,0.7*game_width,0.45*game_height,ALLEGRO_ALIGN_CENTER,"关   闭");

    //volume
    al_draw_text(n.font1,white,0.2*game_width,0.55*game_height,ALLEGRO_ALIGN_LEFT,"音   量");
    if(volume)al_turn(0.6*game_width,0.55*game_height-0.1*word_size,0.8*game_width,0.55*game_height+1.1*word_size,yellow_pink);
    al_draw_filled_rectangle(0.6*game_width,0.55*game_height-0.1*word_size,0.8*game_width,0.55*game_height+1.1*word_size,green_cyan);
    al_draw_filled_rectangle(0.6*game_width,0.55*game_height-0.1*word_size,
                             0.6*game_width+0.2*game_width*(volume_num/100.0),0.55*game_height+1.1*word_size,
                             red_cadmium);
    al_draw_text(n.font1,black,0.7*game_width,0.55*game_height,ALLEGRO_ALIGN_CENTER,int_to_string(volume_num));

    //save
    if(save)al_draw_filled_rounded_rectangle(0.4*game_width,0.65*game_height-0.1*word_size,0.6*game_width,0.65*game_height+1.1*word_size,
                                     0.2*word_size,0.2*word_size,blue_manganic);
    al_draw_text(n.font1,white,0.5*game_width,0.65*game_height,ALLEGRO_ALIGN_CENTER,"保存并返回");

    //recover
    if(recover)al_draw_filled_rounded_rectangle(0.4*game_width,0.75*game_height-0.1*word_size,0.6*game_width,0.75*game_height+1.1*word_size,
                                                0.2*word_size,0.2*word_size,blue_manganic);
    al_draw_text(n.font1,white,0.5*game_width,0.75*game_height,ALLEGRO_ALIGN_CENTER,"恢 复 默 认");

    //set_back
    if(set_back)al_draw_filled_rounded_rectangle(0.4*game_width,0.85*game_height-0.1*word_size,0.6*game_width,0.85*game_height+1.1*word_size,
                                                 0.2*word_size,0.2*word_size,blue_manganic);
    al_draw_text(n.font1,white,0.5*game_width,0.85*game_height,ALLEGRO_ALIGN_CENTER,"返      回");

    al_flip_display();
}
void al_draw_startboard(allegro n)
{
    al_draw_bitmap(n.bitmap1,0,0,0);
    //start
    if(start){
        al_draw_filled_rounded_rectangle(0.35*game_width,0.2*game_height,0.65*game_width,0.3*game_height,0.05*game_width,0.05*game_height,white);
        al_draw_text(n.font1,black,0.5*game_width,0.25*game_height-0.5*word_size,ALLEGRO_ALIGN_CENTER,"新 的 游 戏");
    }
    else{
        al_draw_filled_rounded_rectangle(0.35*game_width,0.2*game_height,0.65*game_width,0.3*game_height,0.05*game_width,0.05*game_height,black);
        al_draw_text(n.font1,white,0.5*game_width,0.25*game_height-0.5*word_size,ALLEGRO_ALIGN_CENTER,"新 的 游 戏");
    }
    //load
    if(load){
        al_draw_filled_rounded_rectangle(0.35*game_width,0.35*game_height,0.65*game_width,0.45*game_height,0.05*game_width,0.05*game_height,white);
        al_draw_text(n.font1,black,0.5*game_width,0.4*game_height-0.5*word_size,ALLEGRO_ALIGN_CENTER,"继 续 游 戏");
    }
    else{
        al_draw_filled_rounded_rectangle(0.35*game_width,0.35*game_height,0.65*game_width,0.45*game_height,0.05*game_width,0.05*game_height,black);
        al_draw_text(n.font1,white,0.5*game_width,0.4*game_height-0.5*word_size,ALLEGRO_ALIGN_CENTER,"继 续 游 戏");
    }
    //list
    if(list){
        al_draw_filled_rounded_rectangle(0.35*game_width,0.5*game_height,0.65*game_width,0.6*game_height,0.05*game_width,0.05*game_height,white);
        al_draw_text(n.font1,black,0.5*game_width,0.55*game_height-0.5*word_size,ALLEGRO_ALIGN_CENTER,"排 行 榜");
    }
    else{
        al_draw_filled_rounded_rectangle(0.35*game_width,0.5*game_height,0.65*game_width,0.6*game_height,0.05*game_width,0.05*game_height,black);
        al_draw_text(n.font1,white,0.5*game_width,0.55*game_height-0.5*word_size,ALLEGRO_ALIGN_CENTER,"排 行 榜");
    }
    //setting
    if(setting){
        al_draw_filled_rounded_rectangle(0.35*game_width,0.65*game_height,0.65*game_width,0.75*game_height,0.05*game_width,0.05*game_height,white);
        al_draw_text(n.font1,black,0.5*game_width,0.7*game_height-0.5*word_size,ALLEGRO_ALIGN_CENTER,"设     置");
    }
    else{
        al_draw_filled_rounded_rectangle(0.35*game_width,0.65*game_height,0.65*game_width,0.75*game_height,0.05*game_width,0.05*game_height,black);
        al_draw_text(n.font1,white,0.5*game_width,0.7*game_height-0.5*word_size,ALLEGRO_ALIGN_CENTER,"设     置");
    }
    //quit
    if(quit){
        al_draw_filled_rounded_rectangle(0.35*game_width,0.8*game_height,0.65*game_width,0.9*game_height,0.05*game_width,0.05*game_height,white);
        al_draw_text(n.font1,black,0.5*game_width,0.85*game_height-0.5*word_size,ALLEGRO_ALIGN_CENTER,"退 出 游 戏");
    }
    else{
        al_draw_filled_rounded_rectangle(0.35*game_width,0.8*game_height,0.65*game_width,0.9*game_height,0.05*game_width,0.05*game_height,black);
        al_draw_text(n.font1,white,0.5*game_width,0.85*game_height-0.5*word_size,ALLEGRO_ALIGN_CENTER,"退 出 游 戏");
    }
    al_flip_display();
}
void al_list(allegro n)
{
    int fd;
    if((fd=open("./list",O_RDONLY))==-1){
        fd=open("./list",O_CREAT|O_WRONLY);
        for(int i=0;i<list_num;i++){
            char *name="<昵称>";
            int socre_num=48;
            int month=48,day=48,hour=48,minute=48;
            write(fd,name,sizeof(char)*MAXSIZE);
            write(fd,&socre_num,sizeof(int));
            write(fd,&month,sizeof(int));
            write(fd,&day,sizeof(int));
            write(fd,&hour,sizeof(int));
            write(fd,&minute,sizeof(int));
        }
        close(fd);
    }
    al_draw_listboard(n);
    bool event_timer=false;
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(n.event_queue,&ev);
        if(ev.timer.type == ALLEGRO_EVENT_TIMER)event_timer = true;
        if(ev.type==ALLEGRO_EVENT_KEY_DOWN&&ev.keyboard.keycode==ALLEGRO_KEY_ENTER)break;
        if(ev.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP&&
                judge_in(ev,0.35*game_width,0.85*game_height,0.65*game_width,0.95*game_height))break;
        if(event_timer&&al_is_event_queue_empty(n.event_queue))al_flip_display();
    }
}
void al_draw_listboard(allegro n)
{
    al_draw_bitmap(n.bitmap3,0,0,0);
    int fd=open("./list",O_RDONLY);
    char name[MAXSIZE];
    int socre_num=0,month=0,day=0,hour=0,minute=0;
    for(int i=0;i<list_num;i++){
        read(fd,&name,sizeof(char)*MAXSIZE);
        read(fd,&socre_num,sizeof(int));
        read(fd,&month,sizeof(int));
        read(fd,&day,sizeof(int));
        read(fd,&hour,sizeof(int));
        read(fd,&minute,sizeof(int));
        al_draw_text(n.font1,white,0.5*game_width,0.1*(i+1)*game_height,ALLEGRO_ALIGN_CENTER,name);
    }
    al_draw_filled_rounded_rectangle(0.35*game_width,0.85*game_height,0.65*game_width,0.95*game_height,0.05*game_width,0.05*game_height,black);
    al_draw_text(n.font1,white,0.5*game_width,0.9*game_height-0.5*word_size,ALLEGRO_ALIGN_CENTER,"返     回");
    al_flip_display();
}
void al_turn(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color)
{
    al_draw_filled_triangle(x1-0.1*word_size,y1,x1-word_size,y1+0.6*word_size,x1-0.1*word_size,y1+1.2*word_size,color);
    al_draw_filled_triangle(x2+0.1*word_size,y2,x2+word_size,y2-0.6*word_size,x2+0.1*word_size,y2-1.2*word_size,color);
}
char *int_to_string(int i)
{
    char *p=str;
    for(int a=0;a<4;a++)str[a]='\0';
    for(int a=2;a>=0;a--){
        str[a]=i%10+48;
        if(i==0)break;
        i=i/10;
    }
    if(str[0]=='0')p=&str[1];
    return p;
}
