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
        target.setRect().y++;

        if(target.isTouching(mc)){
            target.setBehaviour([](Character& newTarget){
                newTarget.setRect().y--;
                newTarget.setRect().x++;
            });
        }


    });

    //Weapon has to follow Main Character, Projectile has to follow weapon. Decide which is created first, weapon or projectile?

    Projectile* projectile = Projectile::getInstance(mc->getRect().x, mc->getRect().y, 10, 10, "Projectile", "/home/rufus/SU/CPROG/GameEngine/resources/images/projectile.png", 30);

    projectile->setBehaviour([](Projectile& target){
        target.setRect().y--;
    });

    Weapon* weapon = Weapon::getInstance(200, 200, 10, 10, "Weapon", mc, 1, 20, 1, ses, projectile, "/home/rufus/SU/CPROG/GameEngine/resources/images/redCircle.png");

    ses.add(weapon);

    Spawner* spawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 10, 5.0f);

    ses.add(spawner);

    ses.run();

    return 0;
}
