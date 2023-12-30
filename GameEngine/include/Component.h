#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>
#include <string>
#include <functional>

namespace gameengine {
    class Component {
    public:
        virtual ~Component();

        virtual void mouseDown(const SDL_Event&) {}
        virtual void mouseUp(const SDL_Event&) {}
        virtual void keyDown(const SDL_Event&) {}
        virtual void keyUp(const SDL_Event&) {}
        virtual void render() const {}

        const SDL_Rect& getRect() const { return rect; }
        SDL_Rect& setRect() { return rect; }
        const std::string& getId() const { return id; }
        void setID(std::string newID){ id = newID; };
        virtual void updatePosition() {}

        bool operator==(const Component& other) const {
            // Compare attributes for equality
            return (this->getRect().x == other.getRect().x) &&
            (this->getRect().y == other.getRect().y) &&
            (this->getRect().w == other.getRect().w) &&
            (this->getRect().h == other.getRect().h) &&
            (this->getId() == other.getId());
        }   

        template <typename T>
        const bool isTouching(T* target) const {

        
        SDL_Rect rect1 = this->getRect();
        SDL_Rect rect2 = target->getRect();

        // Check if the rectangles overlap
        if (SDL_HasIntersection(&rect1, &rect2)) { return true; }

        // No collision detected
        return false;
    }   

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
