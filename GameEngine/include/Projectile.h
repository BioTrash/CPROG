#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Component.h"
#include <functional>


namespace gameengine {
    class Projectile : public Component{
        public:
            ~Projectile();
            static Projectile* getEmpty();
            static Projectile* getInstance(int x, int y, int w, int h, std::string id, const char* imagePath, int speed);
            static Projectile* getCopy(const Projectile& other);
            void updatePosition() override;

            void setBehaviour(const std::function<void(Projectile&)>& behaviour) { behaviourFunction = behaviour; };
            const std::function<void(Projectile&)>& getBehaviour() { return behaviourFunction; };

        protected:
            Projectile();
            Projectile(int x, int y, int w, int h, std::string id, const char* imagePath, int speed);
            Projectile(const Projectile& other);
        private:
            const char* imagePath;
            int speed;
            std::function<void(Projectile&)> behaviourFunction;
    };
}

#endif