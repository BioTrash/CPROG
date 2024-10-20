// Rufus Trukhin rutr7079 | CPROG  Programmeringsprojekt
#ifndef SESSION_H
#define SESSION_H

#include "Component.h"
#include <vector>
#include <string>

namespace gameengine{
    class Session{
        public:
            void add(Component* c);
            void protect(Component* c);
            void remove(Component* c);
            void run();
            const std::vector<Component*> getComp() const { return comp; }

            void changeBackground(std::string backgroundPath) { imagePath = backgroundPath; }
            ~Session();  
        private:
            std::vector<Component*> comp;
            std::vector<Component*> added;
            std::vector<Component*> removed;
            std::vector<Component*> irremovable;
            std::string imagePath;
    };
}

#endif