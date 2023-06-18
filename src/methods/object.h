#ifndef OBJECT_H_
#define OBJECT_H_

#include "../includes/rect_vessel.h"
#include "../includes/surface_arrays.h"
#include <SDL2/SDL.h>

typedef struct Object 
{
	const struct Object_vtable_* vtable_;
	SurfaceArrays surface_arrays;
	RectVessel rect_vessel;
	SDL_Renderer* renderer;
	SDL_Window* window;
} Object;

struct Object_vtable_ 
{
	const void (*Constructor_v)(struct Object* Object, SDL_Window* Window);
	const void (*Destructor_v)(struct Object* Object);
	const void (*loadBackgroundSurfaces_v)(struct Object* Object);
	const void (*loadBeaconSurfaces_v)(struct Object* Object);
	const void (*loadButtonSurfaces_v)(struct Object* Object);
	const void (*loadCharacterSurfaces_v)(struct Object* Object);
	const void (*loadEnemySurfaces_v)(struct Object* Object);
	const void (*modifyRectValues_v)(struct Object* Object, int* scene_counter, int* ground_height);
};


// wrapper functions //
static inline const void Constructor(struct Object* Object, SDL_Window* Window) 
{
	return Object->vtable_->Constructor_v(Object, Window);
}

static inline const void Destructor(struct Object* Object)
{
	return Object->vtable_->Destructor_v(Object);
}

static inline const void loadBackgroundSurfaces(struct Object* Object)
{
	return Object->vtable_->loadBackgroundSurfaces_v(Object);
}

static inline const void loadBeaconSurfaces(struct Object* Object)
{
	return Object->vtable_->loadBeaconSurfaces_v(Object);
}

static inline const void loadButtonSurfaces(struct Object* Object)
{
	return Object->vtable_->loadButtonSurfaces_v(Object);
}

static inline const void loadCharacterSurfaces(struct Object* Object)
{
	return Object->vtable_->loadCharacterSurfaces_v(Object);
}

static inline const void loadEnemySurfaces(struct Object* Object)
{
	return Object->vtable_->loadEnemySurfaces_v(Object);
}

static inline const void modifyRectValues(struct Object* Object, int* scene_counter, int* ground_height)
{
	return Object->vtable_->modifyRectValues_v(Object, scene_counter, ground_height);
}


// vtables declared here //
extern const struct Object_vtable_ MainMenuVTable[];
extern const struct Object_vtable_ LevelOneVTable[];

#endif
