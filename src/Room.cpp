

#include "Room.h"

Wall::Wall(const ofVec2f& start, const ofVec2f& end, const float& scale) : _scale{scale}, _start{start}, _end{end}
{
    //  Calculate unit and normal vectors
    _vector = end - start;
    ofVec2f vectorCopy = _vector;
    _normalVec = vectorCopy.perpendicular();

    //  If the wall is a horizontal/vertical line, add a bounding box
   if (start.x != end.x && start.y != end.y)
   {
       _hasBoundingBox = true;
       _boundingBox = ofRectangle(_start, end.x - start.x, end.y - start.y);
   }
}

Wall::Wall(const Wall& arg) : _scale{arg._scale}, _start{arg._start}, _end{arg._end}, _vector{arg._vector}, _normalVec{arg._normalVec}, _hasBoundingBox{arg._hasBoundingBox}, _boundingBox{arg._boundingBox}
{}

ofVec2f Wall::calculatePointNormal(const ofVec2f& point) const
{
    ofVec2f pointVec = point - _start;
    ofVec2f proj = (_vector.dot(pointVec) / _vector.lengthSquared()) * _vector;

    return pointVec - proj;
}

bool Wall::isPointOutsideWall(const ofVec2f& point) const
{
    //  Check to see if the point is within the bounding box
    if (_hasBoundingBox && !_boundingBox.inside(point))
        return false;

    ofVec2f normal = calculatePointNormal(point);
    float dotProduct = _normalVec.dot(normal.getNormalized());

    if (dotProduct < 0)
        return true;

    return false;
}


Room::Room(const std::vector<ofVec2f>& points) 
{

}

void Room::buildRoom(const std::vector<ofVec2f>& points)
{
    
}