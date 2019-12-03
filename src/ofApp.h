#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ImageUtilities.h"

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
		
    ofVideoGrabber camera;
    ofxCvGrayscaleImage processed;
    ofxCvContourFinder contours;
    ImageUtilities utils;
    ofImage bucket;
    
    enum mode {
        START_GAME,
        PLAY_GAME,
        GAME_ENDED,
        EXIT
    };
    
    mode gamemode;
    
    int w = 640;
    int h = 480;
};
