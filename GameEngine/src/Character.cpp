#include "Character.h"
#include "System.h"
#include "Projectile.h"
#include "Session.h"
#include <SDL2/SDL_image.h>
#include <string>

namespace gameengine{

    Character* Character::getInstance(int x, int y, int w, int h, const char* imagePath, int speed, std::string id, bool controlable, bool mControl){
        return new Character(x, y, w, h, imagePath, speed, id, controlable, mControl);
    }

    Character* Character::getCopy(const Character& other){
        return new Character(other.getRect().x, other.getRect().y, other.getRect().w, other.getRect().h, other.imagePath, other.speed, other.getId(), other.controlable, other.mControl);
    }
    
    Character::Character(int x, int y, int w, int h, const char* imagePath, int speed, std::string id, bool controlable, bool mControl): Component{x,y,w,h, id}, imagePath(imagePath), speed(speed), controlable(controlable), mControl(mControl){
        surf = IMG_Load(imagePath);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);

        if(mControl && controlable){
            SDL_ShowCursor(SDL_DISABLE);
            SDL_WarpMouseInWindow(sys.getWindow(), x, y);
        }
        
    }

    Character::Character(const Character& other) : Component{ other.getRect().x, other.getRect().y, other.getRect().w, other.getRect().h, other.getId()}, imagePath(other.imagePath), speed(other.speed), controlable(other.controlable), mControl(other.mControl){
        surf = IMG_Load(imagePath);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);

        if(mControl && controlable){
            SDL_ShowCursor(SDL_DISABLE);
            SDL_WarpMouseInWindow(sys.getWindow(), other.getRect().x, other.getRect().y);
        }
        
    }

    template const bool Character::isTouching<Character>(Character* target) const;
    template const bool Character::isTouching<Projectile>(Projectile* target) const;

    template <typename T>
    const bool Character::isTouching(T* target) const {

        
        SDL_Rect rect1 = this->getRect();
        SDL_Rect rect2 = target->getRect();

        // Check if the rectangles overlap
        if (SDL_HasIntersection(&rect1, &rect2)) {
            int xMin = std::max(rect1.x, rect2.x);
            int xMax = std::min(rect1.x + rect1.w, rect2.x + rect2.w);
            int yMin = std::max(rect1.y, rect2.y);
            int yMax = std::min(rect1.y + rect1.h, rect2.y + rect2.h);

            Uint32* pixels1 = this->getPixel();
            Uint32* pixels2 = target->getPixel();

            // Iterate over the overlapping region
            for (int y = yMin; y < yMax; ++y) {
                for (int x = xMin; x < xMax; ++x) {
                    // Get the pixel values for both surfaces
                    Uint32 pixel1 = pixels1[(y - rect1.y) * rect1.w + (x - rect1.x)];
                    Uint32 pixel2 = pixels2[(y - rect2.y) * rect2.w + (x - rect2.x)];

                    // Check if the pixels are not transparent
                    if (pixel1 & 0xFF000000 && pixel2 & 0xFF000000) {
                        // Collision detected
                        return true;
                    }
                }
            }
        }

        // No collision detected
        return false;
    }

    void Character::render() const {
        SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
    }

    void Character::keyDown(const SDL_Event& event) {
        if(!mControl && controlable){
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
        if(!mControl && controlable){
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
        
        if (behaviourFunction) {
            behaviourFunction(*this);
        }

        if(!mControl && controlable){

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

        if(mControl && controlable){

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