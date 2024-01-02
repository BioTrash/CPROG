#include "Session.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <SDL2/SDL_image.h>

#define FPS 60

namespace gameengine{

    void Session::add(Component* c){
        added.push_back(c);
    }
    
    void Session::remove(Component* c) {
        removed.push_back(c);
    }

    void Session::run(){
        bool quit = false;
        const int tickInterval = 1000/FPS;
        Uint32 nextTick;
        int delay;

        SDL_Texture* backgroundTexture = nullptr;
        if(imagePath != nullptr){
            backgroundTexture = IMG_LoadTexture(sys.getRen(), imagePath);
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
                    remove(c);
                }
            }

            for(Component* c : added){
                comp.push_back(c);
            }
            added.clear();

            for(Component* c: removed){
                for(std::vector<Component*>::iterator i = comp.begin(); i != comp.end();){
                    if(*i == c ){
                        i = comp.erase(i);
                    }
                    else{
                        i++;
                    }
                }
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