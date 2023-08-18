    #include "ofMain.h"
    #include "Projectile.h"
    #include <queue>
    #include <vector>

    using namespace std;

    class Player{
        
        private:
            int health = 100;
            float acceleration = 5;
            
            ofImage shipSprite;
            queue<char> pressedKeys;
            int shipOrientation;

            bool isMoving = false; // Flag to track if a movement key is being held
            float damping = 0.95; // Damping factor for slowing down

        public:
            ofPoint pos;
            float speed;
            ofVec2f velocity;

            vector<Projectiles> bullets;
            
            Player(int Xposition, int Yposition){
                pos.x = Xposition;
                pos.y = Yposition;

                velocity.set(0, 0);
                this->shipSprite.load("bin\\data\\ShipModel.png");
                this->shipOrientation = 0;
            }
        
            int getHealth() {return this->health;}
            void setHealth(int health){this->health = health;}
            
            
            void draw() {
            // Calculate the rotation angle based on the Orientation
                float rotationAngle = 0.0f;
                if (shipOrientation == 1) {
                    rotationAngle = 90.0f;
                } 
                else if (shipOrientation == 2) {
                    rotationAngle = 180.0f;
                } 
                else if (shipOrientation == 3) {
                    rotationAngle = 270.0f;
                }

            // Draw the ship sprite with the calculated rotation
                ofPushMatrix();
                ofTranslate(this->pos.x, this->pos.y);
                ofRotateDeg(rotationAngle);
                this->shipSprite.draw(-32, -32, 64, 64); // Center the sprite at the origin
                ofPopMatrix();
            };


            void update(){
                // Update velocity based on pressed keys and orientation
                if (!pressedKeys.empty()) {
                    char keyPressed = pressedKeys.front();
                    movement(keyPressed);
                    pressedKeys.pop();
                }

                // Update position based on velocity
                pos += velocity;

                // Add damping to slow down the ship
                velocity *= 0.95;

                // Draw the ship
                draw();
            }

    //Section for movement ------------------------------------------       
        
        // Function to add a pressed key to the queue
            void addPressedKey(char key) {
                pressedKeys.push(key);
                isMoving = true; // Set the movement flag
            }

        //Function to process the keys inside the queue
            void processPressedKeys() {
                while (!pressedKeys.empty()) {
                    char keyPressed = pressedKeys.front();
                    pressedKeys.pop();
                    movement(keyPressed);
                }

                if (!isMoving) {
                    // Apply damping to gradually slow down the ship when no keys are being pressed
                    velocity *= damping; 
                }
                isMoving = false; // Reset the movement flag
            }   



        //Function that will handle the movement for the ship
        void movement(char keyPressed) {
            // Calculate the force vector based on the pressed key and ship orientation
            ofVec2f force;
            if (keyPressed == 'w') {
                force.set(0, -acceleration);
                shipOrientation = 0; // Set orientation to up
            }
            if (keyPressed == 'a') {
                force.set(-acceleration, 0);
                shipOrientation = 3; // Set orientation to left
            }
            if (keyPressed == 's') {
                force.set(0, acceleration);
                shipOrientation = 2; // Set orientation to down
            }
            if (keyPressed == 'd') {
                force.set(acceleration, 0);
                shipOrientation = 1; // Set orientation to right
            }

            // Apply force to velocity
            velocity += force;
        }
        

    //Section for shooting ------------------------------------------
        
            void shoot(){ 
                Projectiles p  = Projectiles(ofPoint(this->pos.x, this->pos.y), this->shipOrientation);
                this->bullets.push_back(p);
            }
            
    };