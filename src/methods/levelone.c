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
	Object->rect_vessel.backgroundRect.w = LEVEL_ONE_MAP_WIDTH;
	Object->rect_vessel.backgroundRect.h = SCREEN_HEIGHT;

	// character rect //
	Object->rect_vessel.characterRect.x = 50;
	Object->rect_vessel.characterRect.y = 350; 
	Object->rect_vessel.characterRect.w = ANIMATION_CLIP_WIDTH;  
	Object->rect_vessel.characterRect.h = CHARACTER_HEIGHT; 

	// clip rect //
	Object->rect_vessel.clipRect.x = 50;
	Object->rect_vessel.clipRect.y = 350; 
	Object->rect_vessel.clipRect.w = CHARACTER_WIDTH; 
	Object->rect_vessel.clipRect.h = CHARACTER_HEIGHT; 

	// left wall rect //
	Object->rect_vessel.leftwallRect.x = LEFT_WALL_X;
	Object->rect_vessel.leftwallRect.y = LEFT_WALL_Y;
	Object->rect_vessel.leftwallRect.w = LEFT_WALL_W;
	Object->rect_vessel.leftwallRect.h = LEFT_WALL_H;

	// right wall rect //
	Object->rect_vessel.rightwallRect.x = RIGHT_WALL_X;
	Object->rect_vessel.rightwallRect.y = RIGHT_WALL_Y;
	Object->rect_vessel.rightwallRect.w = RIGHT_WALL_W;
	Object->rect_vessel.rightwallRect.h = RIGHT_WALL_H; 

	// spawn nect scene beacon rect //
	Object->rect_vessel.spawn_next_scene_beacon_Rect.x = 500;
	Object->rect_vessel.spawn_next_scene_beacon_Rect.y = 350;
	Object->rect_vessel.spawn_next_scene_beacon_Rect.w = ANIMATION_CLIP_WIDTH;
	Object->rect_vessel.spawn_next_scene_beacon_Rect.h = CHARACTER_HEIGHT;

	// beacon clip rect //
	Object->rect_vessel.beacon_clipRect.x = 500;
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

static const void modifyRectValues_v(struct Object* Object, int* scene_counter, int* ground_height)
{
	/* Scenes are indexed starting at zero like an array.
	   Scene zero rect values are initialized in Constructer(). */
	if ((*scene_counter) == 1)
	{
		(*ground_height) = 350;

		// background //
		Object->rect_vessel.backgroundRect.x -= SCREEN_WIDTH; 

		// character //
		Object->rect_vessel.characterRect.x = 50;
		Object->rect_vessel.characterRect.y = 350;

		Object->rect_vessel.clipRect.x = 50;
		Object->rect_vessel.clipRect.y = 350;

		// platforms //
		Object->rect_vessel.box_one_Rect.x = 225;
		Object->rect_vessel.box_one_Rect.y = 300;
		Object->rect_vessel.box_one_Rect.w = 125;
		Object->rect_vessel.box_one_Rect.h = 25;

		Object->rect_vessel.box_two_Rect.x = 360;
		Object->rect_vessel.box_two_Rect.y = 195;
		Object->rect_vessel.box_two_Rect.w = 125;
		Object->rect_vessel.box_two_Rect.h = 25;

		Object->rect_vessel.box_three_Rect.x = 175;
		Object->rect_vessel.box_three_Rect.y = 155;
		Object->rect_vessel.box_three_Rect.w = 125;
		Object->rect_vessel.box_three_Rect.h = 25;

		Object->rect_vessel.box_four_Rect.x = 65;
		Object->rect_vessel.box_four_Rect.y = 120;
		Object->rect_vessel.box_four_Rect.w = 125;
		Object->rect_vessel.box_four_Rect.h = 40;

		// beacon //
		Object->rect_vessel.spawn_next_scene_beacon_Rect.x = 115;
		Object->rect_vessel.spawn_next_scene_beacon_Rect.y = 125;

		Object->rect_vessel.beacon_clipRect.x = 115; 
		Object->rect_vessel.beacon_clipRect.y = 125; 
	}

	if ((*scene_counter) == 2)
	{
		(*ground_height) = 800;

		// background //
		Object->rect_vessel.backgroundRect.x -= SCREEN_WIDTH; 

		// character //
		Object->rect_vessel.characterRect.x = 70;
		Object->rect_vessel.characterRect.y = 15;

		Object->rect_vessel.clipRect.x = 70;
		Object->rect_vessel.clipRect.y = 15;

		// platforms //
		Object->rect_vessel.box_one_Rect.x = 215;  
		Object->rect_vessel.box_one_Rect.y = 345;
		Object->rect_vessel.box_one_Rect.w = 500;
		Object->rect_vessel.box_one_Rect.h = 1000;

		Object->rect_vessel.box_two_Rect.x = 35;  
		Object->rect_vessel.box_two_Rect.y = 45;
		Object->rect_vessel.box_two_Rect.w = 120;
		Object->rect_vessel.box_two_Rect.h = 65;

		Object->rect_vessel.box_three_Rect.x = 500;
		Object->rect_vessel.box_three_Rect.y = 325;
		Object->rect_vessel.box_three_Rect.w = 200;
		Object->rect_vessel.box_three_Rect.h = 25;

		Object->rect_vessel.box_four_Rect.x = 0;
		Object->rect_vessel.box_four_Rect.y = 0;
		Object->rect_vessel.box_four_Rect.w = 0;
		Object->rect_vessel.box_four_Rect.h = 0;

		// beacon //
		Object->rect_vessel.spawn_next_scene_beacon_Rect.x = 570;
		Object->rect_vessel.spawn_next_scene_beacon_Rect.y = 325;

		Object->rect_vessel.beacon_clipRect.x = 570; 
		Object->rect_vessel.beacon_clipRect.y = 325; 
	}

	if ((*scene_counter) == 3)
	{
		(*ground_height) = 800;

		// background //
		Object->rect_vessel.backgroundRect.x -= SCREEN_WIDTH; 

		// character //
		Object->rect_vessel.characterRect.x = 70;
		Object->rect_vessel.characterRect.y = 15;

		Object->rect_vessel.clipRect.x = 70;
		Object->rect_vessel.clipRect.y = 15;

		// platforms //
		Object->rect_vessel.box_one_Rect.x = 12;  
		Object->rect_vessel.box_one_Rect.y = 40;
		Object->rect_vessel.box_one_Rect.w = 115;
		Object->rect_vessel.box_one_Rect.h = 1000;

		Object->rect_vessel.box_two_Rect.x = 200;    
		Object->rect_vessel.box_two_Rect.y = 135;
		Object->rect_vessel.box_two_Rect.w = 115;
		Object->rect_vessel.box_two_Rect.h = 1000;

		Object->rect_vessel.box_three_Rect.x = 395; 
		Object->rect_vessel.box_three_Rect.y = 320;
		Object->rect_vessel.box_three_Rect.w = 600;
		Object->rect_vessel.box_three_Rect.h = 1000;

		Object->rect_vessel.box_four_Rect.x = 0;
		Object->rect_vessel.box_four_Rect.y = 0;
		Object->rect_vessel.box_four_Rect.w = 0;
		Object->rect_vessel.box_four_Rect.h = 0;

		// beacon //
		Object->rect_vessel.spawn_next_scene_beacon_Rect.x = 570;
		Object->rect_vessel.spawn_next_scene_beacon_Rect.y = 325;

		Object->rect_vessel.beacon_clipRect.x = 570; 
		Object->rect_vessel.beacon_clipRect.y = 325; 
	}

	if ((*scene_counter) == 4)
	{
		(*ground_height) = 315;

		// background //
		Object->rect_vessel.backgroundRect.x -= SCREEN_WIDTH; 

		// character //
		Object->rect_vessel.characterRect.x = 250;
		Object->rect_vessel.characterRect.y = 20;

		Object->rect_vessel.clipRect.x = 250;
		Object->rect_vessel.clipRect.y = 20;

		// platforms //
		Object->rect_vessel.box_one_Rect.x = 0;  
		Object->rect_vessel.box_one_Rect.y = 0;
		Object->rect_vessel.box_one_Rect.w = 0;
		Object->rect_vessel.box_one_Rect.h = 0;

		Object->rect_vessel.box_two_Rect.x = 220;    
		Object->rect_vessel.box_two_Rect.y = 95;
		Object->rect_vessel.box_two_Rect.w = 150;
		Object->rect_vessel.box_two_Rect.h = 20;

		Object->rect_vessel.box_three_Rect.x = 0;
		Object->rect_vessel.box_three_Rect.y = 0;
		Object->rect_vessel.box_three_Rect.w = 0;
		Object->rect_vessel.box_three_Rect.h = 0;

		Object->rect_vessel.box_four_Rect.x = 0;
		Object->rect_vessel.box_four_Rect.y = 0;
		Object->rect_vessel.box_four_Rect.w = 0;
		Object->rect_vessel.box_four_Rect.h = 0;

		// beacon //
		Object->rect_vessel.spawn_next_scene_beacon_Rect.x = 570;
		Object->rect_vessel.spawn_next_scene_beacon_Rect.y = 315;

		Object->rect_vessel.beacon_clipRect.x = 570; 
		Object->rect_vessel.beacon_clipRect.y = 315; 
	}
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
