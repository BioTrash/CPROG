#ifndef SPAWNER_H
#define SPAWNER_H

#include "Component.h"
#include "Character.h"
#include <string>

namespace gameengine {
    class Spawner : public Component {
    public:
        static Spawner* getInstance(int x, int y, std::string id, Character* target, int w = 1, int h = 1, int amount = 1, float time = 0);
        void spawn();
        ~Spawner();

    protected:
        Spawner(int x, int y, std::string id, Character* target, int w = 1, int h = 1, int amount = 1, float time = 0);

    private:
        Character* target;
        float time;
    };
}

#endif
