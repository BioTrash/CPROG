#include <SDL2/SDL.h>
#include "Label.h"
#include "Session.h"

using namespace gameengine;

int main(int argc, char** argv){
    Session ses;
    Label* lbl = Label::getInstance(0, 0, 18, 36, "Hello, World!");
    ses.add(lbl);
    ses.run();

    return 0;
};