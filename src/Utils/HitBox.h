#pragma once
#include "Projectile.h"

class HitBox{

    public:
        ofRectangle box; //will serve as the skeleton for the hitbox 

        HitBox(){} //Useless constructor, just use the other constructors
        
        HitBox(ofPoint pos, float width, float height){
            this->box = ofRectangle(pos, width, height);
        }

        HitBox (float px, float py, float width, float height){
            this->box = ofRectangle(px, py, width, height);
        }

    //Method to draw the hitboxes in case you may want to test with them
        void draw(){
            ofDrawRectangle(box);
        }

    /*
        Method to check if a collision occurs. It takes a projectile and 
     */ 
        bool isHit(Projectiles& bullet){
            return box.inside(bullet.position.x, bullet.position.y);          
        }


};