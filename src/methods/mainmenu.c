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

	// set coordinance for SDL_Rect's //
	/*
	Object->rect_vessel.backgroundRect.x = 0;
	Object->rect_vessel.backgroundRect.y = 0;
	Object->rect_vessel.backgroundRect.w = Object->surface_arrays.BackgroundSurfaces[BACKGROUND]->w;
	Object->rect_vessel.backgroundRect.h = Object->surface_arrays.BackgroundSurfaces[BACKGROUND]->h;

	Object->rect_vessel.playbuttonRect.x = 200;
	Object->rect_vessel.playbuttonRect.y = 240;
	Object->rect_vessel.playbuttonRect.w = Object->surface_arrays.ButtonSurfaces[PLAY_BUTTON_UNCLICKED]->w;
	Object->rect_vessel.playbuttonRect.h = Object->surface_arrays.ButtonSurfaces[PLAY_BUTTON_UNCLICKED]->h;
	*/
}

static const void Destructor_v(struct Object* Object)
{
	// free renderer and textures //
	SDL_DestroyRenderer(Object->renderer);

	// free surfaces // 
	for (int i = 0; i < BACKGROUND_TOTAL; i++) 
	{
		SDL_FreeSurface(Object->surface_arrays.BackgroundSurfaces[i]);
		Object->surface_arrays.BackgroundSurfaces[i] = NULL;
	}

	for (int i = 0; i < BUTTON_TOTAL; i++) 
	{
		SDL_FreeSurface(Object->surface_arrays.ButtonSurfaces[i]);
		Object->surface_arrays.ButtonSurfaces[i] = NULL;
	}
}

static const void loadBackgroundSurfaces_v(struct Object* Object) 
{
	Object->surface_arrays.BackgroundSurfaces[BACKGROUND] = SDL_LoadBMP("./assets/mainmenu"
			"/BackgroundSurfaces/BACKGROUND.bmp");
	if (Object->surface_arrays.BackgroundSurfaces[BACKGROUND] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());
}

static const void loadBeaconSurfaces_v(struct Object* Object) 
{
	return;
}

static const void loadButtonSurfaces_v(struct Object* Object) 
{
	Object->surface_arrays.ButtonSurfaces[PLAY_BUTTON_UNCLICKED] = SDL_LoadBMP("./assets/mainmenu/"
			"ButtonSurfaces/PLAY_BUTTON_UNCLICKED.bmp");
	if (Object->surface_arrays.ButtonSurfaces[PLAY_BUTTON_UNCLICKED] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());

	Object->surface_arrays.ButtonSurfaces[PLAY_BUTTON_HOVER] = SDL_LoadBMP("./assets/mainmenu/"
			"ButtonSurfaces/PLAY_BUTTON_HOVER.bmp");
	if (Object->surface_arrays.ButtonSurfaces[PLAY_BUTTON_HOVER] == NULL)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());

	Object->surface_arrays.ButtonSurfaces[PLAY_BUTTON_CLICKED] = SDL_LoadBMP("./assets/mainmenu/"
			"ButtonSurfaces/PLAY_BUTTON_CLICKED.bmp");
	if (Object->surface_arrays.ButtonSurfaces[PLAY_BUTTON_CLICKED] == NULL)
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

static const void modifyRectValues_v(struct Object* Object)
{
	Object->rect_vessel.backgroundRect.x = 0;
	Object->rect_vessel.backgroundRect.y = 0;
	Object->rect_vessel.backgroundRect.w = Object->surface_arrays.BackgroundSurfaces[BACKGROUND]->w;
	Object->rect_vessel.backgroundRect.h = Object->surface_arrays.BackgroundSurfaces[BACKGROUND]->h;

	Object->rect_vessel.playbuttonRect.x = 200;
	Object->rect_vessel.playbuttonRect.y = 240;
	Object->rect_vessel.playbuttonRect.w = Object->surface_arrays.ButtonSurfaces[PLAY_BUTTON_UNCLICKED]->w;
	Object->rect_vessel.playbuttonRect.h = Object->surface_arrays.ButtonSurfaces[PLAY_BUTTON_UNCLICKED]->h;
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
