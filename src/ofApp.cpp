#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    this->playerP = new Player(ofGetWidth()/2, ofGetHeight()/2);
}
//--------------------------------------------------------------

bool ofApp::bulletIsOutOfBounds(Projectiles p){
    // Check if the Projectile's position is outside the screen bounds
    if (p.position.x < 0 || p.position.x > ofGetWidth() || p.position.y < 0 || p.position.y > ofGetHeight()) {
        return true; // Bullet is out of bounds
    }
    return false; // Bullet is within bounds
}

//--------------------------------------------------------------

void ofApp::updateBullets() {
    for (unsigned int i = 0; i < this->playerP->bullets.size(); i++) {
       playerP->bullets[i].update();

        if (bulletIsOutOfBounds(playerP->bullets[i])) {
            playerP->bullets.erase(playerP->bullets.begin() + i);
        }
    }
}

//--------------------------------------------------------------

void ofApp::draw_bullets() {
    for (unsigned int i = 0; i < this->playerP->bullets.size(); i++) {
        this->playerP->bullets[i].draw();
    }
}


//--------------------------------------------------------------

void ofApp::update(){
    this->playerP->processPressedKeys();    

    this->playerP->update();
    wrapCoords(this->playerP->pos);

    if(this->playerP->bullets.size() > 0){
        updateBullets();
    }

    if(!canShoot){
        this->timer += 1;
    }
    if(this->timer == 50){
        this->canShoot = true;
    }   

}

//--------------------------------------------------------------

void ofApp::draw(){
    ofBackground(0);

    if(shot) draw_bullets();
    playerP->draw();

    string timerString = to_string(this->timer);
    ofDrawBitmapString(timerString, 10, 10);

}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    this->playerP->addPressedKey(key);

    if(key == ' '){
        if(canShoot){
            playerP->shoot();
            this->shot = true;
            this->canShoot = false;
            this->timer = 0;
        }
        
    }

}

//--------------------------------------------------------------

void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------

void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button){

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
    // Implement if needed, or leave empty
}

//--------------------------------------------------------------

void ofApp::gotMessage(ofMessage msg) {
    // Implement if needed, or leave empty
}



void ofApp::wrapCoords(ofPoint &currentPos){

    if(currentPos.x < 0.0) currentPos.x = ofGetWidth() - 10;
    
    if(currentPos.x >= ofGetWidth()) currentPos.x = 10;
    
    if(currentPos.y < 0.0) currentPos.y = ofGetHeight() - 10;
    
    if(currentPos.y >= ofGetHeight()) currentPos.y = 10;
    


}