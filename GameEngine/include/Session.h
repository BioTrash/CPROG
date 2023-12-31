#ifndef SESSION_H
#define SESSION_H
#include <vector>
#include "Component.h"

namespace gameengine{
    class Session{
        public:
            void add(Component* c);
            void protect(Component* c);
            void remove(Component* c);
            //void triggerRemove(Component* c);
            void run();
            const std::vector<Component*> getComp() const { return comp; }

            void changeBackground(const char* backgroundPath) { imagePath = backgroundPath; }
            ~Session();  
        private:
            std::vector<Component*> comp;
            std::vector<Component*> added;
            std::vector<Component*> removed;
            std::vector<Component*> irremovable;
            const char* imagePath = nullptr;
    };
}

#endif