// =============================================================================
//
// Copyright (c) 2014 Matt Ebb
// Copyright (c) 2014-2016 Christopher Baker <http://christopherbaker.net>
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


#include "ofx/Tablet.h"
#include "ofAppRunner.h"
#include "ofx/PointerEvents.h"


#ifdef __APPLE__

#include "Tablet_Cocoa.h"

#else
    #error -- Currently this code only works with MAC OS X
#endif


namespace ofx {


Tablet::Tablet()
{
    connectImpl(-1);
}


Tablet::~Tablet()
{
    disconnectImpl(-1);
}


void Tablet::setup()
{
    Tablet::instance();
}


Tablet& Tablet::instance()
{
    // TODO: deviceId is currently ignored.
    static Tablet sh;
    return sh;
}



void Tablet::callback(const TabletData& data)
{
    std::string evtType = PointerEventArgs::POINTER_MOVE;

    switch (data.eventType)
    {
        case TabletData::DOWN:
            evtType = PointerEventArgs::POINTER_DOWN;
            break;
        case TabletData::UP:
            evtType = PointerEventArgs::POINTER_UP;
            break;
        case TabletData::MOVE:
            evtType = PointerEventArgs::POINTER_MOVE;
            break;
    };


    glm::vec3 windowPosition(data.absX - ofGetWindowPositionX(),
                             (ofGetScreenHeight() - data.absY) - ofGetWindowPositionY(),
                             data.absZ);

    Point point(windowPosition,
                glm::vec3(data.absX, data.absY, data.absZ),
                PointShape(),
                data.pressure,
                data.tangentialPressure,
                data.rotation,
                data.tiltX,
                data.tiltY);


    uint64_t modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;


    uint64_t buttons = 0;

    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_1) ? (1 << OF_MOUSE_BUTTON_1) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_2) ? (1 << OF_MOUSE_BUTTON_2) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_3) ? (1 << OF_MOUSE_BUTTON_3) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_4) ? (1 << OF_MOUSE_BUTTON_4) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_5) ? (1 << OF_MOUSE_BUTTON_5) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_6) ? (1 << OF_MOUSE_BUTTON_6) : 0;
    buttons |= ofGetMousePressed(OF_MOUSE_BUTTON_7) ? (1 << OF_MOUSE_BUTTON_7) : 0;

    PointerEventArgs evt(evtType,
                         point,
                         data.deviceID,
                         data.pointerID,
                         PointerEventArgs::TYPE_PEN,
                         false,
                         false,
                         data.button,
                         buttons,
                         modifiers,
                         data.clickCount,
                         ofGetElapsedTimeMillis());

    // Get the default instance.
    PointerEvents& pointerEvents = PointerEvents::instance();

    if (PointerEventArgs::POINTER_DOWN == evt.eventType())
    {
        ofNotifyEvent(pointerEvents.onPointerDown, evt);
    }
    else if(PointerEventArgs::POINTER_UP == evt.eventType())
    {
        ofNotifyEvent(pointerEvents.onPointerUp, evt);
    }
    else if(PointerEventArgs::POINTER_MOVE == evt.eventType())
    {
        ofNotifyEvent(pointerEvents.onPointerMove, evt);
    }
    else if(PointerEventArgs::POINTER_CANCEL == evt.eventType())
    {
        ofNotifyEvent(pointerEvents.onPointerCancel, evt);
    }
}


} // namespace ofx
