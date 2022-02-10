#include "SourceSink.h"

const float Positioning::RADIUS = 15;
const float Listener::DETECT_RADIUS = 30;

void Positioning::grab(const ofVec2f& cursorPos)
{
    //  If the simulation is happening, then the listener should be in a locked state
    //  And this function will do nothing
    if (!_isGrabbed)
    {
        ofVec2f delta = cursorPos - _coordinates;
        if (delta.length() <= RADIUS)
            _isGrabbed = true;
    }
}

void Positioning::release()
{
    _isGrabbed = false;
}

void Positioning::move(const ofVec2f& point)
{
    if (_isGrabbed)
        _coordinates = point;
}


//  Check to see if a given ray reaches a listener
//  Returns std::pair
//  First entry tells us whether or not a collision is detected
//  Second entry tells us which direction
std::pair<bool, Direction> Listener::checkRayCollision(const ofVec2f& ray) const
{
    const ofVec2f delta = ray - _coordinates;

    //  If ray is within the listener's listening bounds
    if (delta.length() <= DETECT_RADIUS)
    {
        //  Get direction
        if (delta.x >= 0)
            return {true, RIGHT};
        else
            return {true, LEFT};
    }

    return {false, LEFT};
}
