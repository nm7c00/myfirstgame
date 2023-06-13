#include <SDL2/SDL.h>
#include "object.h"
#include "../includes/magic_numbers.h"
#include "../includes/errorout.h"
#include "../includes/rect_vessel.h"

static const void Constructor_v(struct Object* Object, SDL_Window* Window)
{
	return;
}

static const void Destructor_v(struct Object* Object)
{
	return;
}

static const void loadBackgroundSurfaces_v(struct Object* Object) 
{
	return;
}

static const void loadBeaconSurfaces_v(struct Object* Object) 
{
	return;
}

static const void loadButtonSurfaces_v(struct Object* Object) 
{
	return;
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
	return;
}

const struct Object_vtable_ LevelOne[] = { { 
		Constructor_v, 
		Destructor_v, 
		loadBackgroundSurfaces_v, 
		loadBeaconSurfaces_v, 
		loadButtonSurfaces_v, 
		loadCharacterSurfaces_v, 
		loadEnemySurfaces_v, 
		modifyRectValues_v } };
