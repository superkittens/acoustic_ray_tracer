
#include "WorldView.h"

const ofVec2f WorldView::_windowOffset = ofVec2f{400, 50};
const ofVec2f WorldView::_windowDimensions = ofVec2f{2000, 800};

void WorldView::setCursor(const ofVec2f& position)
{
    if (cursorInBounds(position))
        _cursorPosition = position;
}

void WorldView::drawRoomSoFar()
{   
    drawWindow();
}


void WorldView::drawWindow()
{
    ofSetColor(255, 255, 255, 80);
    ofDrawRectangle(_windowOffset.x, _windowOffset.y, _windowDimensions.x, _windowDimensions.y);

    ofSetColor(255, 0, 0);
    ofDrawCircle(_cursorPosition, 30);
}

bool WorldView::cursorInBounds(const ofVec2f& position) const
{
    if (position.x >= _windowOffset.x && 
        position.x <= _windowOffset.x + _windowDimensions.x &&
        position.y >= _windowOffset.y &&
        position.y <= _windowOffset.y + _windowDimensions.y)

        return true;

    return false;
}