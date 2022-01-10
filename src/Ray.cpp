#include "Ray.h"

const float Ray::MIN_THRESHOLD = 0.000001f;

void Ray::update()
{
    if (_active)
    {
        _s += _v;
        _iteration += 1;
        _distanceTravelled += _distanceTravelledPerIteration;
        _level = 1 / _distanceTravelled;

        if (_trajectoryChanged)
        {
            _path.push_back(_s);
            _trajectoryChanged = false;
        }

        //  If the signal level is below the threshold, inactivate the ray
        if (_level < MIN_THRESHOLD)
            _active = false;
    }
}

void Ray::draw() const
{
    if (true)
    {
        ofSetColor(255, 255, 255);
        ofSetLineWidth(2);
        ofVec2f prevPoint = _path[0];

        for (auto i = 1; i < _path.size(); ++i)
        {
            ofDrawLine(prevPoint, _path[i]);
            prevPoint = _path[i];
        }

        ofDrawLine(prevPoint, _s);
    }
}