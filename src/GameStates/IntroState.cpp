#include "IntroState.h"

IntroState::IntroState(){
    titleImage.load("bin\\data\\Menu Images\\introWallpaper.jpg");
    
    SoundManager::setVolume("intro", 0.1);
    SoundManager::playSong("intro", true);


    Button* PlayButton = new Button(ofGetWidth()/2 - 100, ofGetHeight()/2, 200, 50, "", "Play");
    Button* PlayButton2 = new Button(ofGetWidth()/2 - 100, ofGetHeight()/2 + 100, 200, 50, "", "Hey There!");


    buttons.push_back(PlayButton);
    buttons.push_back(PlayButton2);
}

void IntroState::update() {
    if(buttons[0]->wasPressed()){
        SoundManager::stopSong("intro");
        SoundManager::playSong("battle", true);
        SoundManager::setVolume("battle", 0.1);
        this->setNextState("BattleState");
        this->setFinished(true);
    }


   for(Button* button : buttons) {
        button->update();
    }

}


void IntroState::draw(){
    ofSetBackgroundColor(ofColor::black);

    titleImage.draw((ofGetWidth() - titleImage.getWidth())/2, (ofGetHeight() - titleImage.getHeight())/2);


    //Draws All of the Buttons 
        for(Button* button : buttons){
            button->draw();
        }


}


void IntroState::keyPressed(int key){
    this->setNextState("BattleState");
    this->setFinished(true);
}

void IntroState::mousePressed(int x, int y, int button){
    for (Button* button : buttons){
        button->setPressed(x, y);
    }
}




void IntroState::keyReleased(int key){
    
}

void IntroState::reset(){
    setFinished(false);
    setNextState("");
}

