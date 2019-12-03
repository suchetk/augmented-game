#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camera.setup(w, h);
    bucket.load(
    "/Users/suchetkumar/Documents/cam-ninja/resources/Plastic-Bucket-Transparent-Images.png");
    
    gamemode = START_GAME;
    myFont.load("/Users/suchetkumar/Documents/cam-ninja/resources/Iron.ttf", 50);
}

//--------------------------------------------------------------
void ofApp::update(){
    // process image and find contours
    camera.update();
    processed = utils.processImage(camera.getPixels());
    processed.flagImageChanged();
    contours.findContours(processed, 100, w*h/2, 1, false);
    
    switch (gamemode) {
        case START_GAME:
        {
            // keep track of the cursor on each option
            if (contours.blobs.size() == 1) {
                if (contours.blobs[0].centroid.x > 55 &&
                    contours.blobs[0].centroid.x < 255 &&
                    contours.blobs[0].centroid.y > 150 &&
                    contours.blobs[0].centroid.y < 250) {
                    selection[0] += 1;
                 } else if (contours.blobs[0].centroid.x > 370 &&
                            contours.blobs[0].centroid.x < 570 &&
                            contours.blobs[0].centroid.y > 150 &&
                            contours.blobs[0].centroid.y < 250) {
                     selection[1] += 1;
                     
                 } else if (contours.blobs[0].centroid.x > 220 &&
                            contours.blobs[0].centroid.x < 420 &&
                            contours.blobs[0].centroid.y > 322 &&
                            contours.blobs[0].centroid.y < 422) {
                     selection[2] += 1;
                 } else {
                     selection[0] = 0;
                     selection[1] = 0;
                     selection[2] = 0;
                 }
            }
            break;
        }
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    switch (gamemode) {
        case START_GAME:
        {
            // flip and display the webcam image
            camera.draw(camera.getWidth(),0,-camera.getWidth(),camera.getHeight());
            
            // draw the boxes for options
            ofSetColor(255, 102, 102);
            ofDrawRectangle(55, 150, 200, 100);
            ofDrawRectangle(370, 150, 200, 100);
            ofDrawRectangle(220, 322, 200, 100);
            
            // draw boxes for selection
            ofSetColor(255, 51, 0);
            ofDrawRectangle(55, 250, 200, -selection[0]);
            ofDrawRectangle(370, 250, 200, -selection[1]);
            ofDrawRectangle(220, 422, 200, -selection[2]);
            
            // draw the text for the options
            ofSetColor(255);
            myFont.drawString("Play", 20+55, 20+200);
            myFont.drawString("About", 20+370, 20+200);
            myFont.drawString("Exit", 40+220, 20+372);
            
            ofSetColor(255, 255, 0);
            // draw a circle at the centroid (object used as a cursor)
            if (contours.blobs.size() == 1) {
                ofDrawCircle(contours.blobs[0].centroid.x, contours.blobs[0].centroid.y, 10);
            }
            
            
            break;
        }
            
        case PLAY_GAME:
        {
            // flip and display the webcam image
            camera.draw(camera.getWidth(),0,-camera.getWidth(),camera.getHeight());
            
            // overlaying the bucket onto the image
            bucket.draw(contours.blobs[0].centroid.x - contours.blobs[0].boundingRect.width/2 - 25,
                        contours.blobs[0].centroid.y - contours.blobs[0].boundingRect.height/2 - 25,
                        contours.blobs[0].boundingRect.width+50,
                        contours.blobs[0].boundingRect.height+50);
            break;
        }
            
        case GAME_ENDED:
        {
            
        }
        default:
            break;
    }

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
