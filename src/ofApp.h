#pragma once

#include "ofMain.h"
#include "playerShip.h"
#include "enemy.h"
#include <string>
#include <cstdlib> 

using namespace std;

class ofApp : public ofBaseApp{
	public:











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
		
		void wrapCoordinates(float ix, float iy, float &ox, float &oy);
		
		void wrapCoords(ofPoint &currentPos);
		
		
		
		void updateBullets();
		void draw_bullets();

		void updateBullets(Player &ship);
		void draw_bullets(Player &ship);

		bool bulletIsOutOfBounds(Projectiles p);
		bool shipIsOutOfBounds(Player ship);
		
		Player* playerP; //Player ship pointer
		EnemyShip* enemyP; //Pointer towards the enemy ships

		void spawnEnemies();

		double speedPicker();


		bool shot; //Flag to know if player has shot (to draw bullets)
		
		bool canShoot; //Flag to allow the player ship to shoot again
		int timer; //Has to start when i click la tecla de space AND canShoot = true
		int enemyTimer; //Timer for the enemy spawns
		void shotTimer(int time);
		bool spawnTimer(int time);

		bool useFirstShip;
		bool useSecondShip;


		vector<EnemyShip*> enemyList;
		vector<double> difSpeeds;


		bool playerAlive;









};
