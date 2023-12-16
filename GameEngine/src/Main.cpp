#include <SDL2/SDL.h>
#include <iostream>
#include "Session.h"
#include "Character.h"
#include "Spawner.h"
#include "Weapon.h"
#include "Projectile.h"

using namespace gameengine;

int main(int argc, char** argv) {

    Session ses;

    Character* mc = Character::getInstance(400, 200, 50, 50, "/home/rufus/SU/CPROG/GameEngine/resources/images/redCircle.png", 10, "Main Character", true, true);

    ses.add(mc);

    Character* enemy = Character::getInstance(0, 0, 100, 100, "/home/rufus/SU/CPROG/GameEngine/resources/images/greenCircle.png", 10, "Enemy");

    enemy->setBehaviour([mc](Character& target) {
        if(target.isTouching(mc)){
            target.setBehaviour([](Character& newTarget){
                newTarget.setRect().y--;
                newTarget.setRect().x++;
            });
        }


    }); 

    //Figure out why projectile modifies all enemies while MC doesn't

    Projectile* projectile = Projectile::getInstance(0, 0, 10, 10, "Projectile", "/home/rufus/SU/CPROG/GameEngine/resources/images/projectile.png", 30);

    Weapon* weapon = Weapon::getInstance(200, 200, 10, 10, "Weapon", 1, 20, 1, ses, mc, projectile, "/home/rufus/SU/CPROG/GameEngine/resources/images/redCircle.png");

    ses.add(weapon);

    Spawner* spawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 10, 5.0f);

    ses.add(spawner);

    ses.run();

    return 0;
}
