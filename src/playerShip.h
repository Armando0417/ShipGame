#include <vector>
#include <unordered_map>
#include "ofMain.h"



#include "Projectile.h"
#include "HitBox.h"

using namespace std;

class Player{ 
    private:
        int health = 100;


    //Related to movement            
        float maxSpeed = 5;
        float speed;
        ofVec2f velocity;
        float accelerationAmount; 
        bool isMoving = false; // Flag to track if a movement key is being held
        float damping = 0.95; // Damping factor for slowing down
            

    //Related to Rotation 
        float rotationSpeed = 1.0; 
        ofImage shipSprite;
    
    public:
        int shipOrientation;
        unordered_map<int, bool> keyMap;
        vector<Projectiles> bullets;
        ofPoint pos;

        HitBox hitBox;
        
            
    //Parametrized Constructor for the playerShip
        Player(int Xposition, int Yposition){
            pos.x = Xposition;
            pos.y = Yposition;

            velocity.set(0, 0);
            this->shipSprite.load("bin\\data\\shipModel2.png");
            this->shipOrientation = 0;
            accelerationAmount = 3.0; // Adjust the value as needed
        }

    //Default Constructor
        //Player(){ Player(ofGetWidth()/2, ofGetHeight()/2); }

  
        void draw() {
        // Draw the ship sprite with the calculated rotation
            ofPushMatrix();
            ofTranslate(this->pos.x, this->pos.y);
            ofRotateDeg(shipOrientation);
            this->shipSprite.draw(-32, -32, 64, 64); // Center the sprite at the origin
            ofPopMatrix();
                
        // Draw the hitbox around the player ship
            drawHitBox();

        };


        
    void drawHitBox() {
    // Calculate hitbox dimensions
    float hitboxWidth = shipSprite.getWidth() * 0.5; // Make the hitbox 20% wider than the ship
    float hitboxHeight = shipSprite.getHeight() * 0.3; // Make the hitbox 20% taller than the ship
    float hitboxX = pos.x - hitboxWidth / 2;
    float hitboxY = pos.y - hitboxHeight / 2;

    // Set the color to red for the rectangle's outline
    ofSetColor(ofColor::red);
    // Draw a hollow rectangle around the hitbox
    ofNoFill(); // Set to no fill to make it hollow
    ofDrawRectangle(hitboxX, hitboxY, hitboxWidth, hitboxHeight);
    ofFill(); // Reset fill mode
    ofSetColor(ofColor::white); 
}




        void update() {
            // Process the pressed keys and calculate orientation change
            processPressedKeys();
            // Limit the velocity to the maximum speed
            velocity.limit(maxSpeed);
            // Update position based on velocity
            pos += velocity;
            // Apply damping to slow down the ship
            velocity *= damping;
            // Draw the ship
            draw();
        }

        
        void shoot(){ 
            Projectiles p = Projectiles(ofPoint(this->pos.x, this->pos.y), this->shipOrientation);
            this->bullets.push_back(p);
        }

    
    //Section for movement ------------------------------------------       
        
    // Function to add a pressed key to the queue
        void addPressedKey(int key) {
            keyMap[key] = true;
            isMoving = true; // Set the movement flag
        }

    //Function that will process if the value of the keys inside the Map are being pressed
        void processPressedKeys() {
            if(keyMap['w']) movement('w');
            if(keyMap['s']) movement('s');
            if(keyMap['d']) movement('d');
            if(keyMap['a']) movement('a');

            if (!isMoving) {
                // Apply damping to gradually slow down the ship when no keys are being pressed
                velocity *= damping; 
            }
        }   
        
    // Function that will handle the movement for the ship
        void movement(char keyPressed) {
            ofVec2f acceleration;

            if (keyPressed == 'w') {
                // Apply acceleration in the direction of the ship's orientation
                acceleration.set(cos(ofDegToRad(shipOrientation)) * accelerationAmount, sin(ofDegToRad(shipOrientation)) * accelerationAmount);
            }
            if (keyPressed == 's') {
                // Apply acceleration in the opposite direction of the ship's orientation
                acceleration.set(-cos(ofDegToRad(shipOrientation)) * accelerationAmount, -sin(ofDegToRad(shipOrientation)) * accelerationAmount);
            }

            // Apply force to velocity
            velocity += acceleration;
        
            if (keyPressed == 'a') {
                // Rotate the ship counterclockwise
                shipOrientation -= rotationSpeed;
            }
            if (keyPressed == 'd') {
                // Rotate the ship clockwise
                shipOrientation += rotationSpeed;
            }
        }

    
};
