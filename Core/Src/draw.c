#include "lcd.h"
#include "draw.h"
#include <stdio.h>

//初始化界面
void draw_start_page(void){
	LCD_ShowString(30,180,200,24,24,"Aircraft");
	LCD_ShowString(130,180,200,24,24,"Battle");
	
	draw_my_plane(120,120);
	
	LCD_ShowString(80,250,200,12,12,"PRESS KEY-0");
}

void init_play_interface(void){
	//设置基础界面
//	LCD_DrawLine(1,1,239,1);
	LCD_DrawLine(1,40,239,40);

//	LCD_DrawLine(1,1,1,40);
//	LCD_DrawLine(239,1,239,40);

//	LCD_DrawLine(130,1,130,40);

	LCD_ShowString(8,7,100,24,24,"score");
	LCD_ShowString(130,7,100,24,24,"life");
}

void draw_new_level(int level){
	char str[3];
	sprintf(str, "%d", level);
	LCD_ShowString(30,180,200,24,24,"Level");
	LCD_ShowString(130,180,200,24,24,str);
}

// game over界面
void draw_end(int *score,int *score_2, int *score_3){
	LCD_Clear(GRAY);
	
	LCD_ShowString(60,30,200,24,24,"Game Over");
	LCD_ShowString(30,80,200,24,24,"My SCORE");
	LCD_ShowxNum(130,80,*score,4,24,0);
	if(*score_2 == 0 && *score_3 == 0){
		*score_2 = *score;
		LCD_ShowString(30,140,200,24,24,"Rank1");
		LCD_ShowxNum(130,140,*score_2,4,24,0);
		LCD_ShowString(30,200,200,24,24,"Rank2");
		LCD_ShowString(160,200,200,24,24,"--");
	}else if(*score_2 != 0 && *score_3 == 0){
		if (*score > *score_2) {
			*score_3 = *score_2;
			*score_2 = *score;
		} else if (*score < *score_2) {
			*score_3 = *score;
		}
		LCD_ShowString(30,140,200,24,24,"Rank1");
		LCD_ShowxNum(130,140,*score_2,4,24,0);
		LCD_ShowString(30,200,200,24,24,"Rank2");
		LCD_ShowxNum(130,200,*score_3,4,24,0);
	}else if(*score_2 != 0 && *score_3 != 0){
		if (*score > *score_2) {
			*score_3 = *score_2;
			*score_2 = *score;
		} else if (*score < *score_2 && *score > *score_3) {
			*score_3 = *score;
		}
		LCD_ShowString(30,140,200,24,24,"Rank1");
		LCD_ShowxNum(130,140,*score_2,4,24,0);
		LCD_ShowString(30,200,200,24,24,"Rank2");
		LCD_ShowxNum(130,200,*score_3,4,24,0);
	}

	*score = 0;
	
	LCD_ShowString(60,280,200,12,12,"Powered by 2019SUSTech");
}


//渲染函数，帧动画调用渲染
//包含分数/生命渲染
//我方子弹渲染
//敌方飞机渲染
//敌方子弹渲染

//其他渲染可调用 basic_draw.h
//1. 我方飞机渲染
//2. boss渲染
//3. cross渲染
void draw_play_title(int score, int life, int limit){
	int i=0;
	int start_x = 195;
	
	//LCD_Fill(75,8,130,32,GRAY);
	LCD_ShowxNum(67,7,score,4,24,0);		//分数
	
	LCD_Fill(190,15,226,25,BACK_COLOR);
	for(i=0; i<life; i++){	//生命值ֵ
		draw_heart(start_x+i*13, 20);
	}
	LCD_ShowxNum(180,41,(60-limit),4,24,0);
}

//#define my_buttle_max 100
//#define enemy_buttle_max 300
//#define enemy_plane_max 10
void draw_all_my_buttles(int my_buttles[100][2]){
	int i =0;
	for(i=0; i<100; i++){
		if(my_buttles[i][0] == 0){
			break;
		}else{
			draw_my_bullet(my_buttles[i][0],my_buttles[i][1]);
		}
	}
}

void draw_all_enemy_planes(int enemy_planes[10][2]){
	int i = 0;
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] == 0){
			break;
		}else{
			draw_enemy_plane(enemy_planes[i][0],enemy_planes[i][1]);
		}
	}
}

void draw_all_enemy_buttles(int enemy_buttles[300][2]){
	int i =0;
	for(i=0; i<300; i++){
		if(enemy_buttles[i][0] == 0){
			break;
		}else{
			draw_enemy_bullet(enemy_buttles[i][0],enemy_buttles[i][1]);
		}
	}
}

//全体渲染
void draw_play_all(int score,int life, int my_plane[2], int my_buttles[100][2], int boss[2], int enemy_planes[10][2], int enemy_buttles[300][2], int limit){
	draw_play_title(score,life,limit);
	
	draw_my_plane(my_plane[0],my_plane[1]);
	draw_all_my_buttles(my_buttles);
	
	draw_boss(boss[0],boss[1]);

	draw_all_enemy_planes(enemy_planes);
	draw_all_enemy_buttles(enemy_buttles);
}

