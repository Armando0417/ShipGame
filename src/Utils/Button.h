#pragma once
#include "ofMain.h"


class Button {
    private:
        int xPos;
        int yPos;
        int width;
        int height;
        string imagePath;
        string textToDisplay;
        ofTrueTypeFont font; 
        ofSoundPlayer music;
        bool pressed;


    public:
        Button(int xPos, int yPos, int width, int height, string imagePath, string text);
        ~Button();

        void update();
        void draw();

        void setPressed(int mouseX, int mouseY);
        bool wasPressed();

};

