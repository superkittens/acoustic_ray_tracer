
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

void WorldView::drawRoomSoFar(const std::vector<ofVec2f>& points) const
{   
    //  Draw crosshairs on cursor
    drawWindow();
    ofSetColor(255, 255, 255);
    ofSetLineWidth(1.0);
    ofDrawLine(_cursorPosition.x, _cursorPosition.y - CROSSHAIR_LENGTH, _cursorPosition.x, _cursorPosition.y + CROSSHAIR_LENGTH);
    ofDrawLine(_cursorPosition.x - CROSSHAIR_LENGTH, _cursorPosition.y, _cursorPosition.x + CROSSHAIR_LENGTH, _cursorPosition.y);
    
    //  Draw walls
    ofSetLineWidth(5.0);
    if (!points.empty())
    {
        ofVec2f prevPoint = points.at(0);
        for (auto i = 1; i < points.size(); ++i)
        {
            ofDrawLine(prevPoint, points.at(i));
            prevPoint = points.at(i);
        }
        
        //  Draw a line between the last point and the cursor position
        ofDrawLine(prevPoint, _cursorPosition);
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
