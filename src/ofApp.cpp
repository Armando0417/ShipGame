#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
    ofSetFrameRate(60);

    this->playerP = new Player(ofGetWidth()/2, ofGetHeight()/2);
    enemyTimer = 0;

    shipDestroyed.load("bin\\data\\Sounds\\shipExplosion.wav");
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

void ofApp::update(){

//Enemy spawn logic
    enemyTimer += 1;
    if(enemyTimer % 100 == 0 && enemyList.size() < 10){
        ofPoint randPosition = getRandomEdgePoint();
        EnemyShip* tempEnemy = new EnemyShip(randPosition.x, randPosition.y, 2.5);
        enemyList.push_back(tempEnemy);
        enemyTimer = 0;
    }

//Movement logic for player 
    this->playerP->processPressedKeys();
    this->playerP->update();
    wrapCoords(this->playerP->pos);


//Movement and hit detection for enemies
    for(int i = 0; i < enemyList.size(); i++){
        EnemyShip* enemy = enemyList[i];
        enemy->update(this->playerP->pos);
        int index = i;
        for(Projectiles p : this->playerP->bullets){
            if(enemy->enemyHitBox.isHit(p)){
                playerP->health = playerP->health + 5; 
                enemyList.erase(enemyList.begin() + index);
                shipDestroyed.play();
            }
        }

    }


// Section for Updating bullets:
    //player projectiles
    if(this->playerP->bullets.size() > 0) updateBullets(); 
    shotTimer(10);

    //enemy projectiles
    for(EnemyShip* enemy : enemyList){
        enemy->shotTimer++;
        updateEnemyBullets(enemy);
        for(Projectiles p : enemy->enemyBullets){
            if(playerP->hitBox.isHit(p)){
                playerP->health = playerP->health - 10;
            }
        }
    }

}

//--------------------------------------------------------------

void ofApp::draw(){
    ofBackground(0); //set the screen to black

    if(shot) draw_bullets();

    playerP->draw();    

    for(EnemyShip* eShip : enemyList){
        eShip->draw();
        if(eShip->enemyBullets.size() > 0){
            drawEnemyBullets(eShip);
        }
    }

    healthBar(this->playerP->health, 100);

}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    this->playerP->addPressedKey(key); //adds the key to the vector to handle the movement
    
    if(key == ' '){
        if(canShoot){
            playerP->shoot();
            this->shot = true; //set to true to draw the bullets
            this->canShoot = false; //set to false to start the timer
            this->timer = 0; //starts the timer with a value of 0
            }
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

}

//--------------------------------------------------------------

void ofApp::gotMessage(ofMessage msg) {

}


//-------------------- Section for added utility methods -------

void ofApp::healthBar(int currHealth, int maxHealth){ 
    ofNoFill();
    ofDrawRectangle(10, 40, maxHealth *2, 20);
    ofFill();
    ofSetColor(ofColor::green);
    ofDrawRectangle(10, 40, currHealth *2, 20);
    ofSetColor(ofColor::white);
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

void ofApp::updateBullets() {
    for (unsigned int i = 0; i < this->playerP->bullets.size(); i++) {
       playerP->bullets[i].update();

        if (bulletIsOutOfBounds(playerP->bullets[i])) {
            playerP->bullets.erase(playerP->bullets.begin() + i);
        }
    }
}

void ofApp::updateEnemyBullets(EnemyShip* enemy){
    for (unsigned int i = 0; i < enemy->enemyBullets.size(); i++) {
       enemy->enemyBullets[i].update();

        if (bulletIsOutOfBounds(enemy->enemyBullets[i])) {
            enemy->enemyBullets.erase(enemy->enemyBullets.begin() + i);
        }
    }
}

void ofApp::draw_bullets() {
    for (unsigned int i = 0; i < this->playerP->bullets.size(); i++) {
        this->playerP->bullets[i].draw();
    }
}

void ofApp::drawEnemyBullets(EnemyShip* enemy){
    for(Projectiles p : enemy->enemyBullets){
        p.draw();
    }
}

void ofApp::shotTimer(int time){
    if(!canShoot) this->timer += 1;

    if(this->timer == time) this->canShoot = true;
}

