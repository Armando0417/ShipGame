#include "State.h"
#include "enemy.h"
#include "playerShip.h"


class ShipBattle : State{ 

    private:
        Player* player;
        vector<EnemyShip*> enemyList;

        bool canShoot;
        bool shot;
        int timer;
        int enemyTimer; //Timer for the enemy spawns
        
        ofSoundPlayer shipDestroyed;


    public:
        ShipBattle();
        void update();
        void draw();
        void reset();
        void keyPress(int key);

        //----- Utility Methods -------

        void wrapCoords(ofPoint &currentPos); //Method to always keep a ship inside the screen	
		
		void updateBullets();
		void draw_bullets();
		
		void drawEnemyBullets(EnemyShip* enemy);
		void updateEnemyBullets(EnemyShip* enemy);

		bool bulletIsOutOfBounds(Projectiles p); //Method to handle the many projectiles that will be shot

        ofVec2f getRandomEdgePoint();

        void shotTimer(int time);

        ~ShipBattle(){
            
        }
};


