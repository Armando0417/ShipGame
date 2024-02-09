#include "ofApp.h"


//--------------------------------------------------------------

void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetEscapeQuitsApp(false);


    //Sound
    SoundManager::loadSong("intro", "bin\\data\\Sounds\\Great Void Sea Battle.mp3");
    SoundManager::loadSong("battle", "bin\\data\\Sounds\\Cosmic Sea of Trees.mp3");
    SoundManager::loadSong("shipExplosion", "bin\\data\\Sounds\\shipExplosion.wav");
    SoundManager::loadSong("bulletSound", "bin\\data\\Sounds\\shootingSound.mp3");
    SoundManager::loadSong("ORT_Xibalba", "bin\\data\\Sounds\\ORT Xibalba.mp3");
    SoundManager::loadSong("ORT_UFO", "bin\\data\\Sounds\\ORT_UFO.mp3");
    SoundManager::loadSong("button", "bin\\data\\Sounds\\buttonInteract.mp3");

//States
    intro = new IntroState();
    battle = new ShipBattle();

    currentState = intro; //Setting the starting state

}

//--------------------------------------------------------------

void ofApp::update(){
    currentState->update();

    if(currentState->hasFinished()){
        if(currentState->getNextState() == "IntroState"){
            currentState = intro;
        }
        else if(currentState->getNextState() == "BattleState"){
            currentState = battle;
        }
    }

}

//--------------------------------------------------------------

void ofApp::draw(){
    currentState->draw();
 

}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    currentState->keyPressed(key);
}

//--------------------------------------------------------------

void ofApp::keyReleased(int key){
    currentState->keyReleased(key);
}

//--------------------------------------------------------------

void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button){
    currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------

void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------

void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------

void ofApp::mouseExited(int x, int y){

}


//--------------------------------------------------------------

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------

void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------

void ofApp::gotMessage(ofMessage msg) {

}


//-------------------- Section for added utility methods -------

