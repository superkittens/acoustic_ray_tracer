
#include "ofMain.h"

#ifndef _SOURCE_SINK_H
#define _SOURCE_SINK_H

typedef enum
{
    LEFT = 0,
    RIGHT
}Direction;


class Positioning
{
    protected:
    typedef enum
    {
        UNLOCKED = 0,
        LOCKED
    }PositioningState;

    PositioningState _currentState;
    ofVec2f _coordinates;
    bool    _isGrabbed = false;
    ofColor _color{255, 255, 255};

    static const float RADIUS;

    public:

    Positioning() : _currentState{UNLOCKED}, _coordinates{ofVec2f(0,0)} {}
    Positioning(ofVec2f coordinates) : _currentState{UNLOCKED}, _coordinates{coordinates} {}
    ~Positioning() = default;

    void grab(const ofVec2f& cursorPos);
    void release();
    void move(const ofVec2f& point);
    void setColor(const ofColor& color) {_color = color;}
    ofVec2f getCoordinates() const { return _coordinates; }
    virtual void draw() const;
};


class Listener : public Positioning
{
    public:

    Listener(ofVec2f coordinates) : Positioning{coordinates} {};
    ~Listener() = default;

    void draw() const override;
    std::pair<bool, Direction> checkRayCollision(const ofVec2f& ray) const;

    protected:
    static const float DETECT_RADIUS;
};


class Emitter : public Positioning
{
    private:

    public:

    Emitter(ofVec2f coordinates) : Positioning{coordinates}{};
    ~Emitter() = default;

    void draw() const override;
    ofVec2f getCoordinates() const { return _coordinates; }
};

#endif