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

	Object->rect_vessel.backgroundRect.w = SCREEN_WIDTH; 
	Object->rect_vessel.backgroundRect.h = SCREEN_HEIGHT; 

	Object->rect_vessel.playbuttonRect.x = PLAY_BUTTON_X;
	Object->rect_vessel.playbuttonRect.y = PLAY_BUTTON_Y;
	Object->rect_vessel.playbuttonRect.w = PLAY_BUTTON_W;
	Object->rect_vessel.playbuttonRect.h = PLAY_BUTTON_H;
}

static const void Destructor_v(struct Object* Object)
{

	// free surfaces // 
	for (int i = 0; i < SURFACE_BACKGROUND_TOTAL; i++) 
	{
		SDL_FreeSurface(Object->surface_arrays.BackgroundSurfaces[i]);
		Object->surface_arrays.BackgroundSurfaces[i] = NULL;
	}

	for (int i = 0; i < SURFACE_BUTTON_TOTAL; i++) 
	{
		SDL_FreeSurface(Object->surface_arrays.ButtonSurfaces[i]);
		Object->surface_arrays.ButtonSurfaces[i] = NULL;
	}

	// free renderer //
	SDL_DestroyRenderer(Object->renderer);
	Object->renderer = NULL;
}

static const void loadBackgroundSurfaces_v(struct Object* Object) 
{
	Object->surface_arrays.BackgroundSurfaces[S_BACKGROUND] = SDL_LoadBMP(
			"./assets/mainmenu/BackgroundSurfaces/BACKGROUND.bmp");
	if (Object->surface_arrays.BackgroundSurfaces[S_BACKGROUND] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());
}

static const void loadBeaconSurfaces_v(struct Object* Object) 
{
	return;
}

static const void loadButtonSurfaces_v(struct Object* Object) 
{
	Object->surface_arrays.ButtonSurfaces[S_PLAY_BUTTON_UNCLICKED] = SDL_LoadBMP(
			"./assets/mainmenu/ButtonSurfaces/PLAY_BUTTON_UNCLICKED.bmp");
	if (Object->surface_arrays.ButtonSurfaces[S_PLAY_BUTTON_UNCLICKED] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());

	Object->surface_arrays.ButtonSurfaces[S_PLAY_BUTTON_HOVER] = SDL_LoadBMP(
			"./assets/mainmenu/ButtonSurfaces/PLAY_BUTTON_HOVER.bmp");
	if (Object->surface_arrays.ButtonSurfaces[S_PLAY_BUTTON_HOVER] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());

	Object->surface_arrays.ButtonSurfaces[S_PLAY_BUTTON_CLICKED] = SDL_LoadBMP(
			"./assets/mainmenu/ButtonSurfaces/PLAY_BUTTON_CLICKED.bmp");
	if (Object->surface_arrays.ButtonSurfaces[S_PLAY_BUTTON_CLICKED] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());
}

static const void loadCharacterSurfaces_v(struct Object* Object) 
{
	return;
}

static const void loadEnemySurfaces_v(struct Object* Object) 
{
	return;
}

static const void modifyRectValues_v(struct Object* Object, int* scene_counter, int* ground_height)
{
	return;
}

const struct Object_vtable_ MainMenuVTable[] = { { 
		Constructor_v, 
		Destructor_v, 
		loadBackgroundSurfaces_v, 
		loadBeaconSurfaces_v, 
		loadButtonSurfaces_v, 
		loadCharacterSurfaces_v, 
		loadEnemySurfaces_v, 
		modifyRectValues_v } };
