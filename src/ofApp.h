#pragma once

#include "ofMain.h"
#include "playerShip.h"
#include "enemy.h"
#include <string>
#include <cstdlib> 

using namespace std;

class ofApp : public ofBaseApp{
	public:
	//Main ofApp methods
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

//-----Section for utility methods and variables for overall game logic----------------	
 
		void wrapCoords(ofPoint &currentPos); //Method to always keep a ship inside the screen	
		
		void updateBullets();
		void draw_bullets();
		
		void drawEnemyBullets(EnemyShip* enemy);
		void updateEnemyBullets(EnemyShip* enemy);

		bool bulletIsOutOfBounds(Projectiles p); //Method to handle the many projectiles that will be shot
		
		Player* playerP; //Player ship pointer

		int enemyTimer; //Timer for the enemy spawns

		bool shot; //Flag to know if player has shot (to draw bullets)
		bool canShoot; //Flag to allow the player ship to shoot again
		int timer;
		void shotTimer(int time);

		vector<EnemyShip*> enemyList;

		ofSoundPlayer shipDestroyed;

	//Method to display HealthBars
		void healthBar(int currHealth, int maxHealth); 

};
