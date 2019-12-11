#ifndef __UTIL_H
#define __UTIL_H
#include "lcd.h"
#include "stm32f1xx_hal.h"

void KEY0_or_POWER_to_skip(void);

void arrange_my_buttles(int my_buttles[100][2]);
void arrange_enemy_planes(int enemy_planes[10][2]);
void arrange_enemy_buttles(int enemy_buttles[300][2]);
	
#endif
