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
#include "ImageUtilities.h"

class ImageUtilities {
public:
    ofxCvColorImage rgb;                           //rgb object for storing color image data
    ofxCvGrayscaleImage filtered,red,green,blue;  //objects for storing grayscale image data
    ofxCvContourFinder contours;                         //object to store contours of the filtered image

    ofxCvGrayscaleImage findObjects(ofPixels img);
    
};

#endif /* ImageUtilities_h */
