#include "SourceSink.h"

const float Positioning::RADIUS = 15;

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

bool Listener::checkRayCollision(const ofVec2f& ray)
{
    return true;
}


void Emitter::draw() const
{
    ofSetColor(233, 115, 83);
    ofDrawCircle(_coordinates, RADIUS);
}