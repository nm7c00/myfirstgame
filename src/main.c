#include <stdio.h>
#include <SDL2/SDL.h>
#include "includes/magic_numbers.h"
#include "includes/errorout.h"
#include "includes/surface_arrays.h"
#include "includes/rect_vessel.h"
#include "methods/object.h"


/* SDL_Renderer is what puts images on your screen using your gpu.
 * The renderer uses an SDL_Texture and as input.
 * SDL_Texture needs an SDL_Surface to be created.  All SDL_Surface's are 
 * stored, created and destroyed in Object's api (check methods/object.h).  
 * Surfaces are structured as arrays of enums (check 'includes/surface_arrays.h').
 * 
 * SDL_Textures are allocated and destroyed inside of main instead 
 * of Object because SDL does weird things in the background*/

int main() 
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());

	SDL_Window* window = NULL;
	
	if ((window = SDL_CreateWindow("My window", SDL_WINDOWPOS_UNDEFINED, 
				SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN)) == NULL) 
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());



	Object* mainmenu = (Object*)calloc(1, sizeof(Object));

	mainmenu->vtable_ = MainMenuVTable;

	Constructor(mainmenu, window);

	loadBackgroundSurfaces(mainmenu);

	loadButtonSurfaces(mainmenu);

	modifyRectValues(mainmenu);


	SDL_Texture* mainmenu_texture = SDL_CreateTextureFromSurface(mainmenu->renderer, mainmenu->surface_arrays.BackgroundSurfaces[S_BACKGROUND]); 
	SDL_RenderCopy(mainmenu->renderer, mainmenu_texture, NULL, &mainmenu->rect_vessel.backgroundRect);
	SDL_RenderPresent(mainmenu->renderer);

	mainmenu_texture = SDL_CreateTextureFromSurface(mainmenu->renderer, mainmenu->surface_arrays.ButtonSurfaces[S_PLAY_BUTTON_UNCLICKED]); 
	SDL_RenderCopy(mainmenu->renderer, mainmenu_texture, NULL, &mainmenu->rect_vessel.playbuttonRect);
	SDL_RenderPresent(mainmenu->renderer);

	SDL_Texture* button_unclicked = SDL_CreateTextureFromSurface(mainmenu->renderer, 
			mainmenu->surface_arrays.ButtonSurfaces[S_PLAY_BUTTON_UNCLICKED]); 
	SDL_Texture* button_hover = SDL_CreateTextureFromSurface(mainmenu->renderer, 
			mainmenu->surface_arrays.ButtonSurfaces[S_PLAY_BUTTON_HOVER]); 
	SDL_Texture* button_click = SDL_CreateTextureFromSurface(mainmenu->renderer, 
			mainmenu->surface_arrays.ButtonSurfaces[S_PLAY_BUTTON_CLICKED]); 

	// main menu logic loop //
	int x_mouse = 0;
	int y_mouse = 0;
	SDL_Event event;

	while (1)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				goto end_mainmenu_loop;

			SDL_GetGlobalMouseState(&x_mouse, &y_mouse);

			if (x_mouse > 200 && x_mouse < 452 && y_mouse > 243 && y_mouse < 340) 
			{
				SDL_RenderCopy(mainmenu->renderer, button_hover, NULL, &mainmenu->rect_vessel.playbuttonRect);
				SDL_RenderPresent(mainmenu->renderer); 	
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					SDL_RenderCopy(mainmenu->renderer, button_click, NULL, &mainmenu->rect_vessel.playbuttonRect);
					SDL_RenderPresent(mainmenu->renderer);	
					// where_next[foo] = 1;
					goto end_mainmenu_loop; 
				}
			} else {
				SDL_RenderCopy(mainmenu->renderer, button_unclicked, NULL, &mainmenu->rect_vessel.playbuttonRect);
				SDL_RenderPresent(mainmenu->renderer);	
			}
		}
	}


end_mainmenu_loop:
	SDL_DestroyTexture(mainmenu_texture);
	SDL_DestroyTexture(button_unclicked);
	SDL_DestroyTexture(button_hover);
	SDL_DestroyTexture(button_click);
	Destructor(mainmenu);	
	free(mainmenu);


	// implement level one and get EVERYTHING working, then make a level choosing screen
	// calloc where_next enum

	/*
	Object* level = (Object*)calloc(1, sizeof(Object));

	if (where_next[LEVEL_ONE])
		level->vtable_ = LevelOneVTable;	
	else if (where_next[LEVEL_TWO])
		level->vtable_ = LevelTwoVTable;

	*/

	
	Object* level = (Object*)calloc(1, sizeof(Object));

	level->vtable_ = LevelOneVTable;

	Constructor(level, window);

	loadBackgroundSurfaces(level);

	loadCharacterSurfaces(level);

	loadBeaconSurfaces(level);

	modifyRectValues(level);




	

	// character textures //
	SDL_Texture* character_idle_right = SDL_CreateTextureFromSurface(level->renderer, 
			level->surface_arrays.CharacterSurfaces[S_CHARACTER_IDLE_RIGHT]);
	SDL_Texture* character_idle_left = SDL_CreateTextureFromSurface(level->renderer, 
			level->surface_arrays.CharacterSurfaces[S_CHARACTER_IDLE_LEFT]);
	SDL_Texture* character_walking_right = SDL_CreateTextureFromSurface(level->renderer, 
			level->surface_arrays.CharacterSurfaces[S_CHARACTER_WALKING_RIGHT]); 
	SDL_Texture* character_walking_left = SDL_CreateTextureFromSurface(level->renderer, 
			level->surface_arrays.CharacterSurfaces[S_CHARACTER_WALKING_LEFT]); 
	SDL_Texture* character_jumping_right = SDL_CreateTextureFromSurface(level->renderer, 
			level->surface_arrays.CharacterSurfaces[S_CHARACTER_JUMPING_RIGHT]);
	SDL_Texture* character_jumping_left = SDL_CreateTextureFromSurface(level->renderer, 
			level->surface_arrays.CharacterSurfaces[S_CHARACTER_JUMPING_LEFT]);

	// background textures //
	SDL_Texture* background_texture = SDL_CreateTextureFromSurface(level->renderer, level->surface_arrays.BackgroundSurfaces[S_BACKGROUND]); 
	SDL_RenderCopy(level->renderer, background_texture, NULL, &level->rect_vessel.backgroundRect);
	SDL_RenderPresent(level->renderer);

	// beacon textures //
	SDL_Texture* beacon_texture = SDL_CreateTextureFromSurface(level->renderer, level->surface_arrays.BeaconSurfaces[S_SPAWN_NEXT_SCENE_BEACON]);
	SDL_RenderCopy(level->renderer, beacon_texture, NULL, &level->rect_vessel.spawn_next_scene_beacon_Rect);
	SDL_RenderPresent(level->renderer);


	//SDL_Event event;
	int clip_counter = 0;
	SDL_Texture* current_image = NULL;
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	int jump_flag = 0;
	Uint32 animation_timer = SDL_GetTicks();
	Uint32 refresh_timer = SDL_GetTicks();
	SDL_Texture* character_idle_direction = character_idle_right; 
	int current_platform_height = GROUND_HEIGHT;
	int current_jump_height = 0;
	while(1)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
		{
			goto end_game_loop;
		}

		if ((SDL_GetTicks() - refresh_timer) > TWENTY_MILLISECONDS)
		{
			// set the correct texture //
			if (!jump_flag) 
				current_image = character_idle_direction;

			// falling off a cliff? //
			if (!jump_flag && level->rect_vessel.characterRect.y < current_platform_height)
				jump_flag = 2;

			// collision detection //
			if (level->rect_vessel.clipRect.x > level->rect_vessel.box_one_Rect.x && level->rect_vessel.clipRect.x 
					< (level->rect_vessel.box_one_Rect.x + level->rect_vessel.box_one_Rect.w))
				current_platform_height = level->rect_vessel.box_one_Rect.y;
			else
				current_platform_height = GROUND_HEIGHT;
			
			if (level->rect_vessel.clipRect.x > level->rect_vessel.box_two_Rect.x && level->rect_vessel.clipRect.x 
					< (level->rect_vessel.box_two_Rect.x + level->rect_vessel.box_two_Rect.w) && 
					(level->rect_vessel.clipRect.y) <= (level->rect_vessel.box_two_Rect.y + level->rect_vessel.box_two_Rect.h))
				current_platform_height = level->rect_vessel.box_two_Rect.y;
			
			if (level->rect_vessel.clipRect.x > level->rect_vessel.box_three_Rect.x && level->rect_vessel.clipRect.x 
					< (level->rect_vessel.box_three_Rect.x + level->rect_vessel.box_three_Rect.w) && 
					(level->rect_vessel.clipRect.y) <= (level->rect_vessel.box_three_Rect.y + level->rect_vessel.box_three_Rect.h))
				current_platform_height = level->rect_vessel.box_three_Rect.y;

			if (level->rect_vessel.clipRect.x > level->rect_vessel.box_four_Rect.x && level->rect_vessel.clipRect.x 
					< (level->rect_vessel.box_four_Rect.x + level->rect_vessel.box_four_Rect.w) && 
					(level->rect_vessel.clipRect.y) <= (level->rect_vessel.box_four_Rect.y + level->rect_vessel.box_four_Rect.h))
				current_platform_height = level->rect_vessel.box_four_Rect.y;




			// collision response //
			if (character_idle_direction == character_idle_right && level->rect_vessel.clipRect.y > current_platform_height)
			{
				level->rect_vessel.characterRect.x -= CHARACTER_SPEED; 
				level->rect_vessel.clipRect.x -= CHARACTER_SPEED; 
			}
			if (character_idle_direction == character_idle_left && level->rect_vessel.clipRect.y > current_platform_height)
			{
				level->rect_vessel.characterRect.x += CHARACTER_SPEED; 
				level->rect_vessel.clipRect.x += CHARACTER_SPEED; 
			}



			// move right //
			if (keys[SDL_SCANCODE_D])
			{
				(level->rect_vessel.characterRect.y != current_platform_height) ? 
					(current_image = character_jumping_right) : 
					(current_image = character_walking_right);
				character_idle_direction = character_idle_right;

				if (level->rect_vessel.clipRect.x < level->rect_vessel.rightwallRect.x && 
						level->rect_vessel.clipRect.y <= current_platform_height)
				{ 
					level->rect_vessel.characterRect.x += CHARACTER_SPEED; 
					level->rect_vessel.clipRect.x += CHARACTER_SPEED; 
				}
			}

			// move left //
			if (keys[SDL_SCANCODE_A]) 
			{
				(level->rect_vessel.characterRect.y != current_platform_height) ? 
					(current_image = character_jumping_left) : 
					(current_image = character_walking_left);
				character_idle_direction = character_idle_left;

				if (level->rect_vessel.clipRect.x > level->rect_vessel.leftwallRect.x && level->rect_vessel.clipRect.y <= current_platform_height)
				{
					level->rect_vessel.characterRect.x -= CHARACTER_SPEED; 
					level->rect_vessel.clipRect.x -= CHARACTER_SPEED; 
				} 
			}

			// jump? //
			if (!jump_flag && keys[SDL_SCANCODE_W])
			{
				current_jump_height = (current_platform_height - CHARACTER_JUMP_HEIGHT);
				jump_flag++;
			}

			if (jump_flag)
			{
				if (jump_flag == 2)
				{
					level->rect_vessel.characterRect.y += CHARACTER_FALL_SPEED;	
					level->rect_vessel.clipRect.y += CHARACTER_FALL_SPEED;
					if (level->rect_vessel.characterRect.y >= current_platform_height)
						jump_flag = !jump_flag;
					goto render_game;
				}
				level->rect_vessel.characterRect.y -= CHARACTER_JUMP_SPEED;	
				level->rect_vessel.clipRect.y -= CHARACTER_JUMP_SPEED;
				if (level->rect_vessel.characterRect.y < current_jump_height)
				   jump_flag++;	
			}


			if (SDL_HasIntersection(&level->rect_vessel.clipRect, &level->rect_vessel.beacon_clipRect))
			{
				level->rect_vessel.clipRect.x -= RESET_CHARACTER_LOCATION;
				level->rect_vessel.characterRect.x -= RESET_CHARACTER_LOCATION;
				level->rect_vessel.backgroundRect.x -= SCREEN_WIDTH;
				SDL_RenderClear(level->renderer);
				SDL_RenderSetClipRect(level->renderer, &level->rect_vessel.backgroundRect);
				SDL_RenderCopy(level->renderer, background_texture, NULL, &level->rect_vessel.backgroundRect);
				SDL_RenderPresent(level->renderer);	


				// object detection //
				//initPlatforms->next_screen;
				//an array of SDL_Rect*'s is passed instead of each rect one by one
				
				level->rect_vessel.box_one_Rect.x = 225;
				level->rect_vessel.box_one_Rect.y = 300;
				level->rect_vessel.box_one_Rect.w = 125;
				level->rect_vessel.box_one_Rect.h = 25;

				level->rect_vessel.box_two_Rect.x = 360;
				level->rect_vessel.box_two_Rect.y = 195;
				level->rect_vessel.box_two_Rect.w = 125;
				level->rect_vessel.box_two_Rect.h = 25;

				level->rect_vessel.box_three_Rect.x = 175;
				level->rect_vessel.box_three_Rect.y = 155;
				level->rect_vessel.box_three_Rect.w = 125;
				level->rect_vessel.box_three_Rect.h = 25;

				level->rect_vessel.box_four_Rect.x = 65;
				level->rect_vessel.box_four_Rect.y = 120;
				level->rect_vessel.box_four_Rect.w = 125;
				level->rect_vessel.box_four_Rect.h = 40;


				// characters new x and y locations


				/*
				spawn_next_scene_beacon_Rect.x = 1;
				spawn_next_scene_beacon_Rect.y = 1;

				beacon_clipRect.x = 1;
				beacon_clipRect.y = 1;
				*/

			}

			
			render_game:
			if ((SDL_GetTicks() - animation_timer) > ONE_HUNDRED_MILLISECONDS)
			{
				clip_counter++;
				level->rect_vessel.characterRect.x -= CHARACTER_WIDTH;
				level->rect_vessel.spawn_next_scene_beacon_Rect.x -= BEACON_WIDTH;
				animation_timer = SDL_GetTicks();
				if (clip_counter == CLIP_TOTAL) 
				{
					clip_counter = 0;
					level->rect_vessel.characterRect.x = level->rect_vessel.clipRect.x;
					level->rect_vessel.spawn_next_scene_beacon_Rect.x = level->rect_vessel.beacon_clipRect.x;
				} 				
			}

			SDL_RenderCopy(level->renderer, background_texture, NULL, &level->rect_vessel.backgroundRect);

			SDL_RenderSetClipRect(level->renderer, &level->rect_vessel.beacon_clipRect);
			SDL_RenderCopy(level->renderer, beacon_texture, NULL, &level->rect_vessel.spawn_next_scene_beacon_Rect);

			SDL_RenderSetClipRect(level->renderer, &level->rect_vessel.clipRect);
			SDL_RenderCopy(level->renderer, current_image, NULL, &level->rect_vessel.characterRect);

			SDL_RenderPresent(level->renderer);	
			refresh_timer = SDL_GetTicks();
		}
	}



end_game_loop:
	SDL_DestroyTexture(character_idle_left);
	SDL_DestroyTexture(character_idle_right);
	SDL_DestroyTexture(character_walking_left);
	SDL_DestroyTexture(character_walking_right);
	SDL_DestroyTexture(character_jumping_left);
	SDL_DestroyTexture(character_jumping_right);
	SDL_DestroyTexture(background_texture);
	SDL_DestroyTexture(beacon_texture);
	Destructor(level);
	free(level);



	// destroy //
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();

	return 0;
}
