#ifndef LABEL_H
#define LABEL_H
#include "Component.h"
#include <string>
#include <SDL2/SDL.h>

namespace gameengine{
    class Label: public Component{
        public:
            Label(int x, int y, int w, int h, std::string text);
            void render() const;
            ~Label();
        private:
            std::string content;
            SDL_Texture* texture;
    };
}

#endif