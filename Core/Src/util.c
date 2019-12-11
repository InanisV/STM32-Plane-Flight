#include "util.h"

#define KEY0_Pin GPIO_PIN_5
#define KEY0_GPIO_Port GPIOC

void KEY0_or_POWER_to_skip(void){
	while(1){
		if(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET){break;}
		else{HAL_Delay(10);}
	}
}

// 数组前移
void arrange_my_buttles(int my_buttles[100][2]){
	int i=0;
	if(my_buttles[0][0] == 0){
		for(i=0; i<99; i++){
			my_buttles[i][0] = my_buttles[i+1][0];
			my_buttles[i][1] = my_buttles[i+1][1];
		}
	}
}

// 数组前移
void arrange_enemy_planes(int enemy_planes[10][2]){
	int i=0;
	if(enemy_planes[0][0] == 0){
		for(i=0; i<9; i++){
			enemy_planes[i][0] = enemy_planes[i+1][0];
			enemy_planes[i][1] = enemy_planes[i+1][1];
		}
	}
}

// 数组前移
void arrange_enemy_buttles(int enemy_buttles[300][2]){
	int i=0;
	if(enemy_buttles[0][0] == 0){
		for(i=0; i<299; i++){
			enemy_buttles[i][0] = enemy_buttles[i+1][0];
			enemy_buttles[i][1] = enemy_buttles[i+1][1];
		}
	}
}
