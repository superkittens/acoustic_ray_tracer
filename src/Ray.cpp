#include "Ray.h"

void Ray::update()
{
    _s += _v;
    _iteration += 1;
    _distanceTravelled += _distanceTravelledPerIteration;
    _level = 1 / _distanceTravelled;
}

void Ray::draw() const
{
    ofSetColor(255, 255, 255);
    ofDrawCircle(_s, 15); 
}