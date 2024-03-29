// Rufus Trukhin rutr7079 | CPROG  Programmeringsprojekt
#include "System.h"
#include "Constants.h"
#include <SDL2/SDL.h>

namespace gameengine{
    System::System(){
        SDL_Init(SDL_INIT_EVERYTHING);

        win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
        ren = SDL_CreateRenderer(win, -1, 0);
        SDL_GetWindowSize(win, &winWidth, &winHeight);
        
        TTF_Init();
        font = TTF_OpenFont((constants::gResPath + "fonts/NotoSansMono-Regular.ttf").c_str(), 36);

    }

    System::~System(){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
    }

    SDL_Renderer* System::getRen() const{
        return ren;
    }

    SDL_Window* System::getWindow() const{
        return win;
    }

    TTF_Font* System::getFont() const{
        return font;
    }
    
    System sys;
}