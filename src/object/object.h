#ifndef OBJECT_H_
#define OBJECT_H_

#include "../includes/surface_arrays.h"
#include "../list/list.h"
#include <SDL2/SDL.h>

typedef struct Object 
{
	const struct Object_vtable_* vtable_;
	SurfaceArrays surface_arrays;
	RectNode* rect_node;
	SDL_Renderer* renderer;
	SDL_Window* window;
	int quit_flag;
	int scene_counter;
	int total_scene_count;
} Object;

struct Object_vtable_ 
{
	const void (*Constructor_v)(struct Object* Object, SDL_Window* Window);
	const void (*Destructor_v)(struct Object* Object);
	const void (*loadBackgroundSurfaces_v)(struct Object* Object);
	const void (*loadBeaconSurfaces_v)(struct Object* Object);
	const void (*loadButtonSurfaces_v)(struct Object* Object);
	const void (*loadCharacterSurfaces_v)(struct Object* Object);
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

// vtables declared here //
extern const struct Object_vtable_ MainMenuVTable[];
extern const struct Object_vtable_ LevelOneVTable[];

#endif
