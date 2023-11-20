#ifndef CHARACTER_H
#define CHARACTER_H
#include "Component.h"
#include <SDL2/SDL.h>

namespace gameengine{
    class Character: public Component{
        public:
            static Character* getInstance(int x, int y, int w, int h, const char* imagePath, bool mControl, bool kControl);
            ~Character();

            void render() const;
            void controls(bool &mControl, bool &kControl);
        protected:
            Character(int x, int y, int w, int h, const char* imagePath, bool mControl, bool kControl);
        private:
            bool mControl;
            bool kControl;
            const char* myPath;
            SDL_Surface* surf;
            SDL_Texture* texture;
    };
}

#endif