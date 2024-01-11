#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Component.h"
#include "Character.h"
#include <functional>
#include <SDL2/SDL.h>


namespace gameengine {
    class Projectile : public Component{
        public:
            ~Projectile();
            static Projectile* getInstance(int x, int y, int w, int h, std::string id, std::string imagePath, int speed);
            static Projectile* getCopy(const Projectile& other);
            void updatePosition() override;
            void render() const;
            /* const bool isTouching(Character* target) const; */
            Uint32* getPixel() const { return static_cast<Uint32*>(surf->pixels); };
            int getSpeed() const { return speed; };

            void setBehaviour(const std::function<void(Projectile&)>& behaviour) { behaviourFunction = behaviour; };
            const std::function<void(Projectile&)>& getBehaviour() { return behaviourFunction; };

        protected:
            Projectile(int x, int y, int w, int h, std::string id, std::string imagePath, int speed);
            Projectile(const Projectile& other);
        private:
            std::string imagePath;
            int speed;
            std::function<void(Projectile&)> behaviourFunction;

            SDL_Surface* surf;
            SDL_Texture* texture;
    };
}

#endif