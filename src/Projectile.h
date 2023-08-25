#pragma once 

#include "ofMain.h"

class Projectiles{

    public:
        ofPoint position;
        ofColor color1, color2;
        float width;
        float height;
        int speed;
        float angle;

        Projectiles(ofPoint p, float angle) { //Constructor for projectiles 
            this->position = p;
            this->angle = angle ;

            width = 10;
            height = 20;
            speed = 15;

            color1 = ofColor::orange;
            color2 = ofColor::red;
        }

        void update() { // Method to update the projectile positions
            // Calculate the new position based on angle and speed
            float vx = cos(ofDegToRad(angle)) * speed;
            float vy = sin(ofDegToRad(angle)) * speed;
            position.x += vx;
            position.y += vy;
        }

        void draw(){ //Method to draw the projectiles
            ofPushMatrix();
            ofTranslate(position);
            ofRotateDeg(angle + 90); // Rotate the projectile based on its angle
            // Draw the two ellipses with distinct colors
            ofSetColor(color1);
            ofDrawEllipse(0, 0, width, height);
            ofSetColor(color2);
            ofDrawEllipse(0, -height / 2, width, height);
            ofSetColor(ofColor::white);
            ofPopMatrix();
        }



}; 
