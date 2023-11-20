#include "Character.h"
#include "System.h"
#include <SDL2/SDL_image.h>

namespace gameengine{

    Character* Character::getInstance(int x, int y, int w, int h, const char* imagePath, bool mControl, bool kControl){
        return new Character(x, y, w, h, imagePath, mControl, kControl);
    }
    
    Character::Character(int x, int y, int w, int h, const char* imagePath, bool mControl, bool kControl): Component{x,y,w,h}, mControl(mControl), kControl(kControl){
        surf = IMG_Load(imagePath);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);

    }

    void Character::render() const {
        SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
    }

    Character::~Character(){
        SDL_FreeSurface(surf);
    }
}