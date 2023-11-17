#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv){

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("My Window", 100, 100, 700, 500, 0);

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Surface* bgSurf = IMG_Load("/home/rufus/Wallpapers/girlWithHens.jpg");
    SDL_Texture* bgTx = SDL_CreateTextureFromSurface(ren, bgSurf);
    SDL_FreeSurface(bgSurf);

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, bgTx, NULL, NULL);
    SDL_RenderPresent(ren);

    SDL_Delay(10000);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}