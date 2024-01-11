#include <SDL2/SDL.h>
#include <iostream>
#include "Session.h"
#include "Character.h"
#include "Spawner.h"
#include "Weapon.h"
#include "Label.h"
#include "Projectile.h"
#include "Constants.h"

using namespace gameengine;

int main(int argc, char** argv) {

    /*GAME TODO:
        Game Over Screen
        */
 
    Session ses;

    ses.changeBackground((constants::gResPath + "images/spaceBG.jpg").c_str());

    std::cout << (constants::gResPath + "images/spaceBG.jpg").c_str() << std::endl;

    Label* time = Label::getInstance(20, 20, 20, 40, "Time: 0", "Timer");
    time->setColor(255, 255, 255);
    time->setTimer();

    ses.add(time);

    Label* score = Label::getInstance(620, 20, 20, 40, "Score: 0", "Score");
    score->setColor(255, 255, 255);

    ses.add(score);

    Character* mc = Character::getInstance(400, 200, 1089/15, 1920/15, "/home/rufus/SU/CPROG/GameEngine/resources/images/spaceShip.png", 10, "Main Character", true, true);

    ses.add(mc);
    ses.protect(mc);

    Character* enemy = Character::getInstance(0, 0, 505/10, 361/10, "/home/rufus/SU/CPROG/GameEngine/resources/images/alien.png", 10, "Enemy");

    Projectile* projectile = Projectile::getInstance(10, 10, 10, 10, "Projectile", "/home/rufus/SU/CPROG/GameEngine/resources/images/projectile.png", 10);

    enemy->setBehaviour([mc, time, projectile, ses](Character& target) {
        target.setRect().y++;
    }); 

    Weapon* weapon = Weapon::getInstance(200, 200, 10, 10, "Weapon", 1, 1000, 1, ses, mc, projectile);

    ses.add(weapon);
    ses.protect(weapon);

    Spawner* spawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 20, 1.0f);

    ses.add(spawner);

    //Game Manager
    Weapon* weaponManager = Weapon::getInstance(2, 2, 10, 10, "Manager", 1, 1000, 1, ses);

    Weapon* secondWeapon = Weapon::getInstance(200, 200, 10, 10, "Weapon", 1, 1000, 1, ses, mc, projectile); 
    Weapon* thirdWeapon = Weapon::getInstance(200, 200, 10, 10, "Weapon", 1, 1000, 1, ses, mc, projectile); 
    
    int i = 0;
    bool secondWeaponBool, thirdWeaponBool, secondSpawnerBool, thirdSpawnerBool, secondProjectileBool;
    weaponManager->setBehaviour([&](Weapon& manager){

        if(score->getContent() == "Score: " + std::to_string(5) && !secondWeaponBool){
            secondWeaponBool = true;

            secondWeapon->setBehaviour([mc](Weapon& newWeapon){
                newWeapon.setRect().x = mc->getRect().x;
            });

            weapon->setBehaviour([mc](Weapon& firstWeapon){
                firstWeapon.setRect().x = mc->getRect().x + mc->getRect().w;
            });

            ses.add(secondWeapon);
            ses.protect(secondWeapon);
        }

        if(score->getContent() == "Score: " + std::to_string(10) && !thirdWeaponBool){
            thirdWeaponBool = true;

            thirdWeapon->setBehaviour([mc](Weapon& newWeapon){
                newWeapon.setRect().x = mc->getRect().x + mc->getRect().w/2;
            });

            ses.add(thirdWeapon);
            ses.protect(thirdWeapon);
        }

        if(score->getContent() == "Score: " + std::to_string(20) && !secondProjectileBool){
            secondProjectileBool = true;

            //Write something here

        }

        if(time->getContent() == "Time: " + std::to_string(15) && !secondSpawnerBool){
            secondSpawnerBool = true;
            Spawner* secondSpawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 20, 1.0f);
            ses.add(secondSpawner);
        }

        if(time->getContent() == "Time: " + std::to_string(30) && !thirdSpawnerBool){
            thirdSpawnerBool = true;
            Spawner* thirdSpawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 20, 1.0f);
            ses.add(thirdSpawner);
        }

        if(manager.detectCollision<Projectile, Character>("Projectile", "Enemy")
        || manager.detectCollision<Projectile, Character>("SecondProjectile", "Enemy")){
            i++;
            score->setText("Score: " + std::to_string(i));
        }

        manager.destroyOnCollision<Projectile, Character>("Projectile", "Enemy"); 
        manager.destroyOnCollision<Projectile, Character>("SecondProjectile", "Enemy"); 
    });

    ses.add(weaponManager);

    ses.run();

    return 0;
}
