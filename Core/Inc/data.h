#ifndef __DATA_H
#define __DATA_H

#define my_buttle_max 100
#define enemy_buttle_max 300

#define enemy_plane_max 10

struct{
	int start_timestamp;

	int score;

	int score_2;
	int score_3;
	
	int life;
	
	int my_plane[2];
	int my_buttles[my_buttle_max][2];

	int level;
	int boss[2];
	int boss_life;
	
	int enemy_planes[enemy_plane_max][2];
	int enemy_buttles[enemy_buttle_max][2];
}interface;

#endif
