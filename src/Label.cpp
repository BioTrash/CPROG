// Rufus Trukhin rutr7079 | CPROG  Programmeringsprojekt
#include "Label.h"
#include "System.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

using namespace std;

namespace gameengine{

    Label* Label::getInstance(int x, int y, int w, int h, string text, string id){

        int newW = w * text.length();
        return new Label(x, y, newW, h, text, id);
    }

    Label::Label(int x, int y, int w, int h, string text, string id): Component(x,y,w,h,id), content(text){
        SDL_Surface* surf = TTF_RenderText_Solid(sys.getFont(), content.c_str(), {r,g,b});
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }

    void Label::render() const {
        SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
    }

    Label::~Label(){
        SDL_DestroyTexture(texture);
    }

    string Label::getContent() const{
        return content;
    }

    void Label::updatePosition(){
        auto currentTime = std::chrono::high_resolution_clock::now();
        elapsedSeconds = std::chrono::duration<float>(currentTime - startTime).count();

        if(timerCheck) setText("Time: " + std::to_string(static_cast<int>(elapsedSeconds)));
    }

    void Label::setTimer(){
        startTime = std::chrono::high_resolution_clock::now();

        timerCheck ? timerCheck = false : timerCheck = true;
    }
    
    void Label::setColor(Uint8 red, Uint8 green, Uint8 blue){
        r = red;
        g = green;
        b = blue;
        setText(content);
    }

    void Label::setText(string newText){
        content = newText;
        SDL_DestroyTexture(texture);
        SDL_Surface* surf = TTF_RenderText_Solid(sys.getFont(), content.c_str(), {r, g, b ,0});

        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }
}