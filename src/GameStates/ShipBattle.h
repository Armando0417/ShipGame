#include "State.h"
#include "enemy.h"
#include "playerShip.h"


class ShipBattle : public State { 

    private:
        vector<EnemyShip*> enemyList;

        bool canShoot;
        bool shot;
        int timer;
        int enemyTimer; // Timer for the enemy spawns

        int score;
        
        ofSoundPlayer shipDestroyed;
        string nextState;

    public:
        
        Player* player;

        ofTrueTypeFont font;
        


        ShipBattle();
        void update();
        void draw();
        void reset();
        void keyPressed(int key);
        void keyReleased(int key);

        //----- Utility Methods -------

        void setNextState(string nextState){ this->nextState = nextState; }

        string getNextState() { return this->nextState; }

        


        void wrapCoords(ofPoint &currentPos); // Method to always keep a ship inside the screen	
		
		void updateBullets();
		void draw_bullets();
		
		void updateEnemyBullets(EnemyShip* enemy);
		void drawEnemyBullets(EnemyShip* enemy);

		bool bulletIsOutOfBounds(Projectiles p); // Method to handle the many projectiles that will be shot

        ofVec2f getRandomEdgePoint();

        void shotTimer(int time);

        ~ShipBattle(){}

        void healthBar(int currHealth, int maxHealth){ 
            ofNoFill();
            ofDrawRectangle(10, 40, maxHealth *2, 20);
            ofFill();
            ofSetColor(ofColor::green);
            ofDrawRectangle(10, 40, currHealth *2, 20);
            ofSetColor(ofColor::white);
        }
};


