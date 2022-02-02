
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

    ofVec2f _coordinates;
    bool    _isGrabbed = false;
    ofColor _color{255, 255, 255};

    static const float RADIUS;

    public:

    Positioning() : _coordinates{ofVec2f(0,0)} {}
    Positioning(ofVec2f coordinates) : _coordinates{coordinates} {}
    ~Positioning() = default;

    void            grab(const ofVec2f& cursorPos);
    void            release();
    void            move(const ofVec2f& point);
    void            setColor(const ofColor& color) {_color = color;}
    const ofColor   getColor() const { return _color; }
    ofVec2f         getCoordinates() const { return _coordinates; }
    const float     getRadius() const { return RADIUS; }
};


class Listener : public Positioning
{
    public:

    Listener(ofVec2f coordinates, size_t ident) : Positioning{coordinates}, _id{ident} { _color = ofColor(0, 127, 255); };
    ~Listener() = default;
    
    void            setId(const size_t ident) { _id = ident; }
    const size_t    getId() const { return _id; }

    std::pair<bool, Direction> checkRayCollision(const ofVec2f& ray) const;

    protected:
    static const float DETECT_RADIUS;
    size_t _id;
};


class Source : public Positioning
{
protected:
    size_t _id;

    public:

    Source(ofVec2f coordinates, size_t ident) : Positioning{coordinates}, _id{ident} { _color = ofColor(255, 127, 0); }
    ~Source() = default;

    ofVec2f getCoordinates() const { return _coordinates; }
    
    void            setId(const size_t ident) { _id = ident; }
    const size_t    getId() const { return _id; }
};

#endif
