#include "ofApp.h"


////////////////////////////////////////
// setup
////////////////////////////////////////
void ofApp::setup()
{
    // fbo
    resetFbo();
    
    // glitch
    glitchSize   = 60;
    mosaicSize   = 10;
    split_vSize  = 30;
    split_hSize  = 60;
    noise_vSize  = 20;
    noise_hSize  = 20;
    rgbShiftSize = 20;
    
    glitch.setup( &fbo );
    glitch.setGlitchSize( &glitchSize );
    glitch.setDelayScreen( &screenBuffer );
    glitch.setMosaicSize( &mosaicSize );
    glitch.setVerticalSplitSize( &split_vSize );
    glitch.setHorizontalSplitSize( &split_hSize );
    glitch.setVerticalNoiseSize( &noise_vSize );
    glitch.setHorizontalNoiseSize( &noise_hSize );
    glitch.setRGBShiftSize( &rgbShiftSize );
    
    bLoadScreen = false;
    
    // points
    for( int i = 0; i < NUM_POINTS; ++i )
    {
        ofPoint p;
        p.x = ofRandomf() * ofGetWidth();
        p.y = ofRandomf() * ofGetWidth();
        p.z = ofRandomf() * ofGetWidth();
        
        points.push_back( p );
    }
    
    bRotate = true;
    
    // camera
    camera.setPosition( 0, 0, 0 );
    camera.setTarget( ofVec3f( 0, 0, 0 ) );
    camera.setFov( 60 );
//    camera.setDistance( 500 );
    
    // material
    material.setAmbientColor( ofFloatColor( 0.0 ) );
    material.setDiffuseColor( ofFloatColor( 1.0 ) );
    material.setSpecularColor( ofFloatColor( 1.0 ) );
    material.setShininess( 64 );
    
    // light
    light.setAmbientColor( ofFloatColor( 0.0 ) );
    light.setDiffuseColor( ofFloatColor( 1.0 ) );
    light.setSpecularColor( ofFloatColor( 1.0 ) );
    light.setPointLight();
    light.setPosition( -ofGetWidth(), -ofGetWidth(), ofGetWidth() );
    
    ofBackground( 0 );
}


////////////////////////////////////////
// setup
////////////////////////////////////////
void ofApp::resetFbo()
{
    ofEnableArbTex();
    
    fbo.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA32F );
    screenBuffer.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA32F );
    
    fbo.begin();
    {
        ofClear( 0, 0, 0, 255 );
    }
    fbo.end();
    
    screenBuffer.begin();
    {
        ofClear( 0, 0, 0, 255 );
    }
    screenBuffer.end();
}


////////////////////////////////////////
// update
////////////////////////////////////////
void ofApp::update()
{
    ofSetWindowTitle( ofToString( ofGetFrameRate(), 2 ) );
    
    split_vSize = ofGetMouseY();
    split_hSize = ofGetMouseX();
    
    noise_hSize  = ofMap( ofGetMouseX(), 0, ofGetWidth(), 0, 40 );
    rgbShiftSize = ofMap( ofGetMouseX(), 0, ofGetWidth(), 0, 50 );
    
    // fbo
    fbo.begin();
    {
        ofBackground( 0 );
        
        camera.begin();
        {
            drawWorld();
        }
        camera.end();
        
        // load screen
        if( bLoadScreen )
        {
            screenBuffer.getTextureReference().loadScreenData( 0, 0, ofGetWidth(), ofGetHeight() );
            bLoadScreen = false;
        }
    }
    fbo.end();
    
    
    
    ofFill();
    // glitch
    glitch.generateFx();
}


////////////////////////////////////////
// draw
////////////////////////////////////////
void ofApp::drawWorld()
{
    ofPushMatrix();
    {
        if( bRotate )
        {
            ofRotateX( ofGetFrameNum()*2 );
            ofRotateY( ofGetFrameNum() );
        }
        
        ofSetColor( 255 );
        ofFill();
        
        ofEnableDepthTest();
        {
            ofEnableLighting();
            light.enable();
            {
                material.begin();
                {
                    for( int i = 0; i < points.size(); ++i )
                    {
                        ofDrawBox( points.at( i ), ofNoise( i * 0.4, ofGetElapsedTimef()*2 ) * 100 );
                    }
                }
                material.end();
            }
            light.disable();
            ofDisableLighting();
        }
        ofDisableDepthTest();
    }
    ofPopMatrix();
}


////////////////////////////////////////
// draw
////////////////////////////////////////
void ofApp::draw()
{
    ofSetColor( 255 );
    fbo.draw( 0, 0, ofGetWidth(), ofGetHeight() );
}


////////////////////////////////////////
// keyPressed
////////////////////////////////////////
void ofApp::keyPressed( int key )
{
    //---------------------------------------- glitch
    // delay
    if( key == 'd' )
    {
        bLoadScreen = true;
        glitch.setFx( OFXWTBSPOSTGLITCH_DELAY, true );
    }
    // glitch
    if( key == 'g' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_GLITCH, true );
    }
    // mosaic
    if( key == 'b' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_MOSAIC, true );
    }
    // split_v
    if( key == 'v' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_SPLIT_V, true );
    }
    // split_h
    if( key == 'h' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_SPLIT_H, true );
    }
    // noise_v
    if( key == 'm' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_NOISE_V, true );
    }
    // noise_h
    if( key == 'n' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_NOISE_H, true );
    }
    // rgbShift
    if( key == 's' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_RGB_SHIFT, true );
    }
    
    if( key == 'r' )
    {
        bRotate = !bRotate;
    }
    
    
    //---------------------------------------- fullscreen
    if( key == 'f' )
    {
        ofToggleFullscreen();
    }
}


////////////////////////////////////////
// keyReleased
////////////////////////////////////////
void ofApp::keyReleased( int key )
{
    //---------------------------------------- glitch
    // delay
    if( key == 'd' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_DELAY, false );
    }
    // glitch
    if( key == 'g' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_GLITCH, false );
    }
    // mosaic
    if( key == 'b' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_MOSAIC, false );
    }
    // split_v
    if( key == 'v' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_SPLIT_V, false );
    }
    // split_h
    if( key == 'h' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_SPLIT_H, false );
    }
    // noise_v
    if( key == 'm' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_NOISE_V, false );
    }
    // noise_h
    if( key == 'n' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_NOISE_H, false );
    }
    // rgbShift
    if( key == 's' )
    {
        glitch.setFx( OFXWTBSPOSTGLITCH_RGB_SHIFT, false );
    }
}


////////////////////////////////////////
// mouseMoved
////////////////////////////////////////
void ofApp::mouseMoved( int x, int y )
{
    
}


////////////////////////////////////////
// mouseDragged
////////////////////////////////////////
void ofApp::mouseDragged( int x, int y, int button )
{
    
}


////////////////////////////////////////
// mousePressed
////////////////////////////////////////
void ofApp::mousePressed( int x, int y, int button )
{
    
}


////////////////////////////////////////
// mouseReleased
////////////////////////////////////////
void ofApp::mouseReleased( int x, int y, int button )
{
    
}


////////////////////////////////////////
// windowResized
////////////////////////////////////////
void ofApp::windowResized( int _w, int _h )
{
    resetFbo();
    
    glitch.setup( &fbo, &screenBuffer );
}


////////////////////////////////////////
// exit
////////////////////////////////////////
void ofApp::exit()
{
    
}
