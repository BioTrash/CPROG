#ifndef SESSION_H
#define SESSION_H
#include <vector>
#include "Component.h"

namespace gameengine{
    class Session{
        public:
            void add(Component* c);
            void run();
            ~Session();  
        private:
            std::vector<Component*> comp;
    };
}

#endif