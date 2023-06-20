#include "list.h"
#include "../includes/magic_numbers.h"
#include <SDL2/SDL.h>

RectNode* init_main_menu_list() 
{
	RectNode* node = (RectNode*)calloc(1, sizeof(RectNode));
	node->next = NULL;

	node->backgroundRect.w = SCREEN_WIDTH; 
	node->backgroundRect.h = SCREEN_HEIGHT; 

	node->playbuttonRect.x = PLAY_BUTTON_X;
	node->playbuttonRect.y = PLAY_BUTTON_Y;
	node->playbuttonRect.w = PLAY_BUTTON_W;
	node->playbuttonRect.h = PLAY_BUTTON_H;

	return node;
}
