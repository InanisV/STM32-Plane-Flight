#ifndef __DRAW_H
#define __DRAW_H
#include "basic_draw.h"

// 初始化界面
void draw_start_page(void);
void init_play_interface(void);
void draw_new_level(int level);
void draw_end(int *score,int *score_2, int *score_3);

// 渲染
void draw_play_all(int score,int life, int my_plane[2], int my_buttles[100][2], int boss[2], int enemy_planes[10][2], int enemy_buttles[300][2], int limit);
#endif
