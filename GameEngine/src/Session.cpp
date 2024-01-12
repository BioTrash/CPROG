#include "Session.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <SDL2/SDL_image.h>

#define FPS 60

namespace gameengine{

    void Session::add(Component* c){
        int count = std::count(added.begin(), added.end(), c);

        if (count == 0) {
            added.push_back(c);
        }
        else{
            return;
        }
    }

    void Session::protect(Component* c){
        int count = std::count(irremovable.begin(), irremovable.end(), c);

        if (count == 0) {
            irremovable.push_back(c);
        }
        else{
            return;
        }
    }
    
    void Session::remove(Component* c) {
        int count = std::count(removed.begin(), removed.end(), c);

        if (count == 0) {
            removed.push_back(c);
        }
        else{
            return;
        }
    }

    void Session::run(){
        bool quit = false;
        const int tickInterval = 1000/FPS;
        Uint32 nextTick;
        int delay;

        SDL_Texture* backgroundTexture = nullptr;
        if(!imagePath.empty()){
            backgroundTexture = IMG_LoadTexture(sys.getRen(), imagePath.c_str());
        }

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

            delay = nextTick - SDL_GetTicks();
            if(delay > 0) SDL_Delay(delay);

            for (Component* c : comp) {
                c->updatePosition();
            }

            for(Component* c : comp){
                if(c->getRect().x < 0 || c->getRect().x >= sys.getWidth() || c->getRect().y < 0 || c->getRect().y >= sys.getHeight()){
                    auto it = std::find(irremovable.begin(), irremovable.end(), c);

                    if (it != irremovable.end()) {
                        continue;
                    } else {
                        remove(c);
                    }
                }
            }

            for(Component* c : added){
                comp.push_back(c);
            }
            added.clear();

            for(Component* c: removed){
                comp.erase(std::remove(comp.begin(), comp.end(), c), comp.end());
                delete c;
            }
            removed.clear();
            
            if(backgroundTexture){
                SDL_RenderCopy(sys.getRen(), backgroundTexture, NULL, NULL);
            }
            else{
                SDL_SetRenderDrawColor(sys.getRen(), 255, 255, 255, 255);
            }

            for(Component* c : comp){ //Render order is important
                c->render();
            }
            
            SDL_RenderPresent(sys.getRen());

            SDL_RenderClear(sys.getRen());
        }

        if(backgroundTexture){
            SDL_DestroyTexture(backgroundTexture);
        }

    }

    Session::~Session(){
        
    }
}