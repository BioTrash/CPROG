// Rufus Trukhin rutr7079 | CPROG  Programmeringsprojekt
#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace gameengine{
    class System{
        public:
            System();
            ~System();

            SDL_Renderer* getRen() const;
            TTF_Font* getFont() const;
            SDL_Window* getWindow() const;
            
            int getHeight() { return winHeight; };
            int getWidth() {return winWidth; };

        private:
            SDL_Window* win;
            SDL_Renderer* ren;
            TTF_Font* font;
            int winHeight;
            int winWidth;
    };

    extern System sys;
}

#endif