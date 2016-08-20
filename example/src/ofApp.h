#pragma once

#include "ofMain.h"
#include "ofxWTBSPostGlitch.h"


#define NUM_POINTS 100


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ofApp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed( int key );
    void keyReleased( int key );
    void mouseMoved( int x, int y );
    void mouseDragged( int x, int y, int button );
    void mousePressed( int x, int y, int button );
    void mouseReleased( int x, int y, int button );
    void windowResized( int w, int h );
    
    
    ofEasyCam camera;
    ofMaterial material;
    ofLight    light;
    
    ofFbo     fbo;
    ofFbo     screenBuffer;
    bool      bLoadScreen;
    
    void resetFbo();
    
    vector< ofPoint > points;
    
    bool bRotate;
    
    void drawWorld();
    
    ofxWTBSPostGlitch glitch;
    
    float glitchSize;
    float mosaicSize;
    float split_vSize;
    float split_hSize;
    float noise_vSize;
    float noise_hSize;
    float rgbShiftSize;
};
