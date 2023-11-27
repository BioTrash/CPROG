#include <SDL2/SDL.h>
#include "Session.h"
#include "Character.h"

using namespace gameengine;

int main(int argc, char** argv){

    Session ses;

    Character* mc = Character::getInstance(400, 200, 100, 100, "/home/rufus/SU/CPROG/GameEngine/resources/images/redCircle.png", false, 10);
    ses.add(mc);

    ses.run();

    return 0;
};