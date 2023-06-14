#include <SDL2/SDL.h>
#include "object.h"
#include "../includes/magic_numbers.h"
#include "../includes/errorout.h"
#include "../includes/rect_vessel.h"
#include "../includes/surface_arrays.h"

static const void Constructor_v(struct Object* Object, SDL_Window* Window)
{
	// init renderer //
	Object->window = Window;
	if (Object->window == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());

	Object->renderer = SDL_CreateRenderer(Object->window, -1, SDL_RENDERER_ACCELERATED);
	if (Object->renderer == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());


	/* Because Object is calloc'd into existence, all SDL_Rect's 
	 * will default to the top left corner of the screen.  */
	Object->rect_vessel.backgroundRect.w = 3200;
	Object->rect_vessel.backgroundRect.h = 480;

	// character rect //
	Object->rect_vessel.characterRect.x = 150;
	Object->rect_vessel.characterRect.y = 350; 
	Object->rect_vessel.characterRect.w = CHARACTER_WIDTH;  
	Object->rect_vessel.characterRect.h = CHARACTER_HEIGHT; 

	// clip rect //
	Object->rect_vessel.clipRect.x = 150;
	Object->rect_vessel.clipRect.y = 350; 
	Object->rect_vessel.clipRect.w = CHARACTER_WIDTH; 
	Object->rect_vessel.clipRect.h = CHARACTER_HEIGHT; 

	// left wall rect //
	Object->rect_vessel.leftwallRect.x = 1;
	Object->rect_vessel.leftwallRect.y = 1;
	Object->rect_vessel.leftwallRect.w = 1;
	Object->rect_vessel.leftwallRect.h = SCREEN_HEIGHT;

	// right wall rect //
	Object->rect_vessel.rightwallRect.x = 490;
	Object->rect_vessel.rightwallRect.y = 1;
	Object->rect_vessel.rightwallRect.w = SCREEN_WIDTH;
	Object->rect_vessel.rightwallRect.h = SCREEN_HEIGHT; 

	// spawn nect scene beacon rect //
	Object->rect_vessel.spawn_next_scene_beacon_Rect.x = 400;
	Object->rect_vessel.spawn_next_scene_beacon_Rect.y = 350;
	Object->rect_vessel.spawn_next_scene_beacon_Rect.w = BEACON_WIDTH;
	Object->rect_vessel.spawn_next_scene_beacon_Rect.h = BEACON_HEIGHT;

	// beacon clip rect //
	Object->rect_vessel.beacon_clipRect.x = 400;
	Object->rect_vessel.beacon_clipRect.y = 350;
	Object->rect_vessel.beacon_clipRect.w = BEACON_WIDTH;
	Object->rect_vessel.beacon_clipRect.h = BEACON_HEIGHT;
}

static const void Destructor_v(struct Object* Object)
{

	// free surfaces // 
	for (int i = 0; i < SURFACE_BACKGROUND_TOTAL; i++) 
	{
		SDL_FreeSurface(Object->surface_arrays.BackgroundSurfaces[i]);
		Object->surface_arrays.BackgroundSurfaces[i] = NULL;
	}

	for (int i = 0; i < SURFACE_BEACON_TOTAL; i++)
	{
		SDL_FreeSurface(Object->surface_arrays.BeaconSurfaces[i]);
		Object->surface_arrays.BeaconSurfaces[i] = NULL;
	}

	for (int i = 0; i < SURFACE_CHARACTER_TOTAL; i++)
	{
		SDL_FreeSurface(Object->surface_arrays.CharacterSurfaces[i]);
		Object->surface_arrays.CharacterSurfaces[i] = NULL;
	}

	// free renderer //
	SDL_DestroyRenderer(Object->renderer);
	Object->renderer = NULL;
}

static const void loadBackgroundSurfaces_v(struct Object* Object) 
{
	Object->surface_arrays.BackgroundSurfaces[S_BACKGROUND] = SDL_LoadBMP(
			"./assets/levelone/BackgroundSurfaces/BACKGROUND.bmp");
	if (Object->surface_arrays.BackgroundSurfaces[S_BACKGROUND] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());
}

static const void loadBeaconSurfaces_v(struct Object* Object) 
{
	Object->surface_arrays.BeaconSurfaces[S_SPAWN_NEXT_SCENE_BEACON] = SDL_LoadBMP(
			"./assets/levelone/BeaconSurfaces/SPAWN_NEXT_SCENE_BEACON.bmp");
	if (Object->surface_arrays.BeaconSurfaces[S_SPAWN_NEXT_SCENE_BEACON] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());
}

static const void loadButtonSurfaces_v(struct Object* Object) 
{
	return;
}

static const void loadCharacterSurfaces_v(struct Object* Object) 
{
	Object->surface_arrays.CharacterSurfaces[S_CHARACTER_IDLE_RIGHT] = SDL_LoadBMP(
			"./assets/levelone/CharacterSurfaces/CHARACTER_IDLE_RIGHT.bmp");
	if (Object->surface_arrays.CharacterSurfaces[S_CHARACTER_IDLE_RIGHT] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());
	Object->surface_arrays.CharacterSurfaces[S_CHARACTER_IDLE_LEFT] = SDL_LoadBMP(
			"./assets/levelone/CharacterSurfaces/CHARACTER_IDLE_LEFT.bmp");
	if (Object->surface_arrays.CharacterSurfaces[S_CHARACTER_IDLE_LEFT] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());

	Object->surface_arrays.CharacterSurfaces[S_CHARACTER_WALKING_RIGHT] = SDL_LoadBMP(
			"./assets/levelone/CharacterSurfaces/CHARACTER_WALKING_RIGHT.bmp");
	if (Object->surface_arrays.CharacterSurfaces[S_CHARACTER_WALKING_RIGHT] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());
	Object->surface_arrays.CharacterSurfaces[S_CHARACTER_WALKING_LEFT] = SDL_LoadBMP(
			"./assets/levelone/CharacterSurfaces/CHARACTER_WALKING_LEFT.bmp");
	if (Object->surface_arrays.CharacterSurfaces[S_CHARACTER_WALKING_LEFT] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());

	Object->surface_arrays.CharacterSurfaces[S_CHARACTER_JUMPING_RIGHT] = SDL_LoadBMP(
			"./assets/levelone/CharacterSurfaces/CHARACTER_JUMPING_RIGHT.bmp");
	if (Object->surface_arrays.CharacterSurfaces[S_CHARACTER_JUMPING_RIGHT] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());
	Object->surface_arrays.CharacterSurfaces[S_CHARACTER_JUMPING_LEFT] = SDL_LoadBMP(
			"./assets/levelone/CharacterSurfaces/CHARACTER_JUMPING_LEFT.bmp");
	if (Object->surface_arrays.CharacterSurfaces[S_CHARACTER_JUMPING_LEFT] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());
}

static const void loadEnemySurfaces_v(struct Object* Object) 
{
	return;
}

static const void modifyRectValues_v(struct Object* Object)
{
	return;
}

const struct Object_vtable_ LevelOneVTable[] = { { 
		Constructor_v, 
		Destructor_v, 
		loadBackgroundSurfaces_v, 
		loadBeaconSurfaces_v, 
		loadButtonSurfaces_v, 
		loadCharacterSurfaces_v, 
		loadEnemySurfaces_v, 
		modifyRectValues_v } };
