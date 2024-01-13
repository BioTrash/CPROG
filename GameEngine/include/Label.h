// Rufus Trukhin rutr7079 | CPROG  Programmeringsprojekt
#ifndef LABEL_H
#define LABEL_H

#include "Component.h"
#include <string>
#include <chrono>
#include <SDL2/SDL.h>

namespace gameengine{
    class Label: public Component{
        public:
            static Label* getInstance(int x, int y, int w, int h, std::string text, std::string id);
            void render() const;
            std::string getContent() const;
            float getTime(){ return elapsedSeconds; }
            void setText(std::string newText);
            void setColor(Uint8 red, Uint8 green, Uint8 blue);
            void setTimer();

            void updatePosition() override;
            ~Label();
        protected:
            Label(int x, int y, int w, int h, std::string text, std::string id);
        private:

            std::string content;
            SDL_Texture* texture;

            Uint8 r = 0;
            Uint8 g = 0; 
            Uint8 b = 0;

            std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
            float elapsedSeconds;
            bool timerCheck = false; 
    };
}

#endif