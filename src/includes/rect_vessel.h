#ifndef RECT_VESSEL_H_
#define RECT_VESSEL_H_

#include <SDL2/SDL.h>

typedef struct RectVessel {
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
} RectVessel;

#endif
