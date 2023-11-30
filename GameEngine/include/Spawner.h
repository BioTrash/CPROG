#ifndef SPAWNER_H
#define SPAWNER_H

#include "Component.h"
#include "Character.h"
#include "Session.h"
#include <string>
#include <chrono>
#include <random>

namespace gameengine {
    class Spawner : public Component {
    public:
        static Spawner* getInstance(int x, int y, std::string id, Character* target, Session& ses, int w = 1, int h = 1, int amount = 0, float time = 0);
        void spawn(int& w, int& h);
        void updatePosition() override;
        ~Spawner();

    protected:
        Spawner(int x, int y, std::string id, Character* target, Session& ses, int w = 1, int h = 1, int amount = 1, float time = 0);

    private:
        Character* target;
        int width;
        int height;
        Session& ses;
        int amount;
        int time;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdateTime;
        std::default_random_engine engine;
    };
}

#endif
