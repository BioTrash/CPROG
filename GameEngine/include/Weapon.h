#ifndef WEAPON_H
#define WEAPON_H
#include "Character.h"
#include "Component.h"
#include "Session.h"
#include "Projectile.h"
#include <string>
#include <chrono>
#include <SDL2/SDL.h>

namespace gameengine{
    class Weapon : public Component {
        public:
            ~Weapon();
            static Weapon* getInstance(int x, int y, int w, int h, std::string id, Character* target, int speed, int amount, int spread, Session& ses, Projectile* proj = nullptr, const char* imagePath = NULL);
            //static Weapon* getCopy(const Weapon& other);
            void render() const;
            void updatePosition() override;
            void spawn(const std::function<void(Projectile&)>& behaviorFunction);
        protected:
            Weapon(int x, int y, int w, int h, std::string id, Character* target, int speed, int amount, int spread, Session& ses, Projectile* proj = nullptr, const char* imagePath = NULL);
            //Weapon(const Weapon& other);
        private:   
            int speed;
            int amount;
            int spread;
            Session& ses;
            Projectile* proj;
            const char* imagePath;

            SDL_Surface* surf;
            SDL_Texture* texture;

            std::chrono::high_resolution_clock::time_point lastUpdateTime;
    };
}
#endif