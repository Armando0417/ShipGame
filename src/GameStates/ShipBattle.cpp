#include "ShipBattle.h"

ShipBattle::ShipBattle(){
    this->player = new Player(ofGetWidth()/2, ofGetHeight()/2);
    this->enemyTimer = 0;
    this->playerScore = 0;
    this->killspreeTimer = 0;
    bossIsActive = false;
    bossIndex = 0;


    shipDestroyed.load("bin\\data\\Sounds\\shipExplosion.wav");
    font.load("bin\\data\\Fonts\\Orbitron.ttf", 20, true, true, false, 0.3, 0);
    backgroundImage.load("bin\\data\\Menu Images\\BattleArea.jpg");

    music.load("bin\\data\\Sounds\\Cosmic Sea of Trees.mp3");
    

    // music.play();

}

ofVec2f ShipBattle::getRandomEdgePoint(){
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

/**
 * Update function for managing enemy spawn, player movement, enemy movement and hit detection, bullet updates, and state switching.
 */
void ShipBattle::update(){
    //Enemy spawn logic

    enemyTimer += 1;

    if(killspreeTimer > 0) killspreeTimer -= 1;  

    // Enemy spawn logic
   if(playerScore > 10000 && !bossIsActive) {   //ORT UFO Boss Encounter
        // music.stop();
        activateBoss();
    }

    if(playerScore > 25000 && !bossIsActive) {   //ORT Xibalba Boss Encounter
        activateBoss();
    }


    if (playerScore > 20 && !bossIsActive) {
        ORT* ORT_Boss = new ORT(0, ofGetHeight() / 2, "ORT");
        // music.stop();
        // ofSleepMillis(1000);
        // UFO* UFO_ORT = new UFO(ofGetWidth()/2 - 100, 20, "Galactica Supercell ORT");
        enemyList.push_back(ORT_Boss);
        // enemyList.push_back(UFO_ORT);
        // bossList.push_back(UFO_ORT);
        bossIsActive = true; 
    }

    if(playerScore < 100) {
        if( enemyTimer % 100 == 0 && enemyList.size() < 10 ) {     // increase in difficulty can be changed here
            ofPoint randPosition = getRandomEdgePoint(); 
            EnemyShip* tempEnemy = new EnemyCruiser(randPosition.x, randPosition.y);
            enemyList.push_back(tempEnemy);
            enemyTimer = 0;
        }
    }

    else {

        if( enemyTimer % 50 == 0 && enemyList.size() < 20 ) { 
            
            // if(!bossIsActive){

            ofPoint randPosition = getRandomEdgePoint();
            EnemyShip* tempEnemy = new EnemyVanguard(randPosition.x, randPosition.y);
            enemyList.push_back(tempEnemy);
            enemyTimer = 0;
            }    // increase in difficulty can be changed here
        }

        
    

//Movement logic for player 
    this->player->processPressedKeys();
    this->player->update();
    wrapCoords(this->player->pos);



//Movement and hit detection for enemies
    for(unsigned int i = 0; i < enemyList.size(); i++){
        EnemyShip* enemy = enemyList[i];
        enemy->update(this->player->pos);
        
        unsigned int index = i; 
        

        for (Projectiles p : this->player->bullets) {
            
               if(enemy->getHitBox()->isHit(p)){
                
                if(player->health + 5 >= 100) {
                    player->health = 100;  
                }

                else {
                    player->health = player->health + 3.0;  //Healing once you kill an enemy 
                }

                enemy->takeDamage(p.getDamage());

                if(enemy->isDead()) {   // Remove the enemy from the list
                    enemyList.erase(enemyList.begin() + index);
                    shipDestroyed.play();
                    playerScore += 20 * scoreMultiplier() * killSpreeMode();  //Score system
                    this->killspreeTimer = 150;
                }

            }
        }
    }

// Section for Updating bullets:
    
    //player projectiles
    if(this->player->bullets.size() > 0) {
        updateBullets();
    } 
    shotTimer(1);

    //enemy projectiles
    for(EnemyShip* enemy : enemyList){
        updateEnemyBullets(enemy);
        for(Projectiles p : enemy->getBullets()){
            if(player->hitBox.isHit(p)){
                if(player->health > 0){
                    if (player->health < 10) {
                        player->health -= player->health;   // To not go below 0
                    }
                    else {
                        player->health = player->health - 10;
                    }
                }
            }
        }
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


    if(bossIsActive){
        // font.drawString(bossList[bossIndex]->getName(), ofGetWidth() / 2 - 50, ofGetHeight() * 3/4 - 20);
    }


    player->draw();
    if(shot) draw_bullets();
    for(EnemyShip* e : enemyList){
        e->draw();
        if(e->getBullets().size() > 0){
            drawEnemyBullets(e);
        }
    }

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

void ShipBattle::drawEnemyBullets(EnemyShip* enemy){
    for(Projectiles p : enemy->getBullets()){
        p.draw();
    }
}

void ShipBattle::updateBullets(){
    for (unsigned int i = 0; i < this->player->bullets.size(); i++) {
       player->bullets[i].update();

        if (bulletIsOutOfBounds(player->bullets[i])) {
            player->bullets.erase(player->bullets.begin() + i);
        }
    }
}

void ShipBattle::updateEnemyBullets(EnemyShip* enemy){
    for (unsigned int i = 0; i < enemy->getBullets().size(); i++) {
       enemy->getBullets()[i].update();

        if (bulletIsOutOfBounds(enemy->getBullets()[i])) {
            enemy->getBullets().erase(enemy->getBullets().begin() + i);
        }
    }
}

bool ShipBattle::bulletIsOutOfBounds(Projectiles p){
    if (p.position.x < 0 || p.position.x > ofGetWidth() || p.position.y < 0 || p.position.y > ofGetHeight()) {
        return true; // Bullet is out of bounds
    }
    return false; // Bullet is within bounds

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

void ShipBattle::activateBoss(){
    if (bossIndex < bossList.size()) {
        // Activate the boss
        enemyList.push_back(bossList[bossIndex]);
        bossIsActive = true;
        bossIndex++;
    }
}