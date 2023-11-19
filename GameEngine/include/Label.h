#ifndef LABEL_H
#define LABEL_H
#include "Component.h"
#include <string>
#include <SDL2/SDL.h>

namespace gameengine{
    class Label: public Component{
        public:
            static Label* getInstance(int x, int y, int w, int h, std::string text);
            void render() const;
            std::string getContent() const;
            void setText(std::string newText);
            ~Label();
        protected:
            Label(int x, int y, int w, int h, std::string text);
        private:
            std::string content;
            SDL_Texture* texture;
    };
}

#endif