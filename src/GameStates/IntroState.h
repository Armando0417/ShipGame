#include "State.h"

class IntroState : State{
    private:
        ofImage titleImage;


    IntroState();
    void update();
    void draw();
    void reset();
    void keyPress(int key);


    ~IntroState(){
        
    }

};