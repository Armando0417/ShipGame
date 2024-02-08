#include "ofApp.h"


//--------------------------------------------------------------

void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetEscapeQuitsApp(false);


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

