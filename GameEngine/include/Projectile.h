#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Component.h"


namespace gameengine {
    class Projectile : public Component{
        public:
            ~Projectile();
            static Projectile* getInstance(int x, int y, int w, int h, std::string id, const char* imagePath, int speed);
            static Projectile* getCopy(const Projectile& other);
        protected:
            Projectile();
            Projectile(int x, int y, int w, int h, std::string id, const char* imagePath, int speed);
            Projectile(const Projectile& other);
        private:
            const char* imagePath;
            int speed;
    };
}

#endif