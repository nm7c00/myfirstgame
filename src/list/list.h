#ifndef LIST_H_
#define LIST_H_

/* lists are statically created to set the values 
 * of the SDL_Rect values for each scene.  Each
 * list init() returns a pointer to the first node */

#include <SDL2/SDL.h>

typedef struct RectNode {
	struct RectNode* next;

	int ground_height;	

	// background //
	SDL_Rect backgroundRect;

	// button //
	SDL_Rect playbuttonRect;

	// character //
	SDL_Rect characterRect;
	SDL_Rect clipRect;

	// walls //
	SDL_Rect leftwallRect;
	SDL_Rect rightwallRect;

	// platforms //
	SDL_Rect box_one_Rect;
	SDL_Rect box_two_Rect;
	SDL_Rect box_three_Rect;
	SDL_Rect box_four_Rect;

	// beacon //
	SDL_Rect spawn_next_scene_beacon_Rect;
	SDL_Rect beacon_clipRect; 
} RectNode;

RectNode* init_level_one_list();

RectNode* init_main_menu_list();

void destroyList(RectNode* node);

#endif
