#pragma once 
#include "ofMain.h"

class State{ 

    protected:
        string nextState;
        ofSoundPlayer music;
        bool finished = false;

    public:
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void keyPressed(int key) = 0;
		virtual void keyReleased(int key) = 0;

        bool hasFinished() { return finished; }
        void setFinished(bool finished) { this-> finished = finished; }
        void setNextState(string nextState) { this->nextState = nextState; }        
        string getNextState(){ return this->nextState; }



        void toggleMusic() {
            // No music to play
            if (!music.isLoaded()) return;
            music.isPlaying() ? music.stop() : music.play();
        }
        

        ~State(){

        }
};  