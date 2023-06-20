#include <stdio.h>
#include <SDL2/SDL.h>
#include "includes/magic_numbers.h"
#include "includes/errorout.h"
#include "includes/surface_arrays.h"
#include "list/list.h"
#include "object/object.h"

// Notes //
/* SDL_Renderer is what puts images on your screen using your gpu.
 * First you attach an image to an SDL_Surface, then you use the 
 * SDL_Surface to make an SDL_Texture;  Now the renderer can use 
 * your texture to put an image on the screen using SDL_RenderCopy()
 * then SDL_RenderPresent().
 *
 * All SDL_Surface's are created and destroyed in 'Object's api (check object/object.h).  
 * Surfaces are stored as arrays of enums (check 'includes/surface_arrays.h').
 * Creating my Object using calloc allows me to zero out all of the variables.
 * Which means all SDL_Rect's will spawn in the upper left corner of the screen,
 * with a width and height of 0 so they are out of the way until you need them.
 * 
 * SDL_Textures are created and destroyed inside of main because I think it
 * makes life easier. */

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

	SDL_Texture* mainmenu_texture = SDL_CreateTextureFromSurface(mainmenu->renderer, mainmenu->surface_arrays.BackgroundSurfaces[S_BACKGROUND]); 
	SDL_RenderCopy(mainmenu->renderer, mainmenu_texture, NULL, &mainmenu->rect_node->backgroundRect);
	SDL_RenderPresent(mainmenu->renderer);

	mainmenu_texture = SDL_CreateTextureFromSurface(mainmenu->renderer, mainmenu->surface_arrays.ButtonSurfaces[S_PLAY_BUTTON_UNCLICKED]); 
	SDL_RenderCopy(mainmenu->renderer, mainmenu_texture, NULL, &mainmenu->rect_node->playbuttonRect);
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
	SDL_Event event; // event is reused for the game loop 
	int quit_flag = 0; 
	while (1)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit_flag++;
				goto end_mainmenu_loop;
			}

			SDL_GetGlobalMouseState(&x_mouse, &y_mouse);

			if (x_mouse > PLAY_BUTTON_X && x_mouse < (PLAY_BUTTON_X + PLAY_BUTTON_W) && 
					y_mouse > PLAY_BUTTON_Y && y_mouse < (PLAY_BUTTON_Y + PLAY_BUTTON_H)) 
			{
				SDL_RenderCopy(mainmenu->renderer, button_hover, NULL, &mainmenu->rect_node->playbuttonRect);
				SDL_RenderPresent(mainmenu->renderer); 	
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					SDL_RenderCopy(mainmenu->renderer, button_click, NULL, &mainmenu->rect_node->playbuttonRect);
					SDL_RenderPresent(mainmenu->renderer);	
					goto end_mainmenu_loop; 
				}
			} else {
				SDL_RenderCopy(mainmenu->renderer, button_unclicked, NULL, &mainmenu->rect_node->playbuttonRect);
				SDL_RenderPresent(mainmenu->renderer);	
			}
		}
	}


end_mainmenu_loop:
	free(mainmenu->rect_node);
	SDL_DestroyTexture(mainmenu_texture);
	SDL_DestroyTexture(button_unclicked);
	SDL_DestroyTexture(button_hover);
	SDL_DestroyTexture(button_click);
	Destructor(mainmenu);	
	free(mainmenu);

	if (quit_flag)
		goto end_program;

	/*
	 * calloc where_next enum 
	Object* level = (Object*)calloc(1, sizeof(Object));

	if (where_next[LEVEL_ONE])
		level->vtable_ = LevelOneVTable;	
	else if (where_next[LEVEL_TWO])
		level->vtable_ = LevelTwoVTable;

	*/

	// init game loop //	
	Object* level = (Object*)calloc(1, sizeof(Object));

	level->vtable_ = LevelOneVTable;

	Constructor(level, window);

	loadBackgroundSurfaces(level);

	loadBeaconSurfaces(level);

	loadCharacterSurfaces(level);

	// background textures //
	SDL_Texture* background_texture = SDL_CreateTextureFromSurface(level->renderer, level->surface_arrays.BackgroundSurfaces[S_BACKGROUND]); 
	SDL_RenderCopy(level->renderer, background_texture, NULL, &level->rect_node->backgroundRect);
	SDL_RenderPresent(level->renderer);

	// beacon textures //
	SDL_Texture* beacon_texture = SDL_CreateTextureFromSurface(level->renderer, level->surface_arrays.BeaconSurfaces[S_SPAWN_NEXT_SCENE_BEACON]);
	SDL_RenderCopy(level->renderer, beacon_texture, NULL, &level->rect_node->spawn_next_scene_beacon_Rect);
	SDL_RenderPresent(level->renderer);

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

	// game loop //
	int clip_counter = 0;

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	Uint32 animation_timer = SDL_GetTicks();
	Uint32 refresh_timer = SDL_GetTicks();

	SDL_Texture* current_image = NULL;
	SDL_Texture* character_idle_direction = character_idle_right; 

	int current_platform_height = level->rect_node->ground_height;
	int jump_flag = 0;
	int current_jump_height = 0;
	while(1)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
		{
			goto destroy_and_quit;
		}

		if ((SDL_GetTicks() - refresh_timer) > TWENTY_FIVE_TICKS)
		{
			// set the correct character texture (left vs right) //
			if (!jump_flag) 
				current_image = character_idle_direction;

			// falling off a cliff? //
			if (!jump_flag && level->rect_node->characterRect.y < current_platform_height)
				jump_flag = 2;

			// fall to your death? //
			if (level->rect_node->clipRect.y > CHARACTER_DEATH_FALL)
				goto destroy_and_quit; // youDied_v() 


			// collision detection //
			if (level->rect_node->clipRect.x > level->rect_node->box_one_Rect.x && level->rect_node->clipRect.x 
					< (level->rect_node->box_one_Rect.x + level->rect_node->box_one_Rect.w))
				current_platform_height = level->rect_node->box_one_Rect.y;
			else
				current_platform_height = level->rect_node->ground_height;

			if (level->rect_node->clipRect.x > level->rect_node->box_two_Rect.x && level->rect_node->clipRect.x 
					< (level->rect_node->box_two_Rect.x + level->rect_node->box_two_Rect.w) && 
					(level->rect_node->clipRect.y) <= (level->rect_node->box_two_Rect.y + level->rect_node->box_two_Rect.h))
				current_platform_height = level->rect_node->box_two_Rect.y;
			
			if (level->rect_node->clipRect.x > level->rect_node->box_three_Rect.x && level->rect_node->clipRect.x 
					< (level->rect_node->box_three_Rect.x + level->rect_node->box_three_Rect.w) && 
					(level->rect_node->clipRect.y) <= (level->rect_node->box_three_Rect.y + level->rect_node->box_three_Rect.h))
				current_platform_height = level->rect_node->box_three_Rect.y;

			if (level->rect_node->clipRect.x > level->rect_node->box_four_Rect.x && level->rect_node->clipRect.x 
					< (level->rect_node->box_four_Rect.x + level->rect_node->box_four_Rect.w) && 
					(level->rect_node->clipRect.y) <= (level->rect_node->box_four_Rect.y + level->rect_node->box_four_Rect.h))
				current_platform_height = level->rect_node->box_four_Rect.y;


			// collision response //
			if (character_idle_direction == character_idle_right && level->rect_node->clipRect.y > current_platform_height)
			{
				level->rect_node->characterRect.x -= CHARACTER_SPEED; 
				level->rect_node->clipRect.x -= CHARACTER_SPEED; 
			}
			if (character_idle_direction == character_idle_left && level->rect_node->clipRect.y > current_platform_height)
			{
				level->rect_node->characterRect.x += CHARACTER_SPEED; 
				level->rect_node->clipRect.x += CHARACTER_SPEED; 
			}


			// move right //
			if (keys[SDL_SCANCODE_D])
			{
				(level->rect_node->characterRect.y != current_platform_height) ? 
					(current_image = character_jumping_right) : 
					(current_image = character_walking_right);
				character_idle_direction = character_idle_right;

				if (level->rect_node->clipRect.x < level->rect_node->rightwallRect.x && 
						level->rect_node->clipRect.y <= current_platform_height)
				{ 
					level->rect_node->characterRect.x += CHARACTER_SPEED; 
					level->rect_node->clipRect.x += CHARACTER_SPEED; 
				}
			}

			// move left //
			if (keys[SDL_SCANCODE_A]) 
			{
				(level->rect_node->characterRect.y != current_platform_height) ? 
					(current_image = character_jumping_left) : 
					(current_image = character_walking_left);
				character_idle_direction = character_idle_left;

				if (level->rect_node->clipRect.x > level->rect_node->leftwallRect.x && 
						level->rect_node->clipRect.y <= current_platform_height)
				{
					level->rect_node->characterRect.x -= CHARACTER_SPEED; 
					level->rect_node->clipRect.x -= CHARACTER_SPEED; 
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
					level->rect_node->characterRect.y += CHARACTER_FALL_SPEED;	
					level->rect_node->clipRect.y += CHARACTER_FALL_SPEED;
					if (level->rect_node->characterRect.y >= current_platform_height)
						jump_flag = !jump_flag;
					goto render_game;
				}
				level->rect_node->characterRect.y -= CHARACTER_JUMP_SPEED;	
				level->rect_node->clipRect.y -= CHARACTER_JUMP_SPEED;
				if (level->rect_node->characterRect.y < current_jump_height)
				   jump_flag++;	
			}

			// spawn next scene? //
			if (SDL_HasIntersection(&level->rect_node->clipRect, &level->rect_node->beacon_clipRect))
			{
				level->scene_counter++;
				if (level->scene_counter == level->total_scene_count)
					goto destroy_and_quit;
				level->rect_node = level->rect_node->next;

				SDL_RenderClear(level->renderer);
				SDL_RenderSetClipRect(level->renderer, &level->rect_node->backgroundRect);
				SDL_RenderCopy(level->renderer, background_texture, NULL, &level->rect_node->backgroundRect);
				SDL_RenderPresent(level->renderer);	
			}
			
render_game:
			if ((SDL_GetTicks() - animation_timer) > ONE_HUNDRED_FIFTY_TICKS)
			{
				clip_counter++;
				level->rect_node->characterRect.x -= CHARACTER_WIDTH;
				level->rect_node->spawn_next_scene_beacon_Rect.x -= BEACON_WIDTH;
				animation_timer = SDL_GetTicks();
				if (clip_counter == CLIP_TOTAL) 
				{
					clip_counter = 0;
					level->rect_node->characterRect.x = level->rect_node->clipRect.x;
					level->rect_node->spawn_next_scene_beacon_Rect.x = level->rect_node->beacon_clipRect.x;
				} 				
			}

			SDL_RenderCopy(level->renderer, background_texture, NULL, &level->rect_node->backgroundRect);

			SDL_RenderSetClipRect(level->renderer, &level->rect_node->beacon_clipRect);
			SDL_RenderCopy(level->renderer, beacon_texture, NULL, &level->rect_node->spawn_next_scene_beacon_Rect);

			SDL_RenderSetClipRect(level->renderer, &level->rect_node->clipRect);
			SDL_RenderCopy(level->renderer, current_image, NULL, &level->rect_node->characterRect);

			SDL_RenderPresent(level->renderer);	
			refresh_timer = SDL_GetTicks();
		}
	}



destroy_and_quit:
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



end_program:
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();

	return 0;
}
