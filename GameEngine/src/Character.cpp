#include "Character.h"
#include "System.h"
#include <SDL2/SDL_image.h>
#include <string>

namespace gameengine{

    Character* Character::getInstance(int x, int y, int w, int h, const char* imagePath, bool mControl, int speed, std::string id){
        return new Character(x, y, w, h, imagePath, mControl, speed, id);
    }

    Character* Character::getCopy(const Character& other){
        return new Character(other.getRect().x, other.getRect().y, other.getRect().w, other.getRect().h, other.imagePath, other.mControl, other.speed, other.getId());
    }
    
    Character::Character(int x, int y, int w, int h, const char* imagePath, bool mControl, int speed, std::string id): Component{x,y,w,h, id}, imagePath(imagePath), mControl(mControl), speed(speed){
        surf = IMG_Load(imagePath);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);

        if(mControl){
            SDL_ShowCursor(SDL_DISABLE);
            SDL_WarpMouseInWindow(sys.getWindow(), x, y);
        }
        
    }

    Character::Character(const Character& other) : Component{ other.getRect().x, other.getRect().y, other.getRect().w, other.getRect().h, other.getId()}, imagePath(other.imagePath), mControl(other.mControl), speed(other.speed) {
        surf = IMG_Load(imagePath);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);

        if(mControl){
            SDL_ShowCursor(SDL_DISABLE);
            SDL_WarpMouseInWindow(sys.getWindow(), other.getRect().x, other.getRect().y);
        }
        
    }

    void Character::render() const {

        SDL_Rect destRect = getRect();

        // Adjust rendering position based on the sprite's pivot point
        destRect.x -= destRect.w / 2;
        destRect.y -= destRect.h / 2;
        
        SDL_RenderCopy(sys.getRen(), texture, NULL, &destRect);
    }

    void Character::keyDown(const SDL_Event& event) {
        if(!mControl){
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
        if(!mControl){
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


    void Character::updatePosition() {
        SDL_Rect& currentRect = const_cast<SDL_Rect&>(getRect());

        if(!mControl){

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

            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            currentRect.y = mouseY;
            currentRect.x = mouseX;
        }

    }

    Character::~Character(){
        SDL_FreeSurface(surf);
    }
}