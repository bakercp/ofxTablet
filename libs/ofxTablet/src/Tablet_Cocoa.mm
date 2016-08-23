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


#import <Cocoa/Cocoa.h>
#import "Tablet_Cocoa.h"
#import "ofx/TabletData.h"
#import "ofx/Tablet.h"
#import <iostream>


void handlePoint(NSEvent *event);
void handleProximity(NSEvent *event);


bool connectImpl(int deviceId)
{
    uint64_t tabletMask = 0;

    tabletMask |= NSLeftMouseDownMask;
    tabletMask |= NSLeftMouseUpMask;
    tabletMask |= NSRightMouseDownMask;
    tabletMask |= NSRightMouseUpMask;
    tabletMask |= NSMouseMovedMask;
    tabletMask |= NSLeftMouseDraggedMask;
    tabletMask |= NSRightMouseDraggedMask;

    id handler = [NSEvent addLocalMonitorForEventsMatchingMask: tabletMask
                                                       handler: ^(NSEvent *event)
                  {
                      switch ([event subtype])
                      {
                          case NX_SUBTYPE_TABLET_POINT:
                          case NX_SUBTYPE_TABLET_PROXIMITY:
                          {
                              ofx::TabletData data;

                              if ([event type] == NSLeftMouseDown || [event type] == NSRightMouseDown)
                              {
                                  data.eventType = ofx::TabletData::DOWN;
                              }
                              else if ([event type] == NSLeftMouseUp || [event type] == NSRightMouseUp)
                              {
                                  data.eventType = ofx::TabletData::UP;
                              }
                              else
                              {
                                  data.eventType = ofx::TabletData::MOVE;
                              }

                              data.evt = [event type];

                              data.absX = [NSEvent mouseLocation].x;
                              data.absY = [NSEvent mouseLocation].y;
                              data.absZ = 0;

                              data.x = [NSEvent mouseLocation].x;
                              data.y = [NSEvent mouseLocation].y;

                              data.tiltX = [event tilt].x;
                              data.tiltY = [event tilt].y;
                              data.pressure = [event pressure];
                              data.rotation = [event rotation];
                              data.tangentialPressure = [event tangentialPressure];

                              data.isProximityEvent = [event isEnteringProximity];

                              data.button = [event buttonNumber];
                              data.pointerID = [event pointingDeviceID];
                              data.deviceID = [event deviceID];

                              data.clickCount = [event clickCount];

                              data.vendorID = [event vendorID];

                              data.vendorPointerType = [event vendorPointingDeviceType];

                              ofx::Tablet::callback(data);
                          }
                              break;
                          case NX_SUBTYPE_DEFAULT:
                              // If the pen tablet sends events of this subtype,
                              // it probably means the driver is not installed
                              // and the OS is treating it as a mouse.
                              break;
                          default:
                              break;
                      }

                      return event;

                  }];

    return true;
}

bool disconnectImpl(int deviceId)
{
    return true;
}
