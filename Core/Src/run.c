#include "run.h"
#include <stdlib.h>

#define KEY_WK_Pin GPIO_PIN_0
#define KEY_WK_GPIO_Port GPIOA
#define KEY0_Pin GPIO_PIN_5
#define KEY0_GPIO_Port GPIOC
#define LED0_Pin GPIO_PIN_8
#define LED0_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_15
#define KEY1_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOD

int left_limit = 2;
int right_limit = 238;
int up_limit = 42;
int down_limit = 318;

int check_overlap(int x, int y, int bound, int enemy_planes[10][2]){
	int i = 0;
	for(i = 0; i < bound*3; i++){
		if(enemy_planes[i][0] != 0 && (abs(enemy_planes[i][0]-x) <= 20 && abs(enemy_planes[i][1]-y) <= 30)){
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
			HAL_Delay(80);
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
			HAL_Delay(80);
			return 1;
		}
	}
	return 0;
}

//敌人数 <= 关卡 * 3,
//一次只生成一个飞机
//生成飞机概率 => 对应关卡
void generate_enemy_planes(int level, int enemy_planes[10][2]){
	int i = 0;
	int possibility_range = 0;
	
	if(level == 0){
		possibility_range = 3;
	}else if(level == 1){
		possibility_range = 4;
	}else if(level == 2){
		possibility_range = 5;
	}else{
		possibility_range = 6;
	}
		
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] == 0){
			if(i < (level+1)*3){
				if(rand()%100 < possibility_range){
					int x = rand()%217 + 11;
					int y = 61;
					int count = 0;
					while(check_overlap(x, y, level+1, enemy_planes) == 1 && count < 3){
						x = rand()%217 + 11;
						count++;
					}
					enemy_planes[i][0] = x;
					enemy_planes[i][1] = y;
//					enemy_planes[i][0] = rand()%217 + 11;
//					enemy_planes[i][1] = 61;
				}
			}
			break;
		}
	}
}

void switch_my_act(int my_plane[2],int my_buttles[100][2]){
	int i=0;
	
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET){
		LCD_Fill(my_plane[0]-20,my_plane[1]-20,	my_plane[0]+20,my_plane[1]+30,BACK_COLOR);
		if(my_plane[0]-10 > left_limit){
			my_plane[0] = my_plane[0]-3;
		}
	}else if(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET){
		LCD_Fill(my_plane[0]-20,my_plane[1]-20,	my_plane[0]+20,my_plane[1]+30,BACK_COLOR);
		if(my_plane[0]+10 < right_limit){
			my_plane[0] = my_plane[0]+3;
		}
	}else if(HAL_GPIO_ReadPin(KEY_WK_GPIO_Port, KEY_WK_Pin) == GPIO_PIN_SET){
		LCD_Fill(my_plane[0]-20,my_plane[1]-20,	my_plane[0]+20,my_plane[1]+30,BACK_COLOR);
		for(i=0; i<100; i++){
			if(my_buttles[i][0] == 0){
				my_buttles[i][0] = my_plane[0];
				my_buttles[i][1] = my_plane[1]-22;
					
				//print_num(190,220,i);
				break;
			}
		}
	}
}

void update_my_buttles(int my_buttles[100][2]){
	int i=0;
	
	for(i=0; i<100; i++){
		if(my_buttles[i][0] != 0){
			// 清除之前所画
			LCD_Fill(my_buttles[i][0]-1,my_buttles[i][1]-1,	my_buttles[i][0]+1,my_buttles[i][1]+1,BACK_COLOR);
			
			my_buttles[i][1] = my_buttles[i][1] - 3;
			
			// 边界销毁
			if(my_buttles[i][1] < 42){				
				my_buttles[i][0] = 0;
				my_buttles[i][1] = 0;
			}
		}
	}
	// 后续数组前移 ？
	arrange_my_buttles(my_buttles);
}

void update_enemy_planes(int level, int enemy_planes[10][2]){
	int i=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			// 清除之前所画
			LCD_Fill(enemy_planes[i][0]-10,enemy_planes[i][1]-20,	enemy_planes[i][0]+10,enemy_planes[i][1]+20,BACK_COLOR);
			
			if(level == 0){
				enemy_planes[i][1] = enemy_planes[i][1] + 1;
			}else if(level == 1){
				enemy_planes[i][1] = enemy_planes[i][1] + 2;
			}else if(level == 2){
				enemy_planes[i][1] = enemy_planes[i][1] + 3;
			}else{
				enemy_planes[i][1] = enemy_planes[i][1] + 4;
			}
			
			// 边界销毁
			if(enemy_planes[i][1] > 298){			
				enemy_planes[i][0] = 0;
				enemy_planes[i][1] = 0;
			}
		}
	}
	// 后续数组前移 ？
	arrange_enemy_planes(enemy_planes);
}

void check_my_plane_to_enemy_plane_collide(int *score, int *life, int my_plane[2], int enemy_planes[10][2]){
	int i=0;
	int temp=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			// 碰撞检测
			if(abs(enemy_planes[i][0] - my_plane[0]) <= 20){
				if(abs(enemy_planes[i][1] - my_plane[1]) <= 40){
					LCD_Fill(my_plane[0]-10,my_plane[1]-20,	my_plane[0]+10,my_plane[1]+20,BACK_COLOR);
					LCD_Fill(enemy_planes[i][0]-10,enemy_planes[i][1]-20,	enemy_planes[i][0]+10,enemy_planes[i][1]+20,BACK_COLOR);
					
					my_plane[0] = 120;
					my_plane[1] = 290;
					
					enemy_planes[i][0] = 0;
					enemy_planes[i][1] = 0;
					
					temp = (*score);
					(*score) = temp+1;
					
					temp = (*life);
					(*life) = temp-1;
					break;
				}
			}
		}
	}
	// 由于敌方飞机有生成间隔，所以在一帧内碰撞最多只会存在一次  敌方飞机间隔(最少为3) > 每帧运动像素(1) ？
	arrange_enemy_planes(enemy_planes);
}

void check_my_buttles_to_enemy_plane_collide(int *score, int my_buttles[100][2], int enemy_planes[10][2]){
	int i=0;
	int j=0;
	int temp=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			for(j=0; j<100; j++){
				// 碰撞检测
				if(abs(my_buttles[j][0] - enemy_planes[i][0]) <= 12){
					if(abs(my_buttles[j][1] - enemy_planes[i][1]) <= 22){
						LCD_Fill(enemy_planes[i][0]-10,enemy_planes[i][1]-20,	enemy_planes[i][0]+10,enemy_planes[i][1]+20,BACK_COLOR);
					
						my_buttles[j][0] = 0;
						my_buttles[j][1] = 0;
						
						enemy_planes[i][0] = 0;
						enemy_planes[i][1] = 0;
						
						temp = (*score);
						(*score) = temp+1;

						HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
						HAL_Delay(80);
						HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
						HAL_Delay(80);
						HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
						HAL_Delay(80);
						HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
						break;
					}
				}
			}
			//飞机只可能碰撞一个 ？
			arrange_enemy_planes(enemy_planes);
		}
	}
	//这里因为 碰撞一次 后就退出了，所以子弹只在第一次发现碰撞时被销毁
	//即使可以有两个子弹满足碰撞条件 => 子弹高度 3 < 每帧相对运动像素(3+1)，但只碰撞第一个 ？
	arrange_my_buttles(my_buttles);
}

void clear_all_enemy_plane(int my_plane[2],	int enemy_plane[10][2]){
	int i=0;
	
	for(i=0; i<10; i++){
		enemy_plane[i][0] = 0;
		enemy_plane[i][1] = 0;
	}
	LCD_Fill(1,41,239,318,BACK_COLOR);
	
	draw_my_plane(my_plane[0],my_plane[1]);
}









