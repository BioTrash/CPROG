#include <SDL2/SDL.h>
#include "Session.h"
#include "Character.h"
#include "Spawner.h"

using namespace gameengine;

int main(int argc, char** argv){

    Session ses;

    Character* mc = Character::getInstance(400, 200, 100, 100, "/home/rufus/SU/CPROG/GameEngine/resources/images/redCircle.png", true, 10, "Main Character");

    ses.add(mc);

    Character* enemy = Character::getInstance(0, 0, 50, 50, "/home/rufus/SU/CPROG/GameEngine/resources/images/greenCircle.png", false, 10, "Enemy");

    Spawner* spawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 200, 100);

    ses.add(spawner);

    ses.run();

    return 0;
};