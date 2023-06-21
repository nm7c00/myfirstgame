#include <SDL2/SDL.h>
#include "object.h"
#include "../includes/magic_numbers.h"
#include "../includes/errorout.h"
#include "../includes/surface_arrays.h"
#include "../list/list.h"

static const void Constructor_v(struct Object* Object, SDL_Window* Window)
{
	// init renderer //
	Object->window = Window;
	if (Object->window == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());

	Object->renderer = SDL_CreateRenderer(Object->window, -1, SDL_RENDERER_ACCELERATED);
	if (Object->renderer == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());

	Object->total_scene_count = 5;
	Object->rect_node = init_level_one_list();
}

static const void Destructor_v(struct Object* Object)
{
	//destroyList(Object->rect_node);

	// free renderer //
	SDL_DestroyRenderer(Object->renderer);
	Object->renderer = NULL;

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

const struct Object_vtable_ LevelOneVTable[] = { { 
		Constructor_v, 
		Destructor_v, 
		loadBackgroundSurfaces_v, 
		loadBeaconSurfaces_v, 
		loadButtonSurfaces_v, 
		loadCharacterSurfaces_v } };
