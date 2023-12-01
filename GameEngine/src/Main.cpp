#include <SDL2/SDL.h>
#include "Session.h"
#include "Character.h"
#include "Spawner.h"

using namespace gameengine;

int main(int argc, char** argv){

    Session ses;

    Character* mc = Character::getInstance(400, 200, 100, 100, "/home/rufus/SU/CPROG/GameEngine/resources/images/redCircle.png", 10, "Main Character", true, true);

    ses.add(mc);

    Character* enemy = Character::getInstance(0, 0, 50, 50, "/home/rufus/SU/CPROG/GameEngine/resources/images/greenCircle.png", 10, "Enemy");

    Spawner* spawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 10, 1.0f);

    ses.add(spawner);

    ses.run();

    return 0;
};