/**
 * @file World.h
 * @author Allen Lee (alee@meoworkshop.org)
 * @brief 
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _WORLD_H
#define _WORLD_H

#include <vector>
#include <optional>
#include "ofMain.h"


class Wall
{
private:
    ofVec2f _start;
    ofVec2f _end;
    ofVec2f _vector;
    ofVec2f _normalVec;

    bool        _hasBoundingBox = false;
    ofRectangle _boundingBox;

    ofVec2f calculatePointNormal(const ofVec2f& point) const;

public:
    Wall(const ofVec2f& start, const ofVec2f& end);
    Wall(const Wall& arg);

    ofVec2f getStart() const { return _start; }
    ofVec2f getEnd() const { return _end; }
    
    float   getLength() const { return _vector.length(); }
    ofVec2f getUnitVector() const { return _vector.normalized(); }
    ofVec2f getVector() const { return _vector; }
    ofVec2f getNormalVector() const { return _normalVec; }

    void    draw() const;
    bool    isPointOutsideWall(const ofVec2f& point) const;
};



class World
{
    public:

    typedef enum
    {
        UNINITIALIZED = 0,
        BUILDING,
        BUILT
    }WorldState;

    static const float WORLD_SCALE;  //  pixels : 1 metre scale

    void draw() const;

    void startWorldBuilding();
    void setPoint();
    void setCursor(const ofVec2f& point);
    void setLineLock(bool lock) { _shiftKeyHeld = lock ? true : false; }

    ofVec2f getWorldOrigin() { return _worldOrigin; }
    float   getSpeedOfSound() const { return _speedOfSound; }
    void    setSpeedOfSound(const float& speedOfSound) { _speedOfSound = speedOfSound; }
    WorldState  getWorldBuildState() const { return _currentState; }

    const std::vector<Wall> getWalls() const { return _walls; }


    private:

    std::vector<ofVec2f>    _points;
    std::vector<Wall>       _walls;
    ofVec2f     _currentCursor;
    WorldState  _currentState = UNINITIALIZED;

    ofVec2f     _worldOrigin;

    bool        _shiftKeyHeld = false;

    float       _speedOfSound = 331.f;

    static const float SNAP_DELTA;

    void buildWalls();
};

#endif
