#ifndef SPAWNER_H
#define SPAWNER_H

#include "Component.h"
#include "Character.h"
#include "Session.h"
#include <string>

namespace gameengine {
    class Spawner : public Component {
    public:
        static Spawner* getInstance(int x, int y, std::string id, Character* target, Session& ses, int w = 1, int h = 1, int amount = 0, float time = 0);
        void spawn(int& w, int& h);
        void random();
        ~Spawner();

    protected:
        Spawner(int x, int y, std::string id, Character* target, Session& ses, int w = 1, int h = 1, int amount = 1, float time = 0);

    private:
        Character* target;
        int width;
        int height;
        Session& ses;
        float time;
    };
}

#endif
