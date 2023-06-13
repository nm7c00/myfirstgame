#ifndef SURFACE_ARRAYS_H_
#define SURFACE_ARRAYS_H_


#include <SDL2/SDL.h>

enum BackgroundSurfaces 
{
	BACKGROUND,
	BACKGROUND_TOTAL	
};

enum BeaconSurfaces
{
	SPAWN_NEXT_SCENE_BEACON,
	BEACON_TOTAL
};

enum ButtonSurfaces
{
	PLAY_BUTTON_UNCLICKED,
	PLAY_BUTTON_HOVER,
	PLAY_BUTTON_CLICKED,
	BUTTON_TOTAL
};

enum CharacterSurfaces 
{
	CHARACTER_IDLE_RIGHT,
	CHARACTER_IDLE_LEFT,
	CHARACTER_WALKING_RIGHT,
	CHARACTER_WALKING_LEFT,
	CHARACTER_JUMPING_RIGHT,
	CHARACTER_JUMPING_LEFT, 
	CHARACTER_TOTAL
};


typedef struct SurfaceArrays {
	SDL_Surface* BackgroundSurfaces[BACKGROUND_TOTAL]; 
	SDL_Surface* BeaconSurfaces[BEACON_TOTAL];
	SDL_Surface* ButtonSurfaces[BUTTON_TOTAL];
	SDL_Surface* CharacterSurfaces[CHARACTER_TOTAL]; 
} SurfaceArrays;


#endif
