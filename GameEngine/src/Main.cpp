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
    Session ses;

    ses.changeBackground(constants::gResPath + "images/spaceBG.jpg");

    Label* time = Label::getInstance(20, 20, 20, 40, "Time: 0", "Timer");
    time->setColor(255, 255, 255);
    time->setTimer();

    ses.add(time);

    Label* score = Label::getInstance(620, 20, 20, 40, "Score: 0", "Score");
    score->setColor(255, 255, 255);

    ses.add(score);

    Character* mc = Character::getInstance(400, 200, 1089/15, 1920/15, constants::gResPath + "images/spaceShip.png", 10, "Main Character", true, true);

    ses.add(mc);
    ses.protect(mc);

    Character* enemy = Character::getInstance(0, 0, 505/10, 361/10, constants::gResPath + "images/alien.png", 1, "Enemy");

    Projectile* projectile = Projectile::getInstance(10, 10, 10, 10, "Projectile", constants::gResPath + "images/projectile.png", 10);

    enemy->setBehaviour([](Character& target) {
        target.setRect().y += target.getSpeed();
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
    int spawnerCount = 1;
    weaponManager->setBehaviour([&](Weapon& manager){

        if((score->getContent() == "Score: " + std::to_string(10) || score->getContent() == "Score: " + std::to_string(90))){

            secondWeapon->setBehaviour([mc](Weapon& newWeapon){
                newWeapon.setRect().x = mc->getRect().x;
            });

            weapon->setBehaviour([mc](Weapon& firstWeapon){
                firstWeapon.setRect().x = mc->getRect().x + mc->getRect().w/2;
            });

            ses.add(secondWeapon);
            ses.protect(secondWeapon);
            secondWeapon->setProjectile(projectile);
        }

        if((score->getContent() == "Score: " + std::to_string(30) || score->getContent() == "Score: " + std::to_string(120))){

            thirdWeapon->setBehaviour([mc](Weapon& newWeapon){
                newWeapon.setRect().x = mc->getRect().x + mc->getRect().w;
            });

            ses.add(thirdWeapon);
            ses.protect(thirdWeapon);
            thirdWeapon->setProjectile(projectile);
        }

        if(score->getContent() == "Score: " + std::to_string(70)){

            projectile->setBehaviour([&](Projectile& proj){
                if(manager.detectCollision<Projectile, Character>("Projectile", "Enemy")){
                    Projectile* tempProj = Projectile::getCopy(proj);
                    tempProj->setID("SecondProjectile");

                    tempProj->setRect().x = manager.returnLeft<Projectile, Character>("Projectile", "Enemy")->getRect().x;
                    tempProj->setRect().y = manager.returnLeft<Projectile, Character>("Projectile", "Enemy")->getRect().y;

                    tempProj->setBehaviour([](Projectile& newProj){
                        newProj.setRect().x += newProj.getSpeed();
                        newProj.setRect().y += newProj.getSpeed();
                    });

                    i++;
                    score->setText("Score: " + std::to_string(i));

                    manager.destroyOnCollision<Projectile, Character>("Projectile", "Enemy"); 

                    ses.add(tempProj);
                }
            });

            secondWeapon->setProjectile(nullptr);
            thirdWeapon->setProjectile(nullptr);
        }

        if(score->getContent() == "Score: " + std::to_string(100)){

            projectile->setBehaviour([&](Projectile& proj){
                if(manager.detectCollision<Projectile, Character>("Projectile", "Enemy")){
                    Projectile* tempProj = Projectile::getCopy(proj);
                    tempProj->setID("SecondProjectile");

                    Projectile* secondTempProj = Projectile::getCopy(proj);
                    secondTempProj->setID("ThirdProjectile");

                    tempProj->setRect().x = manager.returnLeft<Projectile, Character>("Projectile", "Enemy")->getRect().x;
                    tempProj->setRect().y = manager.returnLeft<Projectile, Character>("Projectile", "Enemy")->getRect().y;

                    secondTempProj->setRect().x = manager.returnLeft<Projectile, Character>("Projectile", "Enemy")->getRect().x;
                    secondTempProj->setRect().y = manager.returnLeft<Projectile, Character>("Projectile", "Enemy")->getRect().y;

                    tempProj->setBehaviour([](Projectile& newProj){
                        newProj.setRect().x += newProj.getSpeed();
                        newProj.setRect().y += newProj.getSpeed();
                    });

                    secondTempProj->setBehaviour([](Projectile& newProj){
                        newProj.setRect().x -= newProj.getSpeed();
                        newProj.setRect().y += newProj.getSpeed();
                    });

                    i++;
                    score->setText("Score: " + std::to_string(i));

                    manager.destroyOnCollision<Projectile, Character>("Projectile", "Enemy"); 

                    ses.add(tempProj);
                    ses.add(secondTempProj);
                }
            });
        }

        if(time->getContent() == "Time: " + std::to_string(15) && spawnerCount == 1){
            Spawner* secondSpawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 20, 1.0f);
            ses.add(secondSpawner);
            spawnerCount++;
        }

        if(time->getContent() == "Time: " + std::to_string(50) && spawnerCount == 2){
            Spawner* thirdSpawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 20, 1.0f);
            ses.add(thirdSpawner);
            spawnerCount++;
        }

        if(time->getContent() == "Time: " + std::to_string(80) && spawnerCount == 3){
            enemy->setSpeed(enemy->getSpeed() + 2);
            Spawner* fourthSpawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 20, 1.0f);
            ses.add(fourthSpawner);
            spawnerCount++;
        }

        if(time->getContent() == "Time: " + std::to_string(150) && spawnerCount == 4){
            enemy->setSpeed(enemy->getSpeed() + 4);
            Spawner* fifthSpawner = Spawner::getInstance(0, 0, "Spawner", enemy, ses, 800, 100, 100, 1.0f);
            ses.add(fifthSpawner);
            spawnerCount++;
        }

        if(manager.detectCollision<Projectile, Character>("Projectile", "Enemy")
        || manager.detectCollision<Projectile, Character>("SecondProjectile", "Enemy")
        || manager.detectCollision<Projectile, Character>("ThirdProjectile", "Enemy")){
            i++;
            score->setText("Score: " + std::to_string(i));
        }

        manager.destroyOnCollision<Projectile, Character>("Projectile", "Enemy"); 
        manager.destroyOnCollision<Projectile, Character>("SecondProjectile", "Enemy"); 
        manager.destroyOnCollision<Projectile, Character>("ThirdProjectile", "Enemy"); 

        if(time->getContent() == "Time: " + std::to_string(200) || manager.detectCollision<Character, Character>("Main Character", "Enemy")){
            Label* finalScore = Label::getInstance(170, 250, 30, 60, "Final Score: " + std::to_string(i * (int)time->getTime()), "FinalScore");
            finalScore->setColor(255, 255, 255);

            for(Component* c : ses.getComp()){
                ses.remove(c);
            }
            
            ses.add(finalScore);
        }
    });

    ses.add(weaponManager);

    ses.run();

    return 0;
}
