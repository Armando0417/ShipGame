#pragma once 

#include "ofMain.h"

class Projectiles{

    public:
        ofPoint position;
        ofColor color1, color2;
        float width;
        float height;
        int speed;
        int orientation;

        Projectiles(ofPoint p, int orientation) { //Constructor for projectiles 
            this->position = p;
            this->orientation = orientation;

            width = 10;
            height = 20;
            speed = 5;

            color1 = ofColor::red;
            color2 = ofColor::blue;
        }

        void update(){ //Method to update the projectile positions

            if (orientation == 0) {
                position.y -= speed;
            } 
    
            else if (orientation == 1) {
                position.x += speed;
            } 
    
            else if (orientation == 2) {
                position.y += speed;
            } 
            
            else if (orientation == 3) {
                position.x -= speed;
            }
        } 

        void draw(){ //Method to draw the projectiles
            ofPushMatrix();
            ofTranslate(position);
            ofRotateDeg(orientation * 90);

            // Draw the two ellipses with distinct colors
            ofSetColor(color1);
            ofDrawEllipse(0, 0, width, height);
            ofSetColor(color2);
            ofDrawEllipse(0, -height / 2, width, height);
            ofSetColor(ofColor::white);
            ofPopMatrix();
        }

}; 
