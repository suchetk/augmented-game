//
//  ImageUtilities.h
//  cam-ninja
//
//  Created by Suchet Kumar on 11/20/19.
//

#ifndef ImageUtilities_h
#define ImageUtilities_h

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

class ImageUtilities {
public:
    ofxCvColorImage rgb;                           //rgb object for storing color image data
    ofxCvGrayscaleImage filtered,red,green,blue;  //objects for storing grayscale image data

    ofxCvGrayscaleImage processImage(ofPixels img);
    
};

#endif /* ImageUtilities_h */
