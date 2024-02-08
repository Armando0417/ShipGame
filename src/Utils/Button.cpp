#include "Button.h"

Button::Button(int xPos, int yPos, int width, int height, string imagePath, string text){
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    this->imagePath = imagePath;
    this->textToDisplay = text;
    this->pressed = false;

    font.load("bin\\data\\Fonts\\Orbitron.ttf", 20, true, true, false, 0.3, 0);
    music.load("bin\\data\\Sounds\\buttonInteract.mp3");
}

void Button::setPressed (int mouseX, int mouseY) {
    if (mouseX > xPos && mouseX < xPos + width && mouseY > yPos && mouseY < yPos + height) {
        music.play();
        pressed = true;
    }
    else {
        pressed = false;
    }
}

bool Button::wasPressed() {
    return this->pressed;
}

void Button::update() {
    this->pressed = false;
}


void Button::draw() {
    ofImage img;

    if(imagePath == "") {
        ofSetColor(50, 50, 170);
        ofDrawRectangle(xPos, yPos, width, height);
        ofSetColor(255);
        // Calculate the center position for the text
        float textX = xPos + (width - font.stringWidth(textToDisplay)) / 2;
        float textY = yPos + (height + font.stringHeight(textToDisplay)) / 2;

        font.drawString(textToDisplay, textX, textY);

        return;
    }
    
    img.load(imagePath);
    img.draw(xPos, yPos, width, height);
}


Button::~Button() {

}

