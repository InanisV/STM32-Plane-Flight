#ifndef __RUN_H
#define __RUN_H	
#include "util.h"
#include "draw.h"
#include "stm32f1xx_hal.h"


void generate_enemy_planes(int level, int enemy_planes[10][2]);

// 从输入中更新玩家
void switch_my_act(int my_plane[2],int my_buttles[300][2]);

// 更新位置
void update_my_buttles(int my_buttles[100][2]);
void update_enemy_planes(int level, int enemy_planes[10][2]);

void check_my_plane_to_enemy_plane_collide(int *score,int *life,	int my_plane[2], int enemy_planes[10][2]);
void check_my_buttles_to_enemy_plane_collide(int *score,	int my_buttles[300][2], int enemy_planes[10][2]);

void clear_all_enemy_plane(int my_plane[2], int enemy_plane[10][2]);

#endif
