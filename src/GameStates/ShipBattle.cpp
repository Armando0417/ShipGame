#include "ShipBattle.h"

ShipBattle::ShipBattle(){
    this->player = new Player(ofGetWidth()/2, ofGetHeight()/2);

    this->playerScore = 0;
    this->killspreeTimer = 0;
    
    font.load("bin\\data\\Fonts\\Orbitron.ttf", 20, true, true, false, 0.3, 0);
    backgroundImage.load("bin\\data\\Menu Images\\BattleArea.jpg");

    music.load("bin\\data\\Sounds\\Cosmic Sea of Trees.mp3");
    

    music.play();

}


/**
 * Update function for managing enemy spawn, player movement, enemy movement and hit detection, bullet updates, and state switching.
 */
void ShipBattle::update(){
    
    EnemyManager::updateEnemies(player);
    
//Movement logic for player 
    this->player->processPressedKeys();
    this->player->update();
    wrapCoords(this->player->pos);
    

    playerScore += EnemyManager::getPointsScored() * scoreMultiplier() * killSpreeMode();
    this->player->setScore(playerScore);
    killspreeTimer = EnemyManager::getKillSpreeTimer();

    //player projectiles
    if(this->player->bullets.size() > 0) {
        updateBullets();
    } 
//Section for switching states:
    if(this->player->health <= 0){
        //@TODO add logic for releasing memory allocation
        this->setNextState("IntroState");
        this->setFinished(true);
    }


}

void ShipBattle::shotTimer(int time){
    if(!canShoot) this->timer += 1;
    if(this->timer == time) this->canShoot = true;
}

void ShipBattle::draw(){
    ofSetBackgroundColor(ofColor::black);
    backgroundImage.draw(0, 0, ofGetWidth(), ofGetHeight());

    ofSetColor(ofColor::white); // Set text color to white
    font.drawString("SCORE " + to_string(playerScore), ofGetWidth() / 2 - 50, 50);

    EnemyManager::drawEnemies();


    player->draw();
    if(shot) draw_bullets();
    

    healthBar(player->health, 100);
    killSpreeTimer(this->killspreeTimer, 150);
}   

void ShipBattle::reset(){


}

void ShipBattle::keyPressed(int key){
    player->addPressedKey(key);
}


void ShipBattle::keyReleased(int key){
        key = tolower(key);
        this->player->keyMap[key] = false;
}
void ShipBattle::mousePressed(int x, int y, int button){
    
}


void ShipBattle::wrapCoords(ofPoint &currentPos){
    if(currentPos.x < 0.0) 
        currentPos.x = ofGetWidth() - 10;
    
    if(currentPos.x >= ofGetWidth()) 
        currentPos.x = 10;
    
    if(currentPos.y < 0.0) 
        currentPos.y = ofGetHeight() - 10;    
    
    if(currentPos.y >= ofGetHeight()) 
        currentPos.y = 10;
}

void ShipBattle::draw_bullets(){
    for (unsigned int i = 0; i < this->player->bullets.size(); i++) {
        this->player->bullets[i].draw();
    }
}



void ShipBattle::updateBullets(){
    for (unsigned int i = 0; i < this->player->bullets.size(); i++) {
       player->bullets[i].update();

        // if (player->bullets[i].bulletIsOutOfBounds()) {
        //     player->bullets.erase(player->bullets.begin() + i);
        // }
    }
}



double ShipBattle::killSpreeMode() {
    if(this->killspreeTimer > 0) return 1.5;
    else return 1.0;
}

double ShipBattle::scoreMultiplier() {
    if (playerScore >= 350) return 3.5;
    
    else if (playerScore >= 200) return 2.5;
    
    else if (playerScore >= 100) return 1.5; 
    
    else return 1.0; // Default multiplier
    
}

