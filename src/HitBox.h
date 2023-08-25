#pragma once
#include "Projectile.h"

class HitBox{

    public:
        ofRectangle box;
        HitBox(ofPoint p1, ofPoint p2){
            this->box.set (p1, p2);
        }
        HitBox(ofPoint pos, float width, float height){
            this->box = ofRectangle(pos, width, height);
        }

        HitBox(){

        }

        void draw(){
            ofDrawRectangle(box);
        }

        bool isHit(Projectiles& bullet){
            return box.inside(bullet.position.x, bullet.position.y);          
        }


};