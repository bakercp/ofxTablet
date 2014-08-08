// =============================================================================
//
// Copyright (c) 2014 Matt Ebb
// Copyright (c) 2014 Christopher Baker <http://christopherbaker.net>
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
#include "ofx/PointerEventArgs.h"
#include "ofx/PointerEvents.h"


#ifdef __APPLE__

#include "Tablet_Cocoa.h"

#else
    #error -- Currently this code only works with MAC OS X
#endif


namespace ofx {


// The default tablet is inited here.
Tablet& tablet = Tablet::getTabletRef();


Tablet::Tablet()
{
    connectImpl(-1);
}


Tablet::~Tablet()
{
}

void Tablet::callback(const TabletData& data)
{
    PointerEventArgs::EventType evtType = PointerEventArgs::MOVE;

    switch (data.eventType)
    {
        case TabletData::DOWN:
            evtType = PointerEventArgs::DOWN;
            break;
        case TabletData::UP:
            evtType = PointerEventArgs::UP;
            break;
        case TabletData::MOVE:
            evtType = PointerEventArgs::MOVE;
            break;
    };


    ofVec3f windowPosition(data.absX - ofGetWindowPositionX(),
                           (ofGetScreenHeight() - data.absY) - ofGetWindowPositionY(),
                           data.absZ);

    Point point(windowPosition,
                ofVec3f(data.absX, data.absY, data.absZ),
                PointShape(),
                data.pressure,
                data.tangentialPressure,
                data.rotation,
                data.tiltX,
                data.tiltY);


    unsigned long modifiers = 0;

    modifiers |= ofGetKeyPressed(OF_KEY_CONTROL) ? OF_KEY_CONTROL : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_ALT)     ? OF_KEY_ALT     : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SHIFT)   ? OF_KEY_SHIFT   : 0;
    modifiers |= ofGetKeyPressed(OF_KEY_SUPER)   ? OF_KEY_SUPER   : 0;

    unsigned long buttons = 0;

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
                         data.button,
                         buttons,
                         modifiers,
                         data.clickCount,
                         Poco::Timestamp());

    switch (evt.getEventType())
    {
        case PointerEventArgs::DOWN:
            ofNotifyEvent(PointerEvents().onPointerDown, evt);
            break;
        case PointerEventArgs::UP:
            ofNotifyEvent(PointerEvents().onPointerUp, evt);
            break;
        case PointerEventArgs::MOVE:
            ofNotifyEvent(PointerEvents().onPointerMove, evt);
            break;
        case PointerEventArgs::CANCEL:
            ofNotifyEvent(PointerEvents().onPointerCancel, evt);
            break;
    };
}


Tablet& Tablet::getTabletRef()
{
    // TODO: deviceId is currently ignored.
    static Poco::SingletonHolder<Tablet> sh;
    return *sh.get();
}


} // namespace ofx
