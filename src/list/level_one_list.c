#include "list.h"
#include "../includes/magic_numbers.h"
#include <SDL2/SDL.h>

RectNode* init_level_one_list() 
{
	RectNode* first_node = (RectNode*)calloc(1, sizeof(RectNode));
	
	// first node->//
	first_node->ground_height = 350;

	// background //
	first_node->backgroundRect.w = LEVEL_ONE_MAP_WIDTH;
	first_node->backgroundRect.h = SCREEN_HEIGHT;

	// character rect //
	first_node->characterRect.x = 50;
	first_node->characterRect.y = 350; 
	first_node->characterRect.w = ANIMATION_CLIP_WIDTH;  
	first_node->characterRect.h = CHARACTER_HEIGHT; 

	// clip rect //
	first_node->clipRect.x = 50;
	first_node->clipRect.y = 350; 
	first_node->clipRect.w = CHARACTER_WIDTH; 
	first_node->clipRect.h = CHARACTER_HEIGHT; 

	// left wall rect //
	first_node->leftwallRect.x = LEFT_WALL_X;
	first_node->leftwallRect.y = LEFT_WALL_Y;
	first_node->leftwallRect.w = LEFT_WALL_W;
	first_node->leftwallRect.h = LEFT_WALL_H;

	// right wall rect //
	first_node->rightwallRect.x = RIGHT_WALL_X;
	first_node->rightwallRect.y = RIGHT_WALL_Y;
	first_node->rightwallRect.w = RIGHT_WALL_W;
	first_node->rightwallRect.h = RIGHT_WALL_H; 

	// spawn nect scene beacon rect //
	first_node->spawn_next_scene_beacon_Rect.x = 500;
	first_node->spawn_next_scene_beacon_Rect.y = 350;
	first_node->spawn_next_scene_beacon_Rect.w = ANIMATION_CLIP_WIDTH;
	first_node->spawn_next_scene_beacon_Rect.h = CHARACTER_HEIGHT;

	// beacon clip rect //
	first_node->beacon_clipRect.x = 500;
	first_node->beacon_clipRect.y = 350;
	first_node->beacon_clipRect.w = BEACON_WIDTH;
	first_node->beacon_clipRect.h = BEACON_HEIGHT;



	RectNode* second_node = (RectNode*)calloc(1, sizeof(RectNode));
	first_node->next = second_node;



	// second node->//
	second_node->ground_height = 350;

	// background //
	second_node->backgroundRect.x = -640; 
	second_node->backgroundRect.w = LEVEL_ONE_MAP_WIDTH;
	second_node->backgroundRect.h = SCREEN_HEIGHT;

	// character //
	second_node->characterRect.x = 50;
	second_node->characterRect.y = 350;
	second_node->characterRect.w = ANIMATION_CLIP_WIDTH;  
	second_node->characterRect.h = CHARACTER_HEIGHT; 

	second_node->clipRect.x = 50;
	second_node->clipRect.y = 350;
	second_node->clipRect.w = CHARACTER_WIDTH; 
	second_node->clipRect.h = CHARACTER_HEIGHT; 

	// platforms //
	second_node->box_one_Rect.x = 225;
	second_node->box_one_Rect.y = 300;
	second_node->box_one_Rect.w = 125;
	second_node->box_one_Rect.h = 25;

	second_node->box_two_Rect.x = 360;
	second_node->box_two_Rect.y = 195;
	second_node->box_two_Rect.w = 125;
	second_node->box_two_Rect.h = 25;

	second_node->box_three_Rect.x = 175;
	second_node->box_three_Rect.y = 155;
	second_node->box_three_Rect.w = 125;
	second_node->box_three_Rect.h = 25;

	second_node->box_four_Rect.x = 65;
	second_node->box_four_Rect.y = 120;
	second_node->box_four_Rect.w = 125;
	second_node->box_four_Rect.h = 40;

	// left wall rect //
	second_node->leftwallRect.x = LEFT_WALL_X;
	second_node->leftwallRect.y = LEFT_WALL_Y;
	second_node->leftwallRect.w = LEFT_WALL_W;
	second_node->leftwallRect.h = LEFT_WALL_H;

	// right wall rect //
	second_node->rightwallRect.x = RIGHT_WALL_X;
	second_node->rightwallRect.y = RIGHT_WALL_Y;
	second_node->rightwallRect.w = RIGHT_WALL_W;
	second_node->rightwallRect.h = RIGHT_WALL_H; 

	// beacon //
	second_node->spawn_next_scene_beacon_Rect.x = 115;
	second_node->spawn_next_scene_beacon_Rect.y = 125;
	second_node->spawn_next_scene_beacon_Rect.w = ANIMATION_CLIP_WIDTH;
	second_node->spawn_next_scene_beacon_Rect.h = CHARACTER_HEIGHT;

	second_node->beacon_clipRect.x = 115; 
	second_node->beacon_clipRect.y = 125; 
	second_node->beacon_clipRect.w = BEACON_WIDTH;
	second_node->beacon_clipRect.h = BEACON_HEIGHT;



	RectNode* third_node = (RectNode*)calloc(1, sizeof(RectNode));
	second_node->next = third_node;


	
	// third node->//
	third_node->ground_height = 800;

		// background //
	third_node->backgroundRect.x = -1280; 
	third_node->backgroundRect.w = LEVEL_ONE_MAP_WIDTH;
	third_node->backgroundRect.h = SCREEN_HEIGHT;

	// character //
	third_node->characterRect.x = 70;
	third_node->characterRect.y = 15;
	third_node->characterRect.w = ANIMATION_CLIP_WIDTH;  
	third_node->characterRect.h = CHARACTER_HEIGHT; 

	third_node->clipRect.x = 70;
	third_node->clipRect.y = 15;
	third_node->clipRect.w = CHARACTER_WIDTH; 
	third_node->clipRect.h = CHARACTER_HEIGHT; 

	// platforms //
	third_node->box_one_Rect.x = 215;  
	third_node->box_one_Rect.y = 345;
	third_node->box_one_Rect.w = 500;
	third_node->box_one_Rect.h = 1000;

	third_node->box_two_Rect.x = 35;  
	third_node->box_two_Rect.y = 45;
	third_node->box_two_Rect.w = 120;
	third_node->box_two_Rect.h = 65;

	third_node->box_three_Rect.x = 500;
	third_node->box_three_Rect.y = 325;
	third_node->box_three_Rect.w = 200;
	third_node->box_three_Rect.h = 25;

	third_node->box_four_Rect.x = 0;
	third_node->box_four_Rect.y = 0;
	third_node->box_four_Rect.w = 0;
	third_node->box_four_Rect.h = 0;

	// left wall rect //
	third_node->leftwallRect.x = LEFT_WALL_X;
	third_node->leftwallRect.y = LEFT_WALL_Y;
	third_node->leftwallRect.w = LEFT_WALL_W;
	third_node->leftwallRect.h = LEFT_WALL_H;

	// right wall rect //
	third_node->rightwallRect.x = RIGHT_WALL_X;
	third_node->rightwallRect.y = RIGHT_WALL_Y;
	third_node->rightwallRect.w = RIGHT_WALL_W;
	third_node->rightwallRect.h = RIGHT_WALL_H; 

	// beacon //
	third_node->spawn_next_scene_beacon_Rect.x = 570;
	third_node->spawn_next_scene_beacon_Rect.y = 325;
	third_node->spawn_next_scene_beacon_Rect.w = ANIMATION_CLIP_WIDTH;
	third_node->spawn_next_scene_beacon_Rect.h = CHARACTER_HEIGHT;

	third_node->beacon_clipRect.x = 570; 
	third_node->beacon_clipRect.y = 325; 
	third_node->beacon_clipRect.w = BEACON_WIDTH;
	third_node->beacon_clipRect.h = BEACON_HEIGHT;



	RectNode* fourth_node = (RectNode*)calloc(1, sizeof(RectNode));
	third_node->next = fourth_node;



	// fourth node->//
	fourth_node->ground_height = 800;

	// background //
	fourth_node->backgroundRect.x = -1920; 
	fourth_node->backgroundRect.w = LEVEL_ONE_MAP_WIDTH;
	fourth_node->backgroundRect.h = SCREEN_HEIGHT;

	// character //
	fourth_node->characterRect.x = 70;
	fourth_node->characterRect.y = 15;
	fourth_node->characterRect.w = ANIMATION_CLIP_WIDTH;  
	fourth_node->characterRect.h = CHARACTER_HEIGHT; 

	fourth_node->clipRect.x = 70;
	fourth_node->clipRect.y = 15;
	fourth_node->clipRect.w = CHARACTER_WIDTH; 
	fourth_node->clipRect.h = CHARACTER_HEIGHT; 

	// platforms //
	fourth_node->box_one_Rect.x = 12;  
	fourth_node->box_one_Rect.y = 40;
	fourth_node->box_one_Rect.w = 115;
	fourth_node->box_one_Rect.h = 1000;

	fourth_node->box_two_Rect.x = 200;    
	fourth_node->box_two_Rect.y = 135;
	fourth_node->box_two_Rect.w = 115;
	fourth_node->box_two_Rect.h = 1000;

	fourth_node->box_three_Rect.x = 395; 
	fourth_node->box_three_Rect.y = 320;
	fourth_node->box_three_Rect.w = 600;
	fourth_node->box_three_Rect.h = 1000;

	fourth_node->box_four_Rect.x = 0;
	fourth_node->box_four_Rect.y = 0;
	fourth_node->box_four_Rect.w = 0;
	fourth_node->box_four_Rect.h = 0;

	// left wall rect //
	fourth_node->leftwallRect.x = LEFT_WALL_X;
	fourth_node->leftwallRect.y = LEFT_WALL_Y;
	fourth_node->leftwallRect.w = LEFT_WALL_W;
	fourth_node->leftwallRect.h = LEFT_WALL_H;

	// right wall rect //
	fourth_node->rightwallRect.x = RIGHT_WALL_X;
	fourth_node->rightwallRect.y = RIGHT_WALL_Y;
	fourth_node->rightwallRect.w = RIGHT_WALL_W;
	fourth_node->rightwallRect.h = RIGHT_WALL_H; 

	// beacon //
	fourth_node->spawn_next_scene_beacon_Rect.x = 570;
	fourth_node->spawn_next_scene_beacon_Rect.y = 325;
	fourth_node->spawn_next_scene_beacon_Rect.w = ANIMATION_CLIP_WIDTH;
	fourth_node->spawn_next_scene_beacon_Rect.h = CHARACTER_HEIGHT;

	fourth_node->beacon_clipRect.x = 570; 
	fourth_node->beacon_clipRect.y = 325; 
	fourth_node->beacon_clipRect.w = BEACON_WIDTH;
	fourth_node->beacon_clipRect.h = BEACON_HEIGHT;



	RectNode* fifth_node = (RectNode*)calloc(1, sizeof(RectNode));
	fourth_node->next = fifth_node;



	// fifth node->//
	fifth_node->ground_height = 315;

	// background //
	fifth_node->backgroundRect.x = -2560; 
	fifth_node->backgroundRect.w = LEVEL_ONE_MAP_WIDTH;
	fifth_node->backgroundRect.h = SCREEN_HEIGHT;

	// character //
	fifth_node->characterRect.x = 290;
	fifth_node->characterRect.y = 20;
	fifth_node->characterRect.w = ANIMATION_CLIP_WIDTH;  
	fifth_node->characterRect.h = CHARACTER_HEIGHT; 

	fifth_node->clipRect.x = 290;
	fifth_node->clipRect.y = 20;
	fifth_node->clipRect.w = CHARACTER_WIDTH; 
	fifth_node->clipRect.h = CHARACTER_HEIGHT; 

	// platforms //
	fifth_node->box_one_Rect.x = 0;  
	fifth_node->box_one_Rect.y = 0;
	fifth_node->box_one_Rect.w = 0;
	fifth_node->box_one_Rect.h = 0;

	fifth_node->box_two_Rect.x = 220;    
	fifth_node->box_two_Rect.y = 95;
	fifth_node->box_two_Rect.w = 150;
	fifth_node->box_two_Rect.h = 20;

	fifth_node->box_three_Rect.x = 0;
	fifth_node->box_three_Rect.y = 0;
	fifth_node->box_three_Rect.w = 0;
	fifth_node->box_three_Rect.h = 0;

	fifth_node->box_four_Rect.x = 0;
	fifth_node->box_four_Rect.y = 0;
	fifth_node->box_four_Rect.w = 0;
	fifth_node->box_four_Rect.h = 0;

	// left wall rect //
	fifth_node->leftwallRect.x = LEFT_WALL_X;
	fifth_node->leftwallRect.y = LEFT_WALL_Y;
	fifth_node->leftwallRect.w = LEFT_WALL_W;
	fifth_node->leftwallRect.h = LEFT_WALL_H;

	// right wall rect //
	fifth_node->rightwallRect.x = RIGHT_WALL_X;
	fifth_node->rightwallRect.y = RIGHT_WALL_Y;
	fifth_node->rightwallRect.w = RIGHT_WALL_W;
	fifth_node->rightwallRect.h = RIGHT_WALL_H; 

	// beacon //
	fifth_node->spawn_next_scene_beacon_Rect.x = 570;
	fifth_node->spawn_next_scene_beacon_Rect.y = 315;
	fifth_node->spawn_next_scene_beacon_Rect.w = ANIMATION_CLIP_WIDTH;
	fifth_node->spawn_next_scene_beacon_Rect.h = CHARACTER_HEIGHT;

	fifth_node->beacon_clipRect.x = 570; 
	fifth_node->beacon_clipRect.y = 315; 
	fifth_node->beacon_clipRect.w = BEACON_WIDTH;
	fifth_node->beacon_clipRect.h = BEACON_HEIGHT;
	
	fifth_node->next = first_node;

	return first_node;
}
