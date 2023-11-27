#include "Session.h"
#include "System.h"
#include <SDL2/SDL.h>

#define FPS 120

namespace gameengine{

    void Session::add(Component* c){
        comp.push_back(c);
    }

    void Session::run(){
        bool quit = false;
        const int tickInterval = 1000/FPS;
        Uint32 nextTick;
        int delay;

        while (!quit){
            nextTick = SDL_GetTicks() + tickInterval;

            SDL_Event event;
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT: 
                        quit = true; 
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        for(Component* c : comp){
                            c->mouseDown(event);
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        for(Component* c : comp){
                            c->mouseUp(event);
                        }
                        break;
                    case SDL_KEYDOWN:
                        for(Component* c : comp){
                            c->keyDown(event);
                        }
                        break;
                    case SDL_KEYUP:
                        for(Component* c : comp){
                            c->keyUp(event);
                        }
                        break;
                    default:
                        break;
                }
            }

            for (Component* c : comp) {
            c->updatePosition(event);
            }

            delay = nextTick - SDL_GetTicks();
            if(delay > 0) SDL_Delay(delay);

            SDL_SetRenderDrawColor(sys.getRen(), 255, 255, 255, 255);

            SDL_RenderClear(sys.getRen());

            for(Component* c : comp){
                c->render();
            }
            SDL_RenderPresent(sys.getRen());
        }
    }

    Session::~Session(){
        
    }
}