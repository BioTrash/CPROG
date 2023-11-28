#ifndef SPAWNER_H
#define SPAWNER_H
#include "Component.h"

namespace gameengine{
    class Spawner: public Component{
        public:
            Spawner(int x, int y, int w = 0, int h = 0);
            ~Spawner();
    };
}

#endif