#pragma once

#include "ofMain.h"
#include "playerShip.h"
#include <string>

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
		bool bulletIsOutOfBounds(Projectiles p);
		bool shipIsOutOfBounds(Player ship);
		
		Player* playerP; //Player ship pointer
		bool shot; //Flag to know if player has shot (to draw bullets)
		
		bool canShoot; //Flag to allow the player ship to shoot again
		int timer; //Has to start when i click la tecla de space AND canShoot = true

};
