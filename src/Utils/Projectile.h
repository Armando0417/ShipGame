#pragma once 

#include "ofMain.h"

class Projectiles{

    public:
        ofPoint position;
        ofSoundPlayer shootingSound;
        ofColor color1, color2;
        float width;
        float height;
        int speed;
        float angle;
        int damage;

    //Constructor for projectiles 
        Projectiles(ofPoint p, float angle) { 
            this->position = p;
            this->angle = angle ;
            width = 7;
            height = 12;
            speed = 10; //Modify this to change all projectile speeds
            damage = 10;

            shootingSound.load("bin\\data\\Sounds\\shootingSound.MP3");
            shootingSound.setVolume(0.1);
        }

        Projectiles(ofPoint p, float angle, int dmg){
            this->position = p;
            this->angle = angle;
            width = 7;
            height = 12;
            speed = 10;
            damage = dmg;
            shootingSound.load("bin\\data\\Sounds\\shootingSound.MP3");
            shootingSound.setVolume(0.5);
        }


        void shotSound(){
            shootingSound.play();
        }

        void setColors(ofColor c1, ofColor c2){
            this->color1 = c1;
            this->color2 = c2;
        }

    // Method to update the projectile positions
        void update() { 
            // Calculate the new position based on angle and speed
            float vx = cos(ofDegToRad(angle)) * speed;
            float vy = sin(ofDegToRad(angle)) * speed;
            position.x += vx;
            position.y += vy;
        }

     //Method to draw the projectiles
        void draw(){
            ofPushMatrix();
            ofTranslate(position);
            ofRotateDeg(angle + 90); // Rotate the projectile based on its angle + 90 degrees to rotate in the appropriate orientation
            
            // Draw the two ellipses with distinct colors
            ofSetColor(color1); //This color is for the tail of the projectile
            ofDrawEllipse(0, 0, width, height);
            ofSetColor(color2); //This color is the main color of the projectile
            ofDrawEllipse(0, -height / 2, width, height);
            ofSetColor(ofColor::white);
            ofPopMatrix();
        }

        int getDamage(){ return damage; }

}; 
