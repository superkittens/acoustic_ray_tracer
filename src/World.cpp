#include "World.h"


const float World::WORLD_SCALE = 100;
const float World::SNAP_DELTA = 50;


void World::draw() const
{
    switch (_currentState)
    {
        case BUILDING:
        {
            if (_points.size() != 0)
            {
                ofSetColor(255, 255, 255);
                ofSetLineWidth(4);

                ofVec2f prevPoint = _points.at(0);
                std::string coordinates = "( " + to_string(prevPoint.x) + " , " + to_string(prevPoint.y) + " )";
                ofDrawBitmapString(coordinates, prevPoint);

                for (auto p = 1; p < _points.size(); ++p)
                {
                    ofDrawLine(prevPoint, _points.at(p));
                    prevPoint = _points.at(p);

                    coordinates = "( " + to_string(prevPoint.x) + " , " + to_string(prevPoint.y) + " )";
                    ofDrawBitmapString(coordinates, prevPoint);
                }

                ofDrawLine(prevPoint, _currentCursor);
            
                coordinates = "( " + to_string(_currentCursor.x) + " , " + to_string(_currentCursor.y) + " )";
                ofDrawBitmapString(coordinates, ofVec2f(20, ofGetHeight() - 10));

                ofVec2f delta = _currentCursor - _points.at(_points.size() - 1);
                std::string length = "Length: " + to_string(delta.length() / WORLD_SCALE) + " m";
                ofDrawBitmapString(length, ofVec2f{_currentCursor.x - 10, _currentCursor.y - 10});

            }
            break;
        }

        case BUILT:
        {
            ofSetColor(255, 255, 255);
            
            for (auto &w : _walls)
                w.draw();
        }

        default:
        break;
    }
}

void World::startWorldBuilding()
{
    if (_currentState == UNINITIALIZED)
        _currentState = BUILDING;
}

void World::setPoint()
{
    if (_currentState == BUILDING)
    {
        if (_points.size() != 0)
        {
            if (_currentCursor == _points.at(0))
            {
                buildWalls();
                _currentState = BUILT;
                _points.clear();

                return;
            }
        }
        
        _points.push_back(_currentCursor);
    }
}

void World::setCursor(const ofVec2f& point)
{
    _currentCursor = point;

    //  If the shift key is held, then lock either the cursor x value or y value to 
    if (_shiftKeyHeld && _points.size() > 0)
    {
        ofVec2f prevPoint = _points.at(_points.size() - 1);
        
        //  Lock y value
        if ((point.x > prevPoint.x + SNAP_DELTA) || (point.x < prevPoint.x - SNAP_DELTA))
            _currentCursor.y = prevPoint.y;

        //  Lock x value
        if ((point.y > prevPoint.y + SNAP_DELTA) || (point.y < prevPoint.y - SNAP_DELTA))
            _currentCursor.x = prevPoint.x;

        //  Snap to first point
        prevPoint = _points.at(0);
        if ((point.x < prevPoint.x + SNAP_DELTA) && (point.x > prevPoint.x - SNAP_DELTA) && (point.y < prevPoint.y + SNAP_DELTA) && (point.y > prevPoint.y - SNAP_DELTA))
            _currentCursor = prevPoint;
    }
}

void World::buildWalls()
{
    if (_points.size() == 0)
        _currentState = UNINITIALIZED;
    
    ofVec2f prevPoint = _points.at(0);
    for (auto p = 1; p < _points.size(); ++p)
    {
        _walls.push_back(Wall{prevPoint, _points.at(p), WORLD_SCALE});
        prevPoint = _points.at(p);
    }

    _walls.push_back(Wall{prevPoint, _points.at(0), WORLD_SCALE});
    
    _worldOrigin = _points.at(0);
}





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

void Wall::draw() const
{
    ofSetColor(255, 255, 255);
    ofSetLineWidth(10);
    ofDrawLine(_start, _end);
    std::string lengthString = to_string(getLength() / _scale) + " m";
    ofDrawBitmapString(lengthString, ofVec2f{_start.x - 10, _start.y - 10});

    //  Draw normal vector
    ofVec2f p0 = 0.5 * _vector + _start;
    ofVec2f p1 = 20 * _normalVec + p0;
    ofSetColor(255, 0, 0);
    ofDrawLine(p0, p1);
}

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
