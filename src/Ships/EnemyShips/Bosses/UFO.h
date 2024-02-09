#pragma once
#include "Boss.h"

class UFO : public Boss {
        private:
        double radius;
        public:
        UFO(int xpos, int ypos, string name);
        void update(const ofPoint& playerPos) override;
        void draw() override;
        void shoot() override;
};