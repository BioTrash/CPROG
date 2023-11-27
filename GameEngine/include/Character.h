#ifndef CHARACTER_H
#define CHARACTER_H
#include "Component.h"
#include <SDL2/SDL.h>

namespace gameengine{
    class Character: public Component{
        public:
            static Character* getInstance(int x, int y, int w, int h, const char* imagePath, bool mControl, bool kControl, int speed);
            ~Character();

            void render() const;
            void updatePosition(const SDL_Event& event) override;
            void keyDown(const SDL_Event& event) override;
            void keyUp(const SDL_Event& event) override;
            
        protected:
            Character(int x, int y, int w, int h, const char* imagePath, bool mControl, bool kControl, int speed);
        private:
            bool mControl;
            bool kControl;

            int speed;

            SDL_Surface* surf;
            SDL_Texture* texture;

            bool upPressed = false;
            bool downPressed = false;
            bool leftPressed = false;
            bool rightPressed = false;
    };
}

#endif