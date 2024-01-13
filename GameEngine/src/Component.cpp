// Rufus Trukhin rutr7079 | CPROG  Programmeringsprojekt
#include "Component.h"
#include <string>

namespace gameengine{
    Component::Component(int x, int y, int w, int h, std::string id):rect{x,y,w,h}, id(id){

    }

    Component::~Component(){
        
    }
}

