#include "ofApp.h"
#include "ofxTablet.h"


void ofApp::setup()
{
    ofx::RegisterPointerEvents(this);

    ofBackground(10,10,10);
    ofEnableDepthTest();
//    light.setPosition(100, -50, 100);

    cam.move(0,-600,200);
    cam.lookAt(ofVec3f(0,0,0));

    pressure = 0;
    tabmtx = ofMatrix4x4::newIdentityMatrix();
    gridsize = 500;
    
}


void ofApp::draw()
{
    float gridsize = 500;
    
    cam.begin();
    
    ofDrawGrid(gridsize/2.0, 8.0f, false, false, false, true);
    
    ofPushMatrix();
   
    ofMultMatrix(tabmtx);
    
    ofDrawAxis(30);
    
    //ofEnableLighting();
    //light.enable();
    
    ofPushMatrix();
    ofRotateX(90);
    ofDrawCylinder(0,52,0,3,100);
    ofPopMatrix();

    ofDrawArrow(ofVec3f(0,0,100), ofVec3f(0,0,0), (pressure < 0.1 ? 10 : pressure * 25));

    ofDisableLighting();

    ofPopMatrix();
    
    cam.end();
    
}


void ofApp::onPointerUp(ofx::PointerEventArgs& evt)
{
}


void ofApp::onPointerDown(ofx::PointerEventArgs& evt)
{
}


void ofApp::onPointerMove(ofx::PointerEventArgs& evt)
{
    if (evt.getDeviceType() == ofx::PointerEventArgs::TYPE_PEN)
    {
        pressure = evt.getPoint().getPressure();

        // set up coordinate frame based on tablet data
        float normalizedX = evt.getPoint().x / ofGetWidth() - 0.5;
        float normalizedY = evt.getPoint().y / ofGetHeight() - 0.5;

        ofVec3f translate(normalizedX * gridsize, - normalizedY * gridsize, 0);

        ofVec3f tilt(evt.getPoint().getTiltX(), evt.getPoint().getTiltY());

        ofQuaternion tiltquat;

        tiltquat.makeRotate(ofVec3f(0, 0, 1), tilt);

        tabmtx.setRotate(tiltquat);
        tabmtx.setTranslation(translate);
   }
}


void ofApp::onPointerCancel(ofx::PointerEventArgs& evt)
{
}
