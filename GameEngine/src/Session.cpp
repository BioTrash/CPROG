#include "Session.h"
#include "System.h"
#include <SDL2/SDL.h>

namespace gameengine{

    void Session::add(Component* c){
        comp.push_back(c);
    }

    void Session::run(){
        bool quit = false;
        while (!quit){
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
                }
            }

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