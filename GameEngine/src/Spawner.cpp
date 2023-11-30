#include "Spawner.h"
#include <SDL2/SDL.h>

namespace gameengine {
    Spawner* Spawner::getInstance(int x, int y, std::string id, Character* target, Session& ses, int w, int h, int amount, float time) {
        return new Spawner(x, y, id, target, ses, w, h, amount, time);
    }

    Spawner::Spawner(int x, int y, std::string id, Character* target, Session& ses, int w, int h, int amount, float time)
        : Component(x, y, w, h, id), target(target), width(w), height(h), ses(ses), amount(amount), time(time) {
        lastUpdateTime = std::chrono::high_resolution_clock::now();
        std::random_device rd;
        engine = std::default_random_engine(rd());
    }

    Spawner::~Spawner() {
        // Implementation of destructor
    }

    void Spawner::updatePosition() {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count();

        int characterCheck = 0;
        for(Component* c: ses.getComp()){
            if(c->getId() == target->getId()) characterCheck++;
        }

        if (elapsedSeconds >= time && characterCheck < amount) {

            lastUpdateTime = currentTime;

            std::uniform_int_distribution<int> sWidth(0, width);
            std::uniform_int_distribution<int> sHeight(0, height);

            int tmpWidth = sWidth(engine);
            int tmpHeight = sHeight(engine);

            spawn(tmpWidth, tmpHeight);
        }
    }

    void Spawner::spawn(int& w, int& h) {
        target->changeRect().x = w;
        target->changeRect().y = h;

        Character* tempTarget = Character::getCopy(*target);

        ses.add(tempTarget);
    }
}
