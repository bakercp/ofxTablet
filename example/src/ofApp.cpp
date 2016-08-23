// =============================================================================
//
// Copyright (c) 2009-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


void ofApp::setup()
{
    ofx::RegisterPointerEvents(this);

    ofx::Tablet::setup();

}


void ofApp::update()
{
}


void ofApp::draw()
{
    ofBackground(0);

    ofSetColor(255);
    ofDrawBitmapString("#Points: " + ofToString(points.size()), ofVec2f(12, 12));

    // Simple
    ofFill();
    ofSetColor(255);

    ofMesh mesh;

    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);

    for (std::size_t i = 0; i < points.size(); ++i)
    {
        mesh.addVertex(points[i].point());

        ofDrawCircle(points[i].point().x, points[i].point().y, 20 * points[i].point().pressure());
    }

    mesh.draw();

}


void ofApp::onPointerDown(ofx::PointerEventArgs& evt)
{
    if (evt.deviceType() == ofx::PointerEventArgs::TYPE_PEN)
    {
        ofLogVerbose("ofApp::onPointerDown") << evt.toString();
        points.clear();
        points.push_back(evt);
    }
}


void ofApp::onPointerUp(ofx::PointerEventArgs& evt)
{
    if (evt.deviceType() == ofx::PointerEventArgs::TYPE_PEN)
    {
        ofLogVerbose("ofApp::onPointerUp") << evt.toString();
    }
}


void ofApp::onPointerMove(ofx::PointerEventArgs& evt)
{
    if (evt.deviceType() == ofx::PointerEventArgs::TYPE_PEN)
    {
        ofLogVerbose("ofApp::onPointerMove") << evt.toString();

        if (evt.buttons() > 0)
        {
            points.push_back(evt);
        }
    }
}


void ofApp::onPointerCancel(ofx::PointerEventArgs& evt)
{
    if (evt.deviceType() == ofx::PointerEventArgs::TYPE_PEN)
    {
        ofLogVerbose("ofApp::onPointerCancel") << evt.toString();
    }
}
