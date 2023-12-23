#include "Weapon.h"
#include "System.h"
#include <SDL2/SDL_image.h>

namespace gameengine{

    Weapon::Weapon(int x, int y, int w, int h, std::string id, int speed, int amount, int spread, Session& ses, Character* target, Projectile* proj, const char* imagePath) : Component{x, y , w, h, id}, speed(speed), amount(amount), spread(spread), ses(ses), target(target), proj(proj), imagePath(imagePath){
        if(imagePath != NULL){
            surf = IMG_Load(imagePath);
            texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        }

        lastUpdateTime = std::chrono::high_resolution_clock::now();
    }

    Weapon* Weapon::getInstance(int x, int y, int w, int h, std::string id, int speed, int amount, int spread, Session& ses, Character* target, Projectile* proj, const char* imagePath){
        return new Weapon(x, y, w, h, id, speed, amount, spread, ses, target, proj, imagePath);
    }

    Weapon::~Weapon(){
        //if(imagePath != NULL) SDL_FreeSurface(surf);
    }

    void Weapon::render() const {
        SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
    }

    void Weapon::updatePosition(){
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count();

        if(target != nullptr){
            this->setRect().y = target->getRect().y;
            this->setRect().x = target->getRect().x + target->getRect().w / 2;
        }

        if(behaviourFunction) { //Has to be after target if-statement
            behaviourFunction(*this);
        }

        for(Component* projC : ses.getComp()){ //Need to be moved and made more flexible. This can be default but it need to be able to change. Set this as starting weapon behaviourFunction.
            if(projC->getId() == "Projectile"){
                Projectile* proj = dynamic_cast<Projectile*>(projC);
                for(Component* enemyC : ses.getComp()){
                    if(enemyC->getId() == "Enemy"){
                        Character* tempEnemy = dynamic_cast<Character*>(enemyC);

                        if(tempEnemy->isTouching(proj)){
                            tempEnemy->setBehaviour([&](Character& tempTarget){
                                ses.remove(tempTarget);
                            });
                            proj->setBehaviour([&](Projectile& tempTarget){
                                ses.remove(tempTarget);
                            });     
                        }
                    }
                }
            }
        }

        if(proj != nullptr){
            int characterCheck = 0;
            for(Component* c: ses.getComp()){
                if(c->getId() == proj->getId()) characterCheck++;
            }

            if (elapsedSeconds >= speed && characterCheck < amount) {

                lastUpdateTime = currentTime;

                spawn(proj->getBehaviour());
            }
        }
    }

    void Weapon::spawn(const std::function<void(Projectile&)>& behaviorFunction){
        proj->setRect().y = this->getRect().y;
        proj->setRect().x = this->getRect().x;


        Projectile* tempProj = Projectile::getCopy(*proj);
        tempProj->setBehaviour(behaviorFunction);

        ses.add(tempProj);
    }
}