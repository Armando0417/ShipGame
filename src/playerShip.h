#include <vector>
#include <unordered_map>
#include "ofMain.h"



#include "Projectile.h"
#include "HitBox.h"

using namespace std;

class Player{ 
    private:
    //Related to movement            
        float maxSpeed = 5;
        float speed;
        ofVec2f velocity;
        float accelerationAmount; 
        bool isMoving = false; // Flag to track if a movement key is being held
        float damping = 0.95; // Damping factor for slowing down

        float lastShotTime;
        float shotCooldown;

            
    //Related to Rotation 
        float rotationSpeed = 2.0; 
        ofImage shipSprite;
    
    public:
        int health = 100; //Needed in public for ease of use and direct access
        int shipOrientation; 
        unordered_map<int, bool> keyMap; //A Map is used to handle the keys pressed
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
            accelerationAmount = 5.0; // Adjust the value as needed

            hitBox =  HitBox(pos, shipSprite.getWidth() * 0.25, shipSprite.getHeight() * 0.15);
            
            lastShotTime = 0;
            shotCooldown = 0.25;  // Set the cooldown duration to 0.5 seconds (adjust as needed)

        }

        Player(){
            Player(ofGetWidth()/2, ofGetHeight()/2);
        }
  
    //Main method to draw the playerShip
        void draw() {
        // Draw the ship sprite with the calculated rotation
            ofPushMatrix();
            ofTranslate(this->pos.x, this->pos.y);
            ofRotateDeg(shipOrientation);
            this->shipSprite.draw(-20, -20, 45, 45);
            ofPopMatrix();
                
        // Draw the hitbox around the player ship. Uncomment this line for testing purposes
        // this->hitBox.draw();
        };

    /*
        Main method to update the playerShip. It handles the movement indirectly by calling processPressedKeys(), and updates the position.
        This is the brain of the class.
    */
        void update() {
            processPressedKeys();  // Process the pressed keys and calculate orientation change

            velocity.limit(maxSpeed); // Limit the velocity to the maximum speed
            
            pos += velocity; // Update position based on velocity
            this->hitBox.box.setPosition(pos.x - 15, pos.y - 15);
            
            velocity *= damping; // Apply damping to slow down the ship

            draw();  // Draw the ship

            if(health > 100) health = 100; //small check to mantain the player health capped at 100.
        }

    /*
        Method to generate the projectiles. It creates a projectile object 
        and places it into the bullets vector.  
    */
        void shoot(){ 
            // Projectiles p = Projectiles(ofPoint(this->pos.x, this->pos.y), this->shipOrientation);
            // p.setColors(ofColor::azure, ofColor::blueViolet);
            // this->bullets.push_back(p);
            // p.shotSound();

        // Calculate the current time
            float currentTime = ofGetElapsedTimef();

        // Check if enough time has passed since the last shot
            if (currentTime - lastShotTime >= shotCooldown) {
                Projectiles p = Projectiles(ofPoint(this->pos.x, this->pos.y), this->shipOrientation);
                p.setColors(ofColor::azure, ofColor::blueViolet);
                this->bullets.push_back(p);
                p.shotSound();

                // Update the last shot time to the current time
                lastShotTime = currentTime;
            }
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

            if(keyMap[' ']) {
                shoot();
                // keyMap[' '] = false;
            }
            
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
