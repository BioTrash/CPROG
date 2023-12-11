#ifndef WEAPON_H
#define WEAPON_H
#include "Character.h"
#include "Projectile.h"
#include <string>

namespace gameengine{
    class Weapon : public Component {
        public:
            ~Weapon();
            static Weapon* getInstance(int x, int y, int w, int h, std::string id, Character target, const char* imagePath, int speed, int amount, int spread, Projectile* proj = nullptr);
            //static Weapon* getCopy(const Weapon& other);
            void updatePosition() override;
            void spawnProjectile();
        protected:
            Weapon(int x, int y, int w, int h, std::string id, Character target, int speed, int amount, int spread, Projectile* proj = nullptr, const char* imagePath = NULL);
            //Weapon(const Weapon& other);
        private:   
            const char* imagePath;
            int speed;
            int amount;
            int spread;
            Projectile* proj;
    };
}
#endif