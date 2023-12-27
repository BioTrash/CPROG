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

    ses.changeBackground("/home/rufus/SU/CPROG/GameEngine/resources/images/spaceBG.jpg");

    Character* mc = Character::getInstance(400, 200, 1089/15, 1920/15, "/home/rufus/SU/CPROG/GameEngine/resources/images/spaceShip.png", 10, "Main Character", true, true);

    ses.add(mc);

    Character* enemy = Character::getInstance(0, 0, 505/10, 361/10, "/home/rufus/SU/CPROG/GameEngine/resources/images/alien.png", 10, "Enemy");

    Projectile* projectile = Projectile::getInstance(10, 10, 10, 10, "Projectile", "/home/rufus/SU/CPROG/GameEngine/resources/images/projectile.png", 10);

    enemy->setBehaviour([mc, projectile, ses](Character& target) {
        target.setRect().y++;
        
        if(target.isTouching(mc)){
            target.setBehaviour([](Character& newTarget){
                newTarget.setRect().y--;
                newTarget.setRect().x++;
            });
        }
    }); 

    Weapon* weapon = Weapon::getInstance(200, 200, 10, 10, "Weapon", 1, 100, 1, ses, mc, projectile);

    //A controller class may need to be implemented

    weapon->setBehaviour([&](Weapon& targetWeapon){
        targetWeapon.destroyOnCollision<Projectile, Character>("Projectile", "Enemy");
    });

    ses.add(weapon);

    Spawner* spawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 10, 5.0f);

    ses.add(spawner);

    ses.run();

    return 0;
}
