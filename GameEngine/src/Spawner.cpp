#include "Spawner.h"
#include <string>
#include <random>

namespace gameengine {
    Spawner* Spawner::getInstance(int x, int y, std::string id, Character* target, Session& ses, int w, int h, int amount, float time) {
        return new Spawner(x, y, id, target, ses, w, h, amount, time);
    }

    Spawner::Spawner(int x, int y, std::string id, Character* target, Session& ses, int w, int h, int amount, float time)
        : Component(x, y, w, h, id), target(target), width(w), height(h), ses(ses), time(time){ random(); }

    Spawner::~Spawner() {
        // Implementation of destructor
    }

    void Spawner::random(){
        std::random_device rd;
        std::default_random_engine engine(rd());
        std::uniform_int_distribution<int> sWidth(0, width);
        std::uniform_int_distribution<int> sHeight(0, height);

        int tmpWidth = sWidth(engine);
        int tmpHeight = sHeight(engine);

        spawn(tmpWidth, tmpHeight); //Connect this with FPS and do once every "time" float second
    }

    void Spawner::spawn(int& w, int& h) {
        target->changeRect().x = w;
        target->changeRect().y = h;
        ses.add(target);
    }
}
