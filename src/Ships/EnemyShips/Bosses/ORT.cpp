#include "ORT.h"

ORT::ORT(int xpos, int ypos, string name) : Boss(xpos, ypos,0.5, 500, name) {
    enemyShipSprite.load("bin\\data\\CompressedImages\\ORT_Xibalba-min.png");
    enemyHitBox = new HitBox(pos, enemyShipSprite.getWidth() * 0.05, enemyShipSprite.getHeight() * 0.03);

}
    
void ORT::update(const ofPoint& playerPos) {
    pos.x += speed;
    
    // Check if ORT is out of the screen, reset position if necessary
    if (pos.x > ofGetWidth()) {
        pos.x = 0;
    }

    // Shoot bullets in a semi-circular motion
    if (shotTimer % 60 == 0) { // Adjust the value for the frequency of shooting
        shoot();
    }

    if(enemyBullets.size() > 0) {
        // Update bullets
        for (Projectiles& bullet : enemyBullets) {
            bullet.update();
        }
    }

    // Increment shot timer
    shotTimer++;

}

void ORT::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    // ofRotateDeg(shipOrientation);
    enemyShipSprite.draw(-32, -32, 200, 200);
    ofPopMatrix();
    

    //Uncomment this if you want to see the hitbox for the enemy
        // enemyHitBox->draw();
    showBossHealth();

}


void ORT::shoot() {
    const int numBullets = 5;
    const float angleStep = 30.0; // Degrees between each bullet

    for (int i = 0; i < numBullets; ++i) {
        float angle = i * angleStep;
        Projectiles bullet(pos, angle);
        bullet.setColors(ofColor::red, ofColor::orange); // Set desired colors
        enemyBullets.push_back(bullet);
    }
    SoundManager::playSong("bulletSound", false);
}

