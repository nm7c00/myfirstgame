#include "includes/errorout.h"
#include <stdio.h>
#include <stdlib.h>

void ErrorOut(const char* file, int line, const char* function, const char* sdl_error) 
{
	fprintf(stderr, "Error located at\nfile: %s\nline: %i\nfunction: %s\n"
			"SDL_GetError() returned: %s\n", file, line, function, sdl_error);
	exit(0);
}

// note: SDL memory is not freed when ErrorOut() is called, the heap gets popped 
// regardless so I consider freeing memeory trivial in this instance.
