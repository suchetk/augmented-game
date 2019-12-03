#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camera.setup(w, h);
    bucket.load(
    "/Users/suchetkumar/Documents/cam-ninja/resources/Plastic-Bucket-Transparent-Images.png");
    
    gamemode = START_GAME;
}

//--------------------------------------------------------------
void ofApp::update(){
    // process image and find contours
    camera.update();
    processed = utils.findObjects(camera.getPixels());
    processed.flagImageChanged();
    contours.findContours(processed, 100, w*h/2, 1, false);

}

//--------------------------------------------------------------
void ofApp::draw(){
    switch (gamemode) {
        case START_GAME:
        {
            // flip and display the webcam image
            camera.draw(camera.getWidth(),0,-camera.getWidth(),camera.getHeight());
            
            // draw a circle at the centroid (object used as a cursor)
            ofSetColor(255, 255, 0);
            ofFill();
            ofDrawCircle(contours.blobs[0].centroid.x, contours.blobs[0].centroid.y, 5);
            
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
