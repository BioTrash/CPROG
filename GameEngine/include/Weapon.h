#ifndef WEAPON_H
#define WEAPON_H
#include "Character.h"
#include "Component.h"
#include "Session.h"
#include "Projectile.h"
#include <string>
#include <utility>
#include <chrono>
#include <functional>
#include <SDL2/SDL.h>

namespace gameengine{
    class Weapon : public Component {
        public:
            ~Weapon();
            static Weapon* getInstance(int x, int y, int w, int h, std::string id, int speed, int amount, int spread, Session& ses, Character* target = nullptr, Projectile* proj = nullptr, std::string imagePath = "");
            //static Weapon* getCopy(const Weapon& other);
            /* void render() const; */
            void updatePosition() override;
            void spawn(const std::function<void(Projectile&)>& behaviorFunction);
            void setProjectile(Projectile* newProj) { proj = newProj; };
            
            void setBehaviour(const std::function<void(Weapon&)>& behaviour) { behaviourFunction = behaviour; };
            const std::function<void(Weapon&)>& getBehaviour() { return behaviourFunction; };

            template <typename T, typename U>
            void destroyOnCollision(std::string param1ID, std::string param2ID, bool destroyBoth = true){
                for(Component* c : ses.getComp()){
                    if(c->getId() == param1ID){
                        T* foundC = dynamic_cast<T*>(c);

                        for(Component* otherC : ses.getComp()){
                            if(otherC->getId() == param2ID){
                                U* foundOtherC = dynamic_cast<U*>(otherC);

                                if(foundOtherC->isTouching(foundC)){

                                    if(!destroyBoth){ses.remove(otherC);}
                                    else{
                                        ses.remove(c);
                                        ses.remove(otherC);
                                    }

                                }
                            }
                        }
                    }
                }
            }
            
            template <typename T, typename U>
            bool detectCollision(std::string param1ID, std::string param2ID){
                for(Component* c : ses.getComp()){
                    if(c->getId() == param1ID){
                        T* foundC = dynamic_cast<T*>(c);

                        for(Component* otherC : ses.getComp()){
                            if(otherC->getId() == param2ID){
                                U* foundOtherC = dynamic_cast<U*>(otherC);

                                if(foundOtherC->isTouching(foundC)){
                                    return true;
                                }
                            }
                        }
                    }
                }

                return false;
            }

        protected:
            Weapon(int x, int y, int w, int h, std::string id, int speed, int amount, int spread, Session& ses, Character* target = nullptr, Projectile* proj = nullptr, std::string imagePath = "");
            //Weapon(const Weapon& other);
        private:   
            int speed;
            int amount;
            int spread;
            Session& ses;
            Character* target;
            Projectile* proj;
            std::string imagePath;

            SDL_Surface* surf;
            SDL_Texture* texture;

            std::function<void(Weapon&)> behaviourFunction;

            std::chrono::high_resolution_clock::time_point lastUpdateTime;
    };
}
#endif