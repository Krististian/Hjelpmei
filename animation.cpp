#include "animation.h"
#include "Powder.h"
#include "TestPowder.h"


void runGame(){
    TestWindow window;
    FallingPowder testPow{{10,10}};
    Powder floor {{10,30}};
    while(!window.should_close()) {
        testPow.fall();
        window.draw_rectangle(testPow.getPosition(), powW, powH);
        window.colourGridOccupy();
        window.next_frame();
        cout << testPow.somethingUnder(testPow.getVel()) << endl;
    }
}