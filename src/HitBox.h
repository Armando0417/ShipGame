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
        Method to check if a collision occurs.
        @param Projectiles& bullets   -> passes a projectile to verify if it intersects the hitbox
        @return bool                  -> true if collosion occurred
     */ 
        bool isHit(Projectiles& bullet){
            return box.inside(bullet.position.x, bullet.position.y);          
        }


};