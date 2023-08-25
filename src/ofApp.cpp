#include "ofApp.h"

//--------------------------------------------------------------

/*
Periodically voy a create un enemy y voy a place them in a vector
then iterate through the vector and draw and update them



*/
void ofApp::setup(){
    
    this->playerP = new Player(ofGetWidth()/2, ofGetHeight()/2);
    
    useFirstShip = true;
    useSecondShip = false;

    this->enemyP = new EnemyShip(ofGetWidth()/4, ofGetHeight()/4, 2.5);


    enemyTimer = 0;



}


//--------------------------------------------------------------
ofVec2f getRandomEdgePoint() {
    int edge = ofRandom(4);  // Select a random edge (0: top, 1: right, 2: bottom, 3: left)
    float x, y;
    
    if (edge == 0) {  // Top edge
        x = ofRandomWidth();
        y = 0;
    } else if (edge == 1) {  // Right edge
        x = ofGetWidth();
        y = ofRandomHeight();
    } else if (edge == 2) {  // Bottom edge
        x = ofRandomWidth();
        y = ofGetHeight();
    } else {  // Left edge
        x = 0;
        y = ofRandomHeight();
    }
    
    return ofVec2f(x, y);
}




void ofApp::shotTimer(int time){
    if(!canShoot) this->timer += 1;

    if(this->timer == time) this->canShoot = true;
}




//--------------------------------------------------------------

void ofApp::update(){
    enemyTimer += 1;
    if(enemyTimer % 100 == 0 && enemyList.size() < 10){
        ofPoint randPosition = getRandomEdgePoint();
        EnemyShip* tempEnemy = new EnemyShip(randPosition.x, randPosition.y, 5.0);
        enemyList.push_back(tempEnemy);
        enemyTimer = 0;
    }
    
    if(useFirstShip){
        this->playerP->processPressedKeys();
        this->playerP->update();
        wrapCoords(this->playerP->pos);
    }

    for(int i = 0; i < enemyList.size(); i++){
        EnemyShip* enemy = enemyList[i];
        enemy->update(this->playerP->pos);
        int index = i;
        for(Projectiles p : this->playerP->bullets){
            if(enemy->enemyHitBox.isHit(p)){
                enemyList.erase(enemyList.begin() + index);
            }
        }

    }


if(useFirstShip){
    if(this->playerP->bullets.size() > 0){
        updateBullets();
    }
}

    shotTimer(10);



}

//--------------------------------------------------------------

void ofApp::draw(){
    ofBackground(0);

    if(shot){
        if(useFirstShip) draw_bullets();
    }


    playerP->draw();
    enemyP->draw();

    for(EnemyShip* eShip : enemyList){
        eShip->draw();
    }


    string timerString = to_string(this->timer);
    ofDrawBitmapString(timerString, 10, 10);
    string orientation = to_string(playerP->shipOrientation);
    
    ofDrawBitmapString(orientation, 20, 20);
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    if(useFirstShip) this->playerP->addPressedKey(key);
    
    if(key == ' '){
        if(canShoot){
            if(useFirstShip) playerP->shoot();



            this->shot = true;
            this->canShoot = false;
            this->timer = 0;
        }
        
    }

    if(key == '1'){
        useFirstShip = true;
        useSecondShip = false;
    }
    if(key == '2'){
        useFirstShip = false;
        useSecondShip = true;
    }

}

//--------------------------------------------------------------

void ofApp::keyReleased(int key){
    this->playerP->keyMap[key] = false;
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


void ofApp::draw_bullets() {
    for (unsigned int i = 0; i < this->playerP->bullets.size(); i++) {
        this->playerP->bullets[i].draw();
    }
}

//--------------------------------------------------------------

void ofApp::updateBullets(Player &ship) {
    for (unsigned int i = 0; i < ship.bullets.size(); i++) {
       ship.bullets[i].update();

        if (bulletIsOutOfBounds(ship.bullets[i])) {
            ship.bullets.erase(ship.bullets.begin() + i);
        }
    }
}


void ofApp::draw_bullets(Player &ship) {
    for (unsigned int i = 0; i < ship.bullets.size(); i++) {
        ship.bullets[i].draw();
    }
}