#ifndef _RAY_H
#define _RAY_H

#include "ofMain.h"


class Ray
{
    private:
    static const float MIN_THRESHOLD;

    ofVec2f _v;
    ofVec2f _s;

    float   _iteration = 0;
    float   _distanceTravelledPerIteration;
    float   _distanceTravelled = 1.f;
    float   _level = 1.f;

    std::vector<ofVec2f> _path;

    bool    _trajectoryChanged = false;
    bool    _active = true;

    public:
    Ray(const ofVec2f& v, const ofVec2f& s, const float& distanceTravelledPerIteration) : _v{v}, _s{s}, _distanceTravelledPerIteration{distanceTravelledPerIteration} { _path.push_back(_s); }

    void    update();
    void    draw() const;
    ofVec2f getVelocity() const { return _v; }
    void    setVelocity(const ofVec2f& v) { _v = v; }
    ofVec2f getPosition() const { return _s; }
    void    setPosition(const ofVec2f& s) { _s = s; }
    void    signalTrajectoryChange() { _trajectoryChanged = true; }
    void    setInactive() { _active = false; }
    float   getLevel() const { return _level; }
    bool    getActiveStatus() const { return _active; }
};

#endif