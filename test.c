#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
 {
 SDL_Window *window = NULL;
 SDL_Renderer *renderer = NULL;
 SDL_Texture *texture = NULL;
 SDL_Rect dst = {0, 0, 100, 100};

/* On fait toutes nos initialisations ici */
 SDL_RenderClear(renderer);
 SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
 SDL_SetRenderTarget(renderer, texture);
 SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
 SDL_RenderFillRect(renderer, NULL);
 SDL_SetRenderTarget(renderer, NULL);
 SDL_RenderCopy(renderer, texture, NULL, &dst);
 SDL_RenderPresent(renderer);
 SDL_Delay(10000);

 }