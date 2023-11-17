#include "Label.h"
#include "System.h"
#include <SDL2/SDL_ttf.h>

namespace gameengine{
    Label::Label(int x, int y, int w, int h, std::string text): Component(x,y,w,h), content(text){
        SDL_Surface* surf = TTF_RenderText_Solid(sys.getFont(), content.c_str(), {0,0,0});
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }

    void Label::render() const {
        SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
    }

    Label::~Label(){
        SDL_DestroyTexture(texture);
    }
}