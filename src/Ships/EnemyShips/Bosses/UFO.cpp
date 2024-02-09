#include "UFO.h"


UFO::UFO(int xpos, int ypos, string name) : Boss(xpos, ypos, 0.5, 500, name) {
    enemyShipSprite.load("bin\\data\\ShipModels\\ORT_UFO_BOSS.png");
    enemyHitBox = new HitBox(pos, enemyShipSprite.getWidth() * 0.60, enemyShipSprite.getHeight() * 0.5);
    radius = 50;
    moveRight = true;
    moveLeft = false;

}

void UFO::update(const ofPoint& playerPos) {
    // Move UFO
        if(moveRight) pos.x += 5 * speed;

        if(moveLeft) pos.x -= 5 * speed;

    // Check if UFO is at the left edge, change direction to move right
    if (pos.x <= 0) {
        // ofLogToConsole();
        // ofLogNotice("UFO") << "Changed Position due to " << pos.x << " - " << enemyShipSprite.getWidth() << " = " << pos.x - enemyShipSprite.getWidth() * 3/4;
        moveRight = true;
        moveLeft = false;
    }

    // Check if UFO is at the right edge, change direction to move left
    if (pos.x + enemyShipSprite.getWidth() / 2 >= ofGetWidth() && moveRight) {
        moveRight = false;
        moveLeft = true;
    }

    this->enemyHitBox->box.setPosition(pos.x - 15, pos.y - 15);

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




}



void UFO::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    // ofRotateDeg(shipOrientation);   
    enemyShipSprite.draw(-32, -32, 400, 150);
    ofPopMatrix();
    
    //Uncomment this if you want to see the hitbox for the enemy
        enemyHitBox->draw();
    
    showBossHealth(); 
}

void UFO::shoot() {
    const int numBullets = 5;
    const float angleStep = 30.0; // Degrees between each bullet

    for (int i = 0; i < numBullets; ++i) {
        float angle = angleStep + (i - numBullets / 2) * angleStep;
        // Bullet creation code remains the same
  
        // Calculate the position offset based on the angle (assuming circular pattern)
        float offsetX = radius * cos(ofDegToRad(angle));
        float offsetY = radius * sin(ofDegToRad(angle));

        // Create a projectile with the calculated position offset
        Projectiles bullet(ofPoint(pos.x + offsetX, pos.y + offsetY), angle);
        bullet.setColors(ofColor::red, ofColor::orange); // Set desired colors
        enemyBullets.push_back(bullet);
    }

}
