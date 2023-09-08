#include "IntroState.h"

IntroState::IntroState(){
    setNextState( "ShipBattle" );

}

void IntroState::update(){



}


void IntroState::draw(){
    ofSetBackgroundColor(ofColor::black);
}


void IntroState::keyPress(int key){
    setNextState("ShipBattle");
    setFinished(true);
}

void IntroState::reset(){
    setFinished(false);
    setNextState("");
}

