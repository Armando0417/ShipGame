#pragma once

#include "ofMain.h"
// #include "playerShip.h"
// #include "enemy.h"
#include "State.h"
#include "SoundManager.h"
#include "ShipBattle.h"
#include "introState.h"
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

//-----Section for added / utility methods and variables for overall game logic----------------	
	//States:
		State *currentState;
		IntroState *intro;
		ShipBattle *battle;


};
