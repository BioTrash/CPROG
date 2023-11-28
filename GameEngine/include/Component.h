#ifndef COMPONENT_H
#define COMPONENT_H
#include <SDL2/SDL.h>
#include <string>

namespace gameengine{
    class Component{
        public:
            virtual ~Component();

            virtual void mouseDown(const SDL_Event&) {}
            virtual void mouseUp(const SDL_Event&) {}
            virtual void keyDown(const SDL_Event&) {}
            virtual void keyUp(const SDL_Event&) {}
            virtual void render() const = 0;

            const SDL_Rect& getRect() const { return rect; }
            const std::string& getId() const { return id; }
            virtual void updatePosition() {};

        protected:
            Component(int x, int y, int w, int h, std::string id);
        private:
            SDL_Rect rect;
            std::string id;
            Component(const Component&) = delete;
            const Component& operator=(const Component&) = delete;
    };
}

#endif