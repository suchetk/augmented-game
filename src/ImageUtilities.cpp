//
//  ImageUtilities.cpp
//  cam-ninja
//
//  Created by Suchet Kumar on 11/20/19.
//

#include <stdio.h>
#include "ImageUtilities.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

int w = 640;
int h = 480;

ofxCvGrayscaleImage ImageUtilities::processImage(ofPixels img) {
    // https://dirtydebiandevil.wordpress.com/2013/01/21/color-tracking-in-openframework/
    rgb.allocate(w, h);
    filtered.allocate(w, h);
    red.allocate(w, h);
    green.allocate(w, h);
    blue.allocate(w, h);
    
    rgb.setFromPixels(img);
    rgb.mirror(false, true);
    rgb.convertToGrayscalePlanarImages(red, green, blue);
    
    green += blue;
    red -= green;
    
    for (int i = 0; i < w*h; i++) {
        filtered.getPixels()[i] = ofInRange(red.getPixels()[i],0,40) ? 0 : 255;
    }
    
    return filtered;
}
    
