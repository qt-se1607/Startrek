#ifndef INIT_H
#define INIT_H

#include "variate.h"

void Init_Allegro();//初始化allegro
void Destroy_Allegro(allegro *n);//销毁
void Init_Display(allegro *n);//初始化屏幕
void Init_Queue(allegro *n);//添加事件

#endif // INIT_H
