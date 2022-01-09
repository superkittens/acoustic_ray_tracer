#ifndef _RAY_H
#define _RAY_H

#include "ofMain.h"


class Ray
{
    private:
    ofVec2f _v;
    ofVec2f _s;
    ofPath  _path;

    float   _iteration = 0;
    float   _distanceTravelledPerIteration;
    float   _distanceTravelled = 1.f;
    float   _level = 1.f;

    public:
    Ray(const ofVec2f& v, const ofVec2f& s, const float& distanceTravelledPerIteration) : _v{v}, _s{s}, _distanceTravelledPerIteration{distanceTravelledPerIteration} {}

    void    update();
    void    draw() const;
    ofVec2f getVelocity() const { return _v; }
    void    setVelocity(const ofVec2f& v) { _v = v; }
    ofVec2f getPosition() const { return _s; }
    void    setPosition(const ofVec2f& s) { _s = s; }
};

#endif