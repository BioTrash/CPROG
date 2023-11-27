#include "Character.h"
#include "System.h"
#include <SDL2/SDL_image.h>

namespace gameengine{

    Character* Character::getInstance(int x, int y, int w, int h, const char* imagePath, bool mControl, bool kControl, int speed){
        return new Character(x, y, w, h, imagePath, mControl, kControl, speed);
    }
    
    Character::Character(int x, int y, int w, int h, const char* imagePath, bool mControl, bool kControl, int speed): Component{x,y,w,h}, mControl(mControl), kControl(kControl), speed(speed){
        surf = IMG_Load(imagePath);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_WarpMouseInWindow(sys.getWindow(), x, y);
    }

    void Character::render() const {

        SDL_Rect destRect = getRect();

        // Adjust rendering position based on the sprite's pivot point
        destRect.x -= destRect.w / 2;
        destRect.y -= destRect.h / 2;
        
        SDL_RenderCopy(sys.getRen(), texture, NULL, &destRect);
    }

    void Character::keyDown(const SDL_Event& event) {
        if(kControl){
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
        }
    }

    void Character::keyUp(const SDL_Event& event) {
        if(kControl){
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
        }
    }


    void Character::updatePosition(const SDL_Event& event) { //needs to be tied to FPS
        SDL_Rect& currentRect = const_cast<SDL_Rect&>(getRect());

        if(kControl){

            int moveX = (rightPressed ? 1 : 0) - (leftPressed ? 1 : 0);
            int moveY = (downPressed ? 1 : 0) - (upPressed ? 1 : 0);

            if(moveX != 0 && moveY != 0){
                currentRect.x += moveX * (speed / 1.5); 
                currentRect.y += moveY * (speed / 1.5); 
            }
            else{
                currentRect.x += moveX * speed; 
                currentRect.y += moveY * speed; 
            }

        }

        if(mControl){
            currentRect.y = event.motion.y;
            currentRect.x = event.motion.x;
        }

    }

    Character::~Character(){
        SDL_FreeSurface(surf);
    }
}