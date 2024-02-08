#include "EnemyCruiser.h"

EnemyCruiser::EnemyCruiser(int xpos, int ypos) : EnemyShip(xpos, ypos, 1.0, 10) {
    enemyShipSprite.load("bin\\data\\CompressedImages\\EnemyCruiser-min.png");
    enemyHitBox = new HitBox(pos, enemyShipSprite.getWidth() * 0.05, enemyShipSprite.getHeight() * 0.03);
}


void EnemyCruiser::update(const ofPoint& playerPos) {
    // Calculate the angle to the player
        ofVec2f toPlayer = playerPos - pos;
        float angleToPlayer = ofRadToDeg(-atan2(toPlayer.x, toPlayer.y));

    // Update ship's orientation
        shipOrientation = angleToPlayer;

    // Move towards the player
        pos += toPlayer.getNormalized() * speed;
        enemyHitBox->box.setPosition(pos.x - 15, pos.y - 10);

    this->shotTimer++;
    // Check if the ship should shoot
        if (shotTimer % 200 == 0) {
            shoot();
            shotTimer = 0; //resets the timer
        }
}


void EnemyCruiser::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotateDeg(shipOrientation);
    enemyShipSprite.draw(-32, -32, 60, 60);
    ofPopMatrix();
    
    //Uncomment this if you want to see the hitbox for the enemy
        // enemyHitBox->draw();
}


void EnemyCruiser::shoot() {
    // Create a new projectile and add it to the list of bullets
        Projectiles p = Projectiles(pos, shipOrientation + 90);
        p.setColors(ofColor::red, ofColor::orange);
        enemyBullets.push_back(p);
        p.shotSound();
}