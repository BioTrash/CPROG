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

    void Character::keyDown(const SDL_Event& event) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                upPressed = true;
                break;

            case SDLK_DOWN:
                downPressed = true;
                break;

            case SDLK_LEFT:
                leftPressed = true;
                break;

            case SDLK_RIGHT:
                rightPressed = true;
                break;
        }

        updatePosition();
    }

    void Character::keyUp(const SDL_Event& event) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                upPressed = false;
                break;

            case SDLK_DOWN:
                downPressed = false;
                break;

            case SDLK_LEFT:
                leftPressed = false;
                break;

            case SDLK_RIGHT:
                rightPressed = false;
                break;
        }

        updatePosition();
    }

    void Character::updatePosition() {
        SDL_Rect& currentRect = const_cast<SDL_Rect&>(getRect());

        // Calculate movement based on key states
        int moveX = (rightPressed ? 1 : 0) - (leftPressed ? 1 : 0);
        int moveY = (downPressed ? 1 : 0) - (upPressed ? 1 : 0);

        // Update the character's position
        currentRect.x += moveX * 10; // Adjust the value as needed
        currentRect.y += moveY * 10; // Adjust the value as needed
    }

    Character::~Character(){
        SDL_FreeSurface(surf);
    }
}