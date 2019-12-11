#include "lcd.h"
#include "basic_draw.h"

#define BULLET_COLOR MAGENTA

//x,y用来标识中心点位置
//所以以下尺寸都按照单数来计算

int big_trigon_width = 21;
int big_trigon_height = 35;

int small_trigon_width = 11;
int small_trigon_height = 11;

int cross_width = 15; 
int cross_height = 15;

int heart_width = 11;
int heart_height = 11;

int buttle_width = 3; 
int buttle_height = 3;

int star_width = 5;
int star_height = 9;

//画正向等腰三角形
void draw_forward_trigon(int x,int y,int width, int height);
//画反向等腰三角形
void draw_reversed_trigon(int x,int y,int width, int height);

void draw_rectangle(int x, int y, int width, int height);

void draw_left_triangle(int x, int y, int width, int height);

void draw_right_triangle(int x, int y, int width, int height);

void draw_trapezoid(int x, int y, int upper_width, int lower_width, int height);

void draw_my_plane(int x, int y){
	draw_rectangle(x, y, 4, 24);
	draw_left_triangle(x, y + 16, 12, 9);
	draw_right_triangle(x + 4, y + 16, 12, 9);
	draw_trapezoid(x + 2, y + 24, 6, 14, 4);

}

void draw_enemy_plane(int x ,int y){
	draw_reversed_trigon(x,y-15,big_trigon_width,big_trigon_height);
	draw_reversed_trigon(x,y-20,small_trigon_width,small_trigon_height);
}

void draw_boss(int x, int y){
	if(x != 0){
		if(y != 0){
			draw_reversed_trigon(x,y-15,big_trigon_width*2,big_trigon_height);
			draw_reversed_trigon(x,y-20,small_trigon_width*2,small_trigon_height);
		}
	}
}

void draw_my_bullet(int x, int y){
	LCD_Fast_DrawPoint(x, y-1, BULLET_COLOR);
	LCD_Fast_DrawPoint(x-1, y, BULLET_COLOR);
	LCD_Fast_DrawPoint(x, y, BULLET_COLOR);
	LCD_Fast_DrawPoint(x+1, y, BULLET_COLOR);
	LCD_Fast_DrawPoint(x-1, y+1, BULLET_COLOR);
	LCD_Fast_DrawPoint(x, y+1, BULLET_COLOR);
	LCD_Fast_DrawPoint(x+1, y+1, BULLET_COLOR);
//	LCD_DrawPoint(x,y-1);
//
//	LCD_DrawPoint(x-1,y);
//	LCD_DrawPoint(x,y);
//	LCD_DrawPoint(x+1,y);
//
//	LCD_DrawPoint(x-1,y+1);
//	LCD_DrawPoint(x,y+1);
//	LCD_DrawPoint(x+1,y+1);
}

void draw_enemy_bullet(int x, int y){
	LCD_DrawPoint(x-1,y-1);
	LCD_DrawPoint(x,y-1);
	LCD_DrawPoint(x+1,y-1);
	
	LCD_DrawPoint(x-1,y);
	LCD_DrawPoint(x,y);
	LCD_DrawPoint(x+1,y);

	LCD_DrawPoint(x,y+1);
}

void draw_cross(int x, int y){
	LCD_DrawLine(x-cross_width/2,y-cross_height/2, x+cross_width/2,y+cross_height/2);
	LCD_DrawLine(x-cross_width/2,y+cross_height/2, x+cross_width/2,y-cross_height/2);
}

void draw_heart(int x, int y){
	int i = 0;
	for (i = heart_width/2; i > 0; i--){
		LCD_Draw_Circle(x, y, i);
	}
//	LCD_DrawLine(x-heart_width/2,y-heart_height/2, x+heart_width/2,y+heart_height/2);
//	LCD_DrawLine(x-heart_width/2,y+heart_height/2, x+heart_width/2,y-heart_height/2);
//
//	LCD_DrawLine(x-heart_width/2,y, x+heart_width/2,y);
//	LCD_DrawLine(x,y+heart_height/2, x,y-heart_height/2);
}


void draw_star(int x,int y){
	//竖向较长
	LCD_DrawLine(x,y-star_height/2, x,y+star_height/2);
	//横向较短
	LCD_DrawLine(x-star_width/2,y, x+star_width/2,y);
}

void draw_forward_trigon(int x,int y,int width, int height){
	int x1,y1,x2,y2,x3,y3;
	x1 = x-width/2;	y1 = y;
	x2 = x;	y2 = y - height;
	x3 = x+width/2;	y3 = y;
	
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x2,y2,x3,y3);
}

void draw_reversed_trigon(int x,int y,int width, int height){
	int x1,y1,x2,y2,x3,y3;
	x1 = x-width/2;	y1 = y;
	x2 = x;	y2 = y + height;
	x3 = x+width/2;	y3 = y;
	
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x2,y2,x3,y3);
}

void draw_rectangle(int x, int y, int width, int height){
	int x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = x;
	y1 = y;

	x2 = x + width;
	y2 = y;

	x3 = x1;
	y3 = y + height;

	x4 = x2;
	y4 = y3;

	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x4,y4,x2,y2);
	LCD_DrawLine(x4,y4,x3,y3);
}

void draw_left_triangle(int x, int y, int width, int height){
	int x1, y1, x2, y2, x3, y3;
	x1 = x;
	y1 = y;

	x2 = x - width;
	y2 = y;

	x3 = x;
	y3 = y - height;

	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x2,y2,x3,y3);
}

void draw_right_triangle(int x, int y, int width, int height){
	int x1, y1, x2, y2, x3, y3;
	x1 = x;
	y1 = y;

	x2 = x + width;
	y2 = y;

	x3 = x;
	y3 = y - height;

	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x2,y2,x3,y3);
}

void draw_trapezoid(int x, int y, int upper_width, int lower_width, int height){
	int x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = x - upper_width/2;
	y1 = y;

	x2 = x + upper_width/2;
	y2 = y;

	x3 = x - lower_width/2;
	y3 = y + height;

	x4 = x + lower_width/2;
	y4 = y + height;

	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x4,y4,x2,y2);
	LCD_DrawLine(x4,y4,x3,y3);

}

