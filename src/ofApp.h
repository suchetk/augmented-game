#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ImageUtilities.h"
#include "ofxBox2d.h"
#include <stdlib.h>

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
    
    void addCircle();
    bool shouldCatch(ofVec2f pos);
    bool isDropped(ofVec2f pos);
            
    ofVideoGrabber camera;
    ofxCvGrayscaleImage processed;
    ofxCvContourFinder contours;
    ImageUtilities utils;
    ofImage cup;
    ofImage about1;
    ofImage about2;
    
    ofTrueTypeFont myFont;
    ofTrueTypeFont title;
    ofTrueTypeFont stats;
    
    ofColor changingColor;
    
    enum mode {
        START_GAME,
        ABOUT,
        PLAY_GAME,
        GAME_ENDED,
        EXIT
    };
    
    mode gamemode;
    int selection[3];
    
    // timers for the about page
    unsigned long startTime, actualTime, lastBall, colorChange;
    int timeTillNextBall;

    int w = 640;
    int h = 480;
    
    // box2d objects
    ofxBox2d box2d;
    
    vector <shared_ptr<ofxBox2dCircle> > circles;
    
    int caught;
    int dropped;
    int score;
    
    ofSoundPlayer dropSound;

    ofSoundPlayer catchSound1;
    ofSoundPlayer catchSound2;
    ofSoundPlayer catchSound3;
    ofSoundPlayer catchSound4;
    ofSoundPlayer catchSound5;
    ofSoundPlayer catchSound6;
    ofSoundPlayer catchSound7;
    
    vector<ofSoundPlayer> catchSounds;
    ofSoundPlayer backMusic;
};
