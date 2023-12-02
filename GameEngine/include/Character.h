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

        // Update setBehaviour to accept a std::function<void(Character&)>
        void setBehaviour(const std::function<void(Character&)>& behaviour) { behaviourFunction = behaviour; };
        const std::function<void(Character&)>& getBehaviour() const { return behaviourFunction; };
        void render() const;
        void updatePosition() override;
        void keyDown(const SDL_Event& event) override;
        void keyUp(const SDL_Event& event) override;

    protected:
        Character(const Character& other);
        Character(int x, int y, int w, int h, const char* imagePath, int speed, std::string id, bool controlable = false, bool mControl = false);

    private:
        const char* imagePath;
        int speed;
        bool controlable;
        bool mControl;
        std::function<void(Character&)> behaviourFunction; // Use std::function for storing the behavior function

        SDL_Surface* surf;
        SDL_Texture* texture;

        bool upPressed = false;
        bool downPressed = false;
        bool leftPressed = false;
        bool rightPressed = false;
    };
}

#endif
