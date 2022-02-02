
#include "WorldView.h"

const ofVec2f WorldView::_windowOffset = ofVec2f{400, 50};
const ofVec2f WorldView::_windowDimensions = ofVec2f{2000, 800};
const float WorldView::CROSSHAIR_LENGTH = 50.0;

void WorldView::setCursor(const ofVec2f& position)
{
    _cursorPosition = position;
}

void WorldView::drawEmptyWindow() const
{
    drawWindow();
}

void WorldView::drawRoomSoFar(const std::tuple<const std::vector<ofVec2f>&, const float>& roomDrawData) const
{   
    //  Draw crosshairs on cursor
    drawWindow();
    ofSetColor(255, 255, 255);
    ofSetLineWidth(1.0);
    ofDrawLine(_cursorPosition.x, _cursorPosition.y - CROSSHAIR_LENGTH, _cursorPosition.x, _cursorPosition.y + CROSSHAIR_LENGTH);
    ofDrawLine(_cursorPosition.x - CROSSHAIR_LENGTH, _cursorPosition.y, _cursorPosition.x + CROSSHAIR_LENGTH, _cursorPosition.y);
    
    //  Unpack the tuple
    const std::vector<ofVec2f>& points = std::get<0>(roomDrawData);
    const float worldScale = std::get<1>(roomDrawData);
    
    //  Draw walls
    ofSetLineWidth(5.0);
    if (!points.empty())
    {
        ofVec2f prevPoint = points.at(0);
        for (auto i = 1; i < points.size(); ++i)
        {
            //  Draw coordinates of each vertex
            ofVec2f pointWorldView = prevPoint - _windowOffset;
            std::string coordinateString = "( " + to_string(pointWorldView.x) + " , " + to_string(pointWorldView.y) + " )";
            ofDrawBitmapString(coordinateString, prevPoint.x, prevPoint.y - 10);
            
            auto currentPoint = points.at(i);
            pointWorldView = currentPoint - _windowOffset;
            coordinateString = "( " + to_string(pointWorldView.x) + " , " + to_string(pointWorldView.y) + " )";
            ofDrawBitmapString(coordinateString, currentPoint.x, currentPoint.y - 10);
            
            ofDrawLine(prevPoint, points.at(i));
            prevPoint = points.at(i);
        }

        //  Draw a line between the last point and the cursor position
        ofDrawLine(prevPoint, _cursorPosition);
        
        //  Draw length of wall on screen
        auto lastPoint = points.back();
        const auto wallLength = _cursorPosition - lastPoint;
        std::string wallLengthString = to_string(wallLength.length() * worldScale) + " m";
        ofDrawBitmapString(wallLengthString, _cursorPosition.x + 10, _cursorPosition.y - 10);
    }

    //  Draw coordinates on screen
    auto worldViewCoordinate = _cursorPosition - _windowOffset;
    std::string coordinatesString = "( " + to_string(worldViewCoordinate.x) + " , " + to_string(worldViewCoordinate.y) + " )";
    ofDrawBitmapString(coordinatesString, _windowOffset.x + 10, _windowOffset.y + _windowDimensions.y - 10);
}

void WorldView::drawNormalState(const std::tuple<const Room&, const float, const std::vector<Source>&, const std::vector<Listener>&>& data) const
{
    drawWindow();
    
    //  Unpack the tuple
    const Room& room = std::get<0>(data);
    const float worldScale = std::get<1>(data);
    const std::vector<Source>& sources = std::get<2>(data);
    const std::vector<Listener>& listeners = std::get<3>(data);
    
    //  Draw walls
    ofSetLineWidth(5.0);
    
    const auto& walls = room.getWalls();
    const auto roomOrigin = room.getOrigin();
    
    for (auto& wall : walls)
    {
        //  Wall coordinates are in room space, not pixel space so we need to make the conversion here
        const auto startPoint = wall.getStart() + roomOrigin;
        const auto endPoint = wall.getEnd() + roomOrigin;
        
        //  Draw wall
        ofSetColor(255, 255, 255);
        ofDrawLine(startPoint, endPoint);
        
        //  Draw Normal Vector
        ofSetColor(255, 127, 0);
        const auto normalStartPoint = 0.5 * wall.getVector() + startPoint;
        const auto normalEndPoint = normalStartPoint + (20.0 * wall.getNormalUnitVector());
        ofDrawLine(normalStartPoint, normalEndPoint);
        
        //  Draw length of wall
        ofSetColor(255, 255, 255);
        std::string wallLengthString = to_string(wall.getLength() * worldScale) + " m";
        ofDrawBitmapString(wallLengthString, normalStartPoint.x + 10, normalStartPoint.y - 20);
    }
    
    //  Draw sources, listeners and their IDs
    for (const auto& source : sources)
    {
        ofSetColor(source.getColor());
        ofDrawCircle(source.getCoordinates(), source.getRadius());
        
        ofSetColor(255, 255, 255);
        std::string idString = to_string(source.getId());
        ofDrawBitmapString(idString, source.getCoordinates());
    }
    
    for (const auto& listener: listeners)
    {
        ofSetColor(listener.getColor());
        ofDrawCircle(listener.getCoordinates(), listener.getRadius());
        
        ofSetColor(255, 255, 255);
        std::string idString = to_string(listener.getId());
        ofDrawBitmapString(idString, listener.getCoordinates());
    }
}


void WorldView::drawWindow() const
{
    ofSetColor(255, 255, 255, 80);
    ofDrawRectangle(_windowOffset.x, _windowOffset.y, _windowDimensions.x, _windowDimensions.y);
}

bool WorldView::withinBounds(const ofVec2f& position) const
{
    if (position.x >= _windowOffset.x && 
        position.x <= _windowOffset.x + _windowDimensions.x &&
        position.y >= _windowOffset.y &&
        position.y <= _windowOffset.y + _windowDimensions.y)

        return true;

    return false;
}
