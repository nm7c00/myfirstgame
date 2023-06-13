#include <stdio.h>
#include <SDL2/SDL.h>
#include "includes/magic_numbers.h"
#include "includes/errorout.h"
#include "includes/surface_arrays.h"
#include "includes/rect_vessel.h"
#include "methods/object.h"



int main() 
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());

	SDL_Window* window = NULL;
	
	if ((window = SDL_CreateWindow("My window", SDL_WINDOWPOS_UNDEFINED, 
				SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN)) == NULL) 
		ErrorOut(__FILE__, __LINE__, __FUNCTION__, SDL_GetError());



	Object mainmenu = {MainMenuVTable};

	Constructor(&mainmenu, window);

	loadBackgroundSurfaces(&mainmenu);

	loadButtonSurfaces(&mainmenu);

	modifyRectValues(&mainmenu);


	SDL_Texture* mainmenu_texture = SDL_CreateTextureFromSurface(mainmenu.renderer, mainmenu.surface_arrays.BackgroundSurfaces[BACKGROUND]); 
	SDL_RenderCopy(mainmenu.renderer, mainmenu_texture, NULL, &mainmenu.rect_vessel.backgroundRect);
	SDL_RenderPresent(mainmenu.renderer);

	mainmenu_texture = SDL_CreateTextureFromSurface(mainmenu.renderer, mainmenu.surface_arrays.ButtonSurfaces[PLAY_BUTTON_UNCLICKED]); 
	SDL_RenderCopy(mainmenu.renderer, mainmenu_texture, NULL, &mainmenu.rect_vessel.playbuttonRect);
	SDL_RenderPresent(mainmenu.renderer);

	// main menu logic loop //
	int x_mouse = 0;
	int y_mouse = 0;
	SDL_Event event;
	SDL_Texture* button_unclicked = SDL_CreateTextureFromSurface(mainmenu.renderer, 
			mainmenu.surface_arrays.ButtonSurfaces[PLAY_BUTTON_UNCLICKED]); 
	SDL_Texture* button_hover = SDL_CreateTextureFromSurface(mainmenu.renderer, 
			mainmenu.surface_arrays.ButtonSurfaces[PLAY_BUTTON_HOVER]); 
	SDL_Texture* button_click = SDL_CreateTextureFromSurface(mainmenu.renderer, 
			mainmenu.surface_arrays.ButtonSurfaces[PLAY_BUTTON_CLICKED]); 

	while (1)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				goto end_mainmenu_loop;

			SDL_GetGlobalMouseState(&x_mouse, &y_mouse);

			if (x_mouse > 200 && x_mouse < 452 && y_mouse > 243 && y_mouse < 340) 
			{
				SDL_RenderCopy(mainmenu.renderer, button_hover, NULL, &mainmenu.rect_vessel.playbuttonRect);
				SDL_RenderPresent(mainmenu.renderer); 	
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					SDL_RenderCopy(mainmenu.renderer, button_click, NULL, &mainmenu.rect_vessel.playbuttonRect);
					SDL_RenderPresent(mainmenu.renderer);	
					goto end_mainmenu_loop; 
				}
			} else {
				SDL_RenderCopy(mainmenu.renderer, button_unclicked, NULL, &mainmenu.rect_vessel.playbuttonRect);
				SDL_RenderPresent(mainmenu.renderer);	
			}
		}
	}


end_mainmenu_loop:
	Destructor(&mainmenu);	




	/*

	Object mainmenu = {MainMenuVTable};
	
	Constructor(&mainmenu);

	loadBackgroundSurfaces(&mainmenu);

	loadButtonSurfaces(&mainmenu);


	*/




	//Destructor(&mainmenu);





































	/*
  	printf("\n\n%i\n", Destructor(&mainmenu));

  	printf("\n\n%i\n", loadBackgroundSurfaces(&mainmenu));

  	printf("\n\n%i\n", loadBeaconSurfaces(&mainmenu));

  	printf("\n\n%i\n", loadButtonSurfaces(&mainmenu));

  	printf("\n\n%i\n", loadCharacterSurfaces(&mainmenu));

  	printf("\n\n%i\n", modifyRectValues(&mainmenu));


  	printf("\n\n%i\n", Destructor(&levelone));

  	printf("\n\n%i\n", loadBackgroundSurfaces(&levelone));

  	printf("\n\n%i\n", loadBeaconSurfaces(&levelone));

  	printf("\n\n%i\n", loadButtonSurfaces(&levelone));

  	printf("\n\n%i\n", loadCharacterSurfaces(&levelone));

  	printf("\n\n%i\n", modifyRectValues(&levelone));
	*/



	//short int where_next_flag = 1;
	// where_next_flag values //
		/* 0 = quit program
		 * 1 = main menu
		 * 2 = level one */ 


	/*
	while (where_next_flag != 0) 
	{
		if (where_next_flag == 1)
			mainmenu(window, &where_next_flag);
		if (where_next_flag == 2)
			levelone(window, &where_next_flag);
	}
	*/



	// destroy //
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();

	return 0;
}
