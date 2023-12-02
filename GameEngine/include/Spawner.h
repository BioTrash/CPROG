// Spawner.h

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
        static Spawner* getInstance(int x, int y, std::string id, Character* target, Session& ses, int w, int h, int amount, float time);
        ~Spawner();

        void updatePosition() override;

    private:
        Spawner(int x, int y, std::string id, Character* target, Session& ses, int w, int h, int amount, float time);
        void spawn(int& w, int& h, const std::function<void(Character&)>& behaviorFunction);

        Character* target;
        Session& ses;
        int width;
        int height;
        int amount;
        float time;
        std::chrono::high_resolution_clock::time_point lastUpdateTime;
        std::default_random_engine engine;
    };
}

#endif
