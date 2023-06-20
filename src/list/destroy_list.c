#include "list.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

void destroyList(RectNode* node) 
{
	RectNode* next = NULL;
	RectNode* current = node;
	do {
		next = current->next;
		free(current);
		current = next;
	} while (current->next != NULL);
}
