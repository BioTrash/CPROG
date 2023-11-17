#include <SDL2/SDL.h>
#include "Label.h"
#include "Session.h"

using namespace gameengine;

int main(int argc, char** argv){
    Session ses;
    Label lbl(100, 100, 200, 70, "Hej");
    ses.add(&lbl);
    ses.run();
    return 0;
};