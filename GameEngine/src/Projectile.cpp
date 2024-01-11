#include "Projectile.h"
#include "System.h"
#include "Character.h"
#include <SDL2/SDL_image.h>
#include <string>

namespace gameengine{

    Projectile::Projectile(int x, int y, int w, int h, std::string id, std::string imagePath, int speed) : Component{x,y,w,h,id}, imagePath(imagePath), speed(speed){
        surf = IMG_Load(imagePath.c_str());
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    }

    Projectile::Projectile(const Projectile& other) : Component{ other.getRect().x, other.getRect().y, other.getRect().h, other.getRect().w, other.getId()}, imagePath(other.imagePath), speed(other.speed){
        surf = IMG_Load(imagePath.c_str());
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    }

    Projectile* Projectile::getInstance(int x, int y, int w, int h, std::string id, std::string imagePath, int speed){
        return new Projectile(x, y, w, h, id, imagePath, speed);
    }

    Projectile* Projectile::getCopy(const Projectile& other){
        return new Projectile(other.getRect().x, other.getRect().y, other.getRect().h, other.getRect().w, other.getId(), other.imagePath, other.speed);
    }

    void Projectile::render() const {
        SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
    }

    void Projectile::updatePosition(){

        this->setRect().y -= speed;
        if (behaviourFunction) {
            behaviourFunction(*this);
        }
    }

    Projectile::~Projectile(){
        SDL_FreeSurface(surf);
    }
}