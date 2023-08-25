#include "ofMain.h"
#include "Projectile.h"
#include <vector>
#include "HitBox.h"

class EnemyShip {
private:
    vector<Projectiles> enemyBullets;
    ofImage enemyShipSprite;
    ofPoint pos;
    float speed;
    float shootingThreshold; // Angle threshold to start shooting
    float damping;

    ofVec2f movement;

    //Handle Rotation
    int shipOrientation;
    float rotationSpeed;

public:
    HitBox enemyHitBox;


    EnemyShip(int xpos, int ypos, float _speed) {
        pos.x = xpos;
        pos.y = ypos;
        speed = _speed;
        rotationSpeed = 1.0;
        shootingThreshold = 1.0;
        damping = 0.95;

        enemyShipSprite.load("bin\\data\\EnemyCruiser.png");
        shipOrientation = 0;

        this->enemyHitBox = HitBox(pos, enemyShipSprite.getWidth() * 0.05, enemyShipSprite.getHeight() * 0.03);
    
    }

    void draw() {
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofRotateDeg(shipOrientation);
        enemyShipSprite.draw(-32, -32, 64, 64);
        ofPopMatrix();
        
        // Draw the hitbox around the player ship
        enemyHitBox.draw();
    }

    void drawHitBox() {
    // Calculate hitbox dimensions
    // float hitboxWidth = enemyShipSprite.getWidth() * 0.05; 
    // float hitboxHeight = enemyShipSprite.getHeight() * 0.03; 
    // float hitboxX = pos.x - hitboxWidth / 2;
    // float hitboxY = pos.y - hitboxHeight / 2;

    // Set the color to red for the rectangle's outline
//     ofSetColor(ofColor::red);
//     // Draw a hollow rectangle around the hitbox
//     ofNoFill(); // Set to no fill to make it hollow
//     // ofDrawRectangle(hitboxX, hitboxY, hitboxWidth, hitboxHeight);
//     ofDrawRectangle(enemyHitBox.x);
//     ofFill(); // Reset fill mode
//     ofSetColor(ofColor::white); 
    }

    void update(const ofPoint& playerPos) {
        // Calculate the angle to the player
        ofVec2f toPlayer = playerPos - pos;
        float angleToPlayer = ofRadToDeg(-atan2(toPlayer.x, toPlayer.y));

        // Update ship's orientation
        shipOrientation = angleToPlayer;

        // Move towards the player
        pos += toPlayer.getNormalized() * speed;
        enemyHitBox.box.setPosition(pos.x - 10, pos.y - 10);

        // Check if the ship should shoot
        if (abs(shipOrientation) < shootingThreshold) {
            shoot();

        }
    }
    
    
    
    void shoot() {
        // Create a new projectile and add it to the list of bullets
        Projectiles p = Projectiles(pos, shipOrientation);
        enemyBullets.push_back(p);
    }

};


