#include "Projectile.h"
#include "System.h"
#include <SDL2/SDL_image.h>
#include <string>

namespace gameengine{

    Projectile::Projectile(int x, int y, int w, int h, std::string id, const char* imagePath, int speed) : Component{x,y,w,h,id}, imagePath(imagePath), speed(speed){
        surf = IMG_Load(imagePath);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    }

    Projectile::Projectile(const Projectile& other) : Component{ other.getRect().x, other.getRect().y, other.getRect().h, other.getRect().w, other.getId()}, imagePath(other.imagePath), speed(other.speed){
        surf = IMG_Load(imagePath);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    }

    Projectile* Projectile::getInstance(int x, int y, int w, int h, std::string id, const char* imagePath, int speed){
        return new Projectile(x, y, w, h, id, imagePath, speed);
    }

    Projectile* Projectile::getCopy(const Projectile& other){
        return new Projectile(other.getRect().x, other.getRect().y, other.getRect().h, other.getRect().w, other.getId(), other.imagePath, other.speed);
    }

    const bool Projectile::isTouching(Projectile* target) const {
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

    void Projectile::render() const {
        SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
    }

    void Projectile::updatePosition(){
        if (behaviourFunction) {
            behaviourFunction(*this);
        }
    }

    Projectile::~Projectile(){
        SDL_FreeSurface(surf);
    }
}