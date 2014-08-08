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


#pragma once

// for meanings of fields see here: http://www.wacomeng.com/mac/Developers%20Guide.htm

namespace ofx {


struct TabletData
{
public:
    enum PointerType
    {
        PTypeUnknown = 0,       // should never happen
        PTypePen,               // tip end of a stylus like device
        PTypeCursor,            // any puck like device
        PTypeEraser             // eraser end of a stylus like device
    };


    enum EventType
    {
        DOWN = 0,
        UP,
        MOVE
    };

    EventType eventType;

    int evt;

    // from driver
    float absX;
    float absY;
    float absZ;

    float tiltX; // 2d projection of normalized 3d vector on to ground plane, from driver
    float tiltY;

    float pressure;
    float rotation;
    float tangentialPressure;

    // from proximity events
    bool isProximityEvent;
    int button;
    int clickCount;
    int pointerID; // index of the device on this tablet
    int deviceID;  // used to match pointer events with proximity events

    int vendorID;

    unsigned int vendorPointerType;

};



}; // namespace ofx