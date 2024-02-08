#include "Boss.h"


class ORT : public Boss {

    public:
        ORT(int xpos, int ypos, string name);
        void update(const ofPoint& playerPos) override;
        void draw() override;
        void shoot() override;
        
};