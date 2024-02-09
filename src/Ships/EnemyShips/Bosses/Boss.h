#pragma once 
#include "enemy.h"

class Boss : public EnemyShip {
    
    protected:
        int BossHealth;
        string bossName;
        bool moveLeft;
        bool moveRight;
    public:
        Boss(int xpos, int ypos, double speed, int health, string name) : EnemyShip(xpos, ypos, speed, health, 10000) {
            bossName = name;
            BossHealth = health;
            amIBoss = true;
        }


        virtual void update(const ofPoint& playerPos) = 0;
        virtual void draw() = 0;
        virtual void shoot() = 0;
 
        string getName() { return this->bossName; }

 
        void showBossHealth() {
            // Draw a red health bar at the top center of the screen
            ofNoFill();
            ofDrawRectangle(ofGetWidth() / 4, ofGetHeight() * 3/4, ofGetWidth() / 2, 20);   //Overlay
            ofFill();
            ofSetColor(ofColor::red);

    // Calculate the width of the red health bar based on the proportion of health remaining
            float healthPercentage = static_cast<float>(health) / static_cast<float>(ofGetWidth()/2);
            int redBarWidth = static_cast<int>(ofGetWidth() / 2 * healthPercentage);
            
            ofDrawRectangle(ofGetWidth() / 4, ofGetHeight() * 3/4, redBarWidth, 20);    //Red box
            ofSetColor(ofColor::white); // Reset color to white


        }


};