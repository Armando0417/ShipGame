#pragma once

#include "ofMain.h"
#include "Projectile.h"
#include <vector>
#include "HitBox.h"

class EnemyShip {
    protected:
        ofPoint pos;
        float speed;
        int health;
        float damping;
        ofVec2f movement;
        int shipOrientation;
        float rotationSpeed;
        int shotTimer;
        HitBox* enemyHitBox;
        vector<Projectiles> enemyBullets;
        ofImage enemyShipSprite;


        bool dead;

    public:
        //Main Constructor for the EnemyShip class.
        EnemyShip(int xpos, int ypos, float _speed, int health) {
            pos.x = xpos;
            pos.y = ypos;
            speed = _speed;
            this->health = health;
            damping = 0.95;
            shipOrientation = 0;
            rotationSpeed = 1.0;
            shotTimer = 1; //Starts at 1 instead of 0 to avoid the ship shooting as soon as the ship spawns
            this->dead = false;
            // this->enemyHitBox = new HitBox(pos, enemyShipSprite.getWidth() * 0.05, enemyShipSprite.getHeight() * 0.03);

        }

        // Pure virtual method to be implemented by the individual enemy classes
        virtual void update(const ofPoint& playerPos) = 0;
        virtual void draw() = 0;
        virtual void shoot() = 0;


        // Getters
        ofPoint& getPos() { return pos; }
        HitBox* getHitBox() { return enemyHitBox; }
        vector<Projectiles>& getBullets() { return enemyBullets; }

        //Other methods:
        virtual void takeDamage(int dmg) {
            if(health - dmg <= 0) {
                health = 0;
                dead = true;
                return;
            }
            health -= dmg;
        }
        bool isDead() { return dead; }

    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~EnemyShip() {}

};



