#include <SDL2/SDL.h>
#include <iostream>
#include "Session.h"
#include "Character.h"
#include "Spawner.h"
#include "Weapon.h"
#include "Label.h"
#include "Projectile.h"

using namespace gameengine;

int main(int argc, char** argv) {

    /*GAME TODO:
        
        Enemy dies when off-screen (later)
        Set screen to a certain resolution (later)
        Enemy speed and amount changes on certain time threasholds (implement a in-build timer) TIMER AND SCORE - DONE!
        Projectile/Weapon gets upgraded on certain enemy kill threashhold (implement in-build weapon/projectile swap)
        Game Over Screen*/

    Session ses;

    ses.changeBackground("/home/rufus/SU/CPROG/GameEngine/resources/images/spaceBG.jpg");

    Label* time = Label::getInstance(20, 20, 20, 40, "Time: 0", "Timer");
    time->setColor(255, 255, 255);
    time->setTimer();

    ses.add(time);

    Label* score = Label::getInstance(620, 20, 20, 40, "Score: 0", "Score");
    score->setColor(255, 255, 255);

    ses.add(score);

    Character* mc = Character::getInstance(400, 200, 1089/15, 1920/15, "/home/rufus/SU/CPROG/GameEngine/resources/images/spaceShip.png", 10, "Main Character", true, true);

    ses.add(mc);

    Character* enemy = Character::getInstance(0, 0, 505/10, 361/10, "/home/rufus/SU/CPROG/GameEngine/resources/images/alien.png", 10, "Enemy");

    Projectile* projectile = Projectile::getInstance(10, 10, 10, 10, "Projectile", "/home/rufus/SU/CPROG/GameEngine/resources/images/projectile.png", 10);

    enemy->setBehaviour([mc, time, projectile, ses](Character& target) {
        target.setRect().y++;
    }); 

    Weapon* weapon = Weapon::getInstance(200, 200, 10, 10, "Weapon", 1, 100, 1, ses, mc, projectile);

    //A controller class may need to be implemented
    int i = 0;
    weapon->setBehaviour([&](Weapon& targetWeapon){
       
        if(targetWeapon.detectCollision<Projectile, Character>("Projectile", "Enemy")){
            i++;
            score->setText("Score: " + std::to_string(i));
        }

        targetWeapon.destroyOnCollision<Projectile, Character>("Projectile", "Enemy");
    });

    ses.add(weapon);

    Spawner* spawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 10, 5.0f);

    ses.add(spawner);

    ses.run();

    return 0;
}
