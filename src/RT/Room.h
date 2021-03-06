
#ifndef ROOM_H_
#define ROOM_H_

//  TODO:  Eventually remove ofMain dependence
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


public:
    Wall(const ofVec2f& start, const ofVec2f& end);
    Wall(const Wall& arg);

    ofVec2f getStart() const { return _start; }
    ofVec2f getEnd() const { return _end; }
    
    float   getLength() const { return _vector.length(); }      //  getLength() will return the length in pixel space!
    ofVec2f getUnitVector() const { return _vector.getNormalized(); }
    ofVec2f getVector() const { return _vector; }
    ofVec2f getNormalUnitVector() const { return _normalVec; }

    bool    isPointOutsideWall(const ofVec2f& point) const;
    ofVec2f calculatePointNormal(const ofVec2f& point) const;
};


class Room
{
    public:
    
    const std::vector<Wall>&    getWalls() const { return _walls; }
    void                        buildRoom(const std::vector<ofVec2f>& points);
    bool                        isBuilt() const { return _roomBuilt; }
    void                        reset();

    private:
    std::vector<Wall>   _walls;
    bool                _roomBuilt = false;
};

#endif
