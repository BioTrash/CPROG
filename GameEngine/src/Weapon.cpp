#include "Weapon.h"
#include "System.h"
#include <SDL2/SDL_image.h>

namespace gameengine{

    Weapon::Weapon(int x, int y, int w, int h, std::string id, Character* target, int speed, int amount, int spread, Session& ses, Projectile* proj, const char* imagePath) : Component{x, y , w, h, id}, speed(speed), amount(amount), spread(spread), ses(ses), proj(proj), imagePath(imagePath){
        if(imagePath != NULL){
            surf = IMG_Load(imagePath);
            texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        }

        lastUpdateTime = std::chrono::high_resolution_clock::now();
    }

    Weapon* Weapon::getInstance(int x, int y, int w, int h, std::string id, Character* target, int speed, int amount, int spread, Session& ses, Projectile* proj, const char* imagePath){
        return new Weapon(x, y, w, h, id, target, speed, amount, spread, ses, proj, imagePath);
    }

    void Weapon::render() const {
        SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
    }

    void Weapon::updatePosition(){
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count();

        int characterCheck = 0;
        for(Component* c: ses.getComp()){
            if(c->getId() == proj->getId()) characterCheck++;
        }

        if (elapsedSeconds >= speed && characterCheck < amount) {

            lastUpdateTime = currentTime;

            // Pass the behavior function to the spawned character
            spawn(proj->getBehaviour());
        }
    }

    void Weapon::spawn(const std::function<void(Projectile&)>& behaviorFunction){
        Projectile* tempProj = Projectile::getCopy(*proj);
        tempProj->setBehaviour(behaviorFunction);

        ses.add(tempProj);
    }

    Weapon::~Weapon(){
        if(imagePath != NULL) SDL_FreeSurface(surf);
    }
}