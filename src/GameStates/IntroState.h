#include "State.h"

class IntroState : public State{
    private:
        ofImage titleImage;

    public:
        IntroState();
        void update();
        void draw();
        void reset();
        void keyPressed(int key);
        void keyReleased(int key);

        ~IntroState(){ }

};