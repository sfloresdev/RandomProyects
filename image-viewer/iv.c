#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main()
{
    const char *str = "Image viewer";

    printf("Hello world\n");

    SDL_Window *pwindow = SDL_CreateWindow(str, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            900, 600, 0);
	SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    
    Uint8 r, g, b;
    r = 0x1A;
    g = 0x21;
    b = 0x21;
    Uint32 color = SDL_MapRGB(psurface->format, r,  g,  b);
    SDL_FillRect(psurface, NULL, color);
    SDL_UpdateWindowSurface(pwindow);
	SDL_Delay(3000);

    return (0); 
}
