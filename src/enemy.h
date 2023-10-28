#include "ofMain.h"
#include "Projectile.h"
#include <vector>
#include "HitBox.h"

class EnemyShip {
    private:
        ofImage enemyShipSprite;
        ofPoint pos;
        float speed;
        float damping; 

        ofVec2f movement;

        //Handle Rotation
        int shipOrientation;
        float rotationSpeed;


    public:
        int shotTimer; 
        HitBox enemyHitBox;
        vector<Projectiles> enemyBullets;

    //Main Constructor for the EnemyShip class.
        EnemyShip(int xpos, int ypos, float _speed) {
            pos.x = xpos;
            pos.y = ypos;
            speed = _speed;
            damping = 0.95;
            shipOrientation = 0;
            rotationSpeed = 1.0;
            shotTimer = 1; //Starts at 1 instead of 0 to avoid the ship shooting as soon as the ship spawns

            enemyShipSprite.load("bin\\data\\EnemyCruiser.png");
            this->enemyHitBox = HitBox(pos, enemyShipSprite.getWidth() * 0.05, enemyShipSprite.getHeight() * 0.03);
        }

    //Method to draw the enemyShip and orient it in the correct direction
        void draw() {
            ofPushMatrix();
            ofTranslate(pos.x, pos.y);
            ofRotateDeg(shipOrientation);
            enemyShipSprite.draw(-32, -32, 60, 60);
            ofPopMatrix();
            
            //Uncomment this if you want to see the hitbox for the enemies
                //enemyHitBox.draw();
        }


    /*
        Main method for the EnemyShip Logic and movement. It takes the position of the player and calculates a movement
        vector to follow the player ship anywhere on the screen.

        @param  ofPoint& playerPos  -> position of the player
 
    */
    void update(const ofPoint& playerPos) {
        // Calculate the angle to the player
            ofVec2f toPlayer = playerPos - pos;
            float angleToPlayer = ofRadToDeg(-atan2(toPlayer.x, toPlayer.y));

        // Update ship's orientation
            shipOrientation = angleToPlayer;

        // Move towards the player
            pos += toPlayer.getNormalized() * speed;
            enemyHitBox.box.setPosition(pos.x - 15, pos.y - 10);

        // Check if the ship should shoot
            if (shotTimer % 200 == 0) {
                shoot();
                shotTimer = 0; //resets the timer
            }
    }
    
    
    /*
        Method to generate the projectiles. It creates a projectile object 
        and places it into the enemyBullets vector.  
    */
    void shoot() {
        // Create a new projectile and add it to the list of bullets
            Projectiles p = Projectiles(pos, shipOrientation +90);
            p.setColors(ofColor::red, ofColor::orange);
            enemyBullets.push_back(p);
            p.shotSound();
    }

};


