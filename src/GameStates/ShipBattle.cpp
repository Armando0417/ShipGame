#include "ShipBattle.h"

ShipBattle::ShipBattle(){
    this->player = new Player(ofGetWidth()/2, ofGetHeight()/2);
    this->enemyTimer = 0;
    shipDestroyed.load("bin\\data\\Sounds\\shipExplosion.wav");

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

void ShipBattle::update(){
//Enemy spawn logic
    enemyTimer += 1;
    if(enemyTimer % 100 == 0 && enemyList.size() < 10){
        ofPoint randPosition = getRandomEdgePoint();
        EnemyShip* tempEnemy = new EnemyShip(randPosition.x, randPosition.y, 2.5);
        enemyList.push_back(tempEnemy);
        enemyTimer = 0;
    }


//Movement logic for player 
    this->player->processPressedKeys();
    this->player->update();
    wrapCoords(this->player->pos);



//Movement and hit detection for enemies
    for(int i = 0; i < enemyList.size(); i++){
        EnemyShip* enemy = enemyList[i];
        enemy->update(this->player->pos);
        int index = i;
        for(Projectiles p : this->player->bullets){
            if(enemy->enemyHitBox.isHit(p)){
                if(player->health + 5 >= 100){
                    player->health = 100;    
                }
                else{
                    player->health = player->health + 5; 
                }
                enemyList.erase(enemyList.begin() + index);
                shipDestroyed.play();
            }
        }
    }

// Section for Updating bullets:
    //player projectiles
    if(this->player->bullets.size() > 0) {
        updateBullets();
    } 
    shotTimer(10);

    //enemy projectiles
    for(EnemyShip* enemy : enemyList){
        enemy->shotTimer++;
        updateEnemyBullets(enemy);
        for(Projectiles p : enemy->enemyBullets){
            if(player->hitBox.isHit(p)){
                if(player->health > 0){
                    if(player->health < 10){
                        player->health -= player->health;
                    }
                    else{
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
    player->draw();
    if(shot) draw_bullets();
    for(EnemyShip* e : enemyList){
        e->draw();
        if(e->enemyBullets.size() > 0){
            drawEnemyBullets(e);
        }
    }

    healthBar(player->health, 100);
}   

void ShipBattle::reset(){


}

void ShipBattle::keyPressed(int key){
        player->addPressedKey(key);
        // if(key == ' '){
        //     player->shoot();
        // }
}

void ShipBattle::keyReleased(int key){
       this->player->keyMap[key] = false;
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
    for(Projectiles p : enemy->enemyBullets){
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
    for (unsigned int i = 0; i < enemy->enemyBullets.size(); i++) {
       enemy->enemyBullets[i].update();

        if (bulletIsOutOfBounds(enemy->enemyBullets[i])) {
            enemy->enemyBullets.erase(enemy->enemyBullets.begin() + i);
        }
    }
}

bool ShipBattle::bulletIsOutOfBounds(Projectiles p){
    if (p.position.x < 0 || p.position.x > ofGetWidth() || p.position.y < 0 || p.position.y > ofGetHeight()) {
        return true; // Bullet is out of bounds
    }
    return false; // Bullet is within bounds

}

