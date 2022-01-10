#include "SourceSink.h"

const float Positioning::RADIUS = 15;
const float Listener::DETECT_RADIUS = 30;

void Positioning::grab(const ofVec2f& cursorPos)
{
    //  If the simulation is happening, then the listener should be in a locked state
    //  And this function will do nothing
    if (_currentState == UNLOCKED && !_isGrabbed)
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
    if (_isGrabbed && _currentState == UNLOCKED)
        _coordinates = point;
}

void Positioning::draw() const
{
    ofSetColor(_color);
    ofDrawCircle(_coordinates, RADIUS);
}



void Listener::draw() const
{
    ofSetColor(72, 128, 184);
    ofDrawCircle(_coordinates, RADIUS);
}

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


void Emitter::draw() const
{
    ofSetColor(233, 115, 83);
    ofDrawCircle(_coordinates, RADIUS);
}