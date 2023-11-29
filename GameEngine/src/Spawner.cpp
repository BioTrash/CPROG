#include "Spawner.h"
#include <string>

namespace gameengine {
    Spawner* Spawner::getInstance(int x, int y, std::string id, Character* target, int w, int h, int amount, float time) {
        return new Spawner(x, y, id, target, w, h, amount, time);
    }

    Spawner::Spawner(int x, int y, std::string id, Character* target, int w, int h, int amount, float time)
        : Component(x, y, w, h, id), target(target), time(time) {
        // Decide to pump or to not pump enemies
    }

    Spawner::~Spawner() {
        // Implementation of destructor
    }

    void Spawner::spawn() {
        // Implementation of spawn function
    }
}
