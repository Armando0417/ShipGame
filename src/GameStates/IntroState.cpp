#include "IntroState.h"

IntroState::IntroState(){
  //TODO show the intro screen for the game

}

void IntroState::update(){


}


void IntroState::draw(){
    ofSetBackgroundColor(ofColor::white);
}


void IntroState::keyPressed(int key){
    this->setNextState("BattleState");
    this->setFinished(true);
}

void IntroState::keyReleased(int key){
    
}

void IntroState::reset(){
    setFinished(false);
    setNextState("");
}

