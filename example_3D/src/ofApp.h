#pragma once


#include "ofMain.h"
#include "ofxTablet.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void draw();

    // Pointer Events
    void onPointerUp(ofx::PointerEventArgs& evt);
    void onPointerDown(ofx::PointerEventArgs& evt);
    void onPointerMove(ofx::PointerEventArgs& evt);
    void onPointerCancel(ofx::PointerEventArgs& evt);

    //ofLight light; // creates a light and enables lighting
    ofCamera cam;

    float pressure;
    ofMatrix4x4 tabmtx;
    float gridsize;


};
