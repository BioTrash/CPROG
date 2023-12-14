// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <string>
#include <functional>

namespace gameengine {
    class Character : public Component {
    public:
        static Character* getInstance(int x, int y, int w, int h, const char* imagePath, int speed, std::string id, bool controlable = false, bool mControl = false);
        static Character* getCopy(const Character& other);
        ~Character();
        Uint32* getPixel() const { return static_cast<Uint32*>(surf->pixels); };
        const bool isTouching(Character* target) const;
        void render() const;
        void updatePosition() override;
        void keyDown(const SDL_Event& event) override;
        void keyUp(const SDL_Event& event) override;

        void setBehaviour(const std::function<void(Character&)>& behaviour) { behaviourFunction = behaviour; };
        const std::function<void(Character&)>& getBehaviour() { return behaviourFunction; };

    protected:
        Character(const Character& other);
        Character(int x, int y, int w, int h, const char* imagePath, int speed, std::string id, bool controlable = false, bool mControl = false);

    private:
        const char* imagePath;
        int speed;
        bool controlable;
        bool mControl;

        SDL_Surface* surf;
        SDL_Texture* texture;

        std::function<void(Character&)> behaviourFunction;

        bool upPressed = false;
        bool downPressed = false;
        bool leftPressed = false;
        bool rightPressed = false;
    };
}

#endif
