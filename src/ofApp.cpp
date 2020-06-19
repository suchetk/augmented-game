#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camera.setup(w, h);
    cup.load("/Users/suchetkumar/Documents/cam-ninja/resources/Plastic-Bucket-Transparent-Images.png");
    about1.load("/Users/suchetkumar/Documents/cam-ninja/resources/about1.png");
    about2.load("/Users/suchetkumar/Documents/cam-ninja/resources/about2.png");
    
    myFont.load("/Users/suchetkumar/Documents/cam-ninja/resources/Iron.ttf", 50);
    title.load("/Users/suchetkumar/Documents/cam-ninja/resources/Iron.ttf", 70);
    stats.load("/Users/suchetkumar/Documents/cam-ninja/resources/Gameplay.ttf", 20);
    
    dropSound.load("/Users/suchetkumar/Documents/cam-ninja/resources/bonk.wav");
    
    catchSound1.load("/Users/suchetkumar/Documents/cam-ninja/resources/okay.wav");
    catchSound2.load("/Users/suchetkumar/Documents/cam-ninja/resources/swag.wav");
    catchSound3.load("/Users/suchetkumar/Documents/cam-ninja/resources/Khaled1.wav");
    catchSound3.setVolume(0.7);
    catchSound4.load("/Users/suchetkumar/Documents/cam-ninja/resources/Khaled2.wav");
    catchSound4.setVolume(0.7);
    catchSound5.load("/Users/suchetkumar/Documents/cam-ninja/resources/Rrrrat.wav");
    catchSound6.load("/Users/suchetkumar/Documents/cam-ninja/resources/wow.wav");
    catchSound6.setVolume(0.5);
    catchSound7.load("/Users/suchetkumar/Documents/cam-ninja/resources/yeah.wav");
    catchSound7.setVolume(0.5);
    
    catchSounds.push_back(catchSound1);
    catchSounds.push_back(catchSound2);
    catchSounds.push_back(catchSound3);
    catchSounds.push_back(catchSound4);
    catchSounds.push_back(catchSound5);
    catchSounds.push_back(catchSound6);
    catchSounds.push_back(catchSound7);
    
    
    backMusic.load("/Users/suchetkumar/Documents/cam-ninja/resources/backmusic.mp3");
    backMusic.setLoop(true);
    backMusic.setVolume(0.5);
    backMusic.play();
    
    gamemode = START_GAME;
    
    box2d.init();
    box2d.setGravity(0,30);
    
    startTime = ofGetElapsedTimeMillis();
    lastBall = ofGetElapsedTimeMillis();
    timeTillNextBall = 1000;
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
            actualTime = ofGetElapsedTimeMillis();
            // set the title color change
            if (actualTime - startTime > 681){
                startTime = ofGetElapsedTimeMillis();
                changingColor = ofColor(150+rand()%100, 150+rand()%100, 150+rand()%100);
            }
            
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
            if (selection[0] > 99) {
                gamemode = PLAY_GAME;
                selection[0] = 0;
                startTime = ofGetElapsedTimeMillis();
                timeTillNextBall = 1000;

            } else if (selection[1] > 99) {
                gamemode = ABOUT;
                selection[1] = 0;
                startTime = ofGetElapsedTimeMillis();
            } else if (selection[2] > 99) {
                ofExit();
            }
            break;
        }
        case ABOUT:
        {
            actualTime = ofGetElapsedTimeMillis();
            if (actualTime - startTime > 7000) {
                gamemode = START_GAME;
            }
            break;
        }
        case PLAY_GAME:
        {
            actualTime = ofGetElapsedTimeMillis();
            
            // check if the game ended
            if (dropped > 9) {
                gamemode = GAME_ENDED;
                score = actualTime - startTime;
                startTime = ofGetElapsedTimeMillis();
                colorChange = ofGetElapsedTimeMillis();
            };
            
            // create a new ball
            if (actualTime - lastBall > timeTillNextBall){
                addCircle();
                lastBall = ofGetElapsedTimeMillis();
            }
            
            // check if a circle has reached the bottom
            // check if a circle needs to be caught by the bucket
            for (auto circle : circles){
                if (shouldCatch(circle->getPosition())){
                    catchSounds[rand()%7].play();
                    circle->destroy();
                    caught += 1;
                    // make the balls drop faster with every catch
                    if (timeTillNextBall > 700){
                        timeTillNextBall -= 20;
                    } else if (timeTillNextBall > 500) {
                        timeTillNextBall -= 15;
                    } else if (timeTillNextBall > 300) {
                        timeTillNextBall -= 5;
                    } else {
                        timeTillNextBall = 300;
                    }
                };
                if (isDropped(circle->getPosition())){
                    dropSound.play();
                    circle->destroy();
                    dropped += 1;
                }
            }
            box2d.update();
            break;
        }
        case GAME_ENDED:
        {
            actualTime = ofGetElapsedTimeMillis();
            if (actualTime - startTime > 7000) {
                // reset the game
                startTime = ofGetElapsedTimeMillis();
                caught = 0;
                dropped = 0;
                gamemode = START_GAME;
            }
            if ((actualTime - colorChange)>681){
                changingColor = ofColor(150+rand()%100, 150+rand()%100, 150+rand()%100);
                colorChange = ofGetElapsedTimeMillis();
            }
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
            
            ofSetColor(60,60,60);
            // draw rectangle for the title
            ofDrawRectangle(159, 27, 325, 73);
            ofSetColor(changingColor);
            title.drawString("Catch2 .h", 154, 95);
            
            ofSetColor(255, 255, 0);
            // draw a circle at the centroid (object used as a cursor)
            if (contours.blobs.size() == 1) {
                ofDrawCircle(contours.blobs[0].centroid.x, contours.blobs[0].centroid.y, 10);
            }
            ofSetColor(225);
            break;
        }
        case ABOUT:
        {
            if (actualTime - startTime < 3500) {
                about1.draw(0, 0, 640, 480);
            }
            else {
                about2.draw(0, 0, 640, 480);
            }
            ofSetColor(0, 204, 0);
            ofDrawRectangle(0, 0, 640*(actualTime-startTime)/7000, 10);
            ofSetColor(255);
            break;
        }
        case PLAY_GAME:
        {
            // flip and display the webcam image
            camera.draw(camera.getWidth(),0,-camera.getWidth(),camera.getHeight());
            
            // draw circles
            for (auto circle : circles){
                circle->draw();
            }
            
            // overlaying the bucket onto the image
            cup.draw(contours.blobs[0].centroid.x - contours.blobs[0].boundingRect.width/2 - 25,
                        contours.blobs[0].centroid.y - contours.blobs[0].boundingRect.height/2 - 25,
                        contours.blobs[0].boundingRect.width+50,
                        contours.blobs[0].boundingRect.height+50);
            
            // draw time and stats
            ofSetColor(0);
            stats.drawString("Score: "+ to_string(caught), 20, 50);
            stats.drawString("Missed: " + to_string(dropped) + " /10", 400, 50);
            ofSetColor(255);
            break;
        }
            
        case GAME_ENDED:
        {
            ofSetColor(255, 153, 0);
            stats.drawString("Nice Try...", 230, 100);
            
            ofSetColor(changingColor);
            myFont.drawString("Score: " + to_string(score), 150, 200);
            myFont.drawString("Caught balls: " + to_string(caught), 100, 400);
            
            ofSetColor(0, 204, 0);
            ofDrawRectangle(0, 0, 640*(actualTime-startTime)/7000, 10);
            ofSetColor(255);
            break;
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

//--------------------------------------------------------------
void ofApp::addCircle(){
    auto circle = make_shared<ofxBox2dCircle>();
    circle->setPhysics(3.0, 0.5, 1.0);
    circle->setVelocity(rand()%8-4, -5);
    circle->setup(box2d.getWorld(), 100+rand()%440, 20, 25);
    circles.push_back(circle);
}

//--------------------------------------------------------------
bool ofApp::shouldCatch(ofVec2f pos){
    if (contours.blobs.size() == 1){
        if (pos.x > contours.blobs[0].centroid.x - contours.blobs[0].boundingRect.width/2 &&
            pos.x < contours.blobs[0].centroid.x + contours.blobs[0].boundingRect.width/2 &&
            pos.y > contours.blobs[0].centroid.y - contours.blobs[0].boundingRect.height/2 &&
            pos.y < contours.blobs[0].centroid.y - contours.blobs[0].boundingRect.height/2 + 25){
            return true;
        }
    }
    return false;
}

//--------------------------------------------------------------
bool ofApp::isDropped(ofVec2f pos){
    if (pos.y > 480) {
        return true;
    }
    return false;
}


