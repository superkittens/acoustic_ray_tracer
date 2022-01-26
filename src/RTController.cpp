
#include "RTController.h"

const float RTController::SNAP_THRESHOLD = 50.0;

void RTController::mouseMoved(const ofVec2f& position)
{
    switch (_currentState)
    {
        case ROOM_BUILD:
        {
            auto cursorPos = position;
            auto vertices = _model.getRoomVertices();
            
            if (_drawStraightLines)
                cursorPos = snapCursor(cursorPos);
            
            _worldView.setCursor(cursorPos);
            break;
        }
            
        default:
            break;
    }
}

void RTController::mouseClicked(const ofVec2f& position, const int button)
{
    switch (_currentState)
    {
        case ROOM_BUILD:
        {
            auto point = position;
            
            if (_worldView.withinBounds(position))
            {
                if (_drawStraightLines)
                    point = snapCursor(point);
                
                _model.addRoomVertex(point);
            }
            
            break;
        }
            
        default:
            break;
    }
}

void RTController::mouseDragged(const ofVec2f& position, const int button)
{

}

void RTController::keyPressed(const int key)
{
    switch (key)
    {
        case ofKey::OF_KEY_ESC:
            if (_currentState == ROOM_BUILD)
                _currentState = START;
            
            break;
        
        case ofKey::OF_KEY_SHIFT:
            _drawStraightLines = true;
            break;
            
        default:
        break;
    }
}

void RTController::keyReleased(const int key)
{
    switch (key)
    {
        case ofKey::OF_KEY_SHIFT:
            _drawStraightLines = false;
            break;
        
        default:
            break;
    }
}

void RTController::draw() const
{
    switch (_currentState)
    {
        case START:
        {
            _worldView.drawEmptyWindow();
            break;
        }

        case ROOM_BUILD:
        {
            _worldView.drawRoomSoFar(_model.getRoomVertices());
            break;
        }
            
        default:
            break;
    }
}

void RTController::onCreateRoomClicked()
{
    if (_currentState == START)
        _currentState = ROOM_BUILD;
}

ofVec2f RTController::snapCursor(const ofVec2f& cursorPos)
{
    ofVec2f outputCursor = cursorPos;
    const auto vertices = _model.getRoomVertices();
    
    if (!vertices.empty())
    {
        const auto lastPoint = vertices.back();
        
        if (cursorPos.x > lastPoint.x + SNAP_THRESHOLD || cursorPos.x < lastPoint.x - SNAP_THRESHOLD)
            outputCursor.y = lastPoint.y;
        if (cursorPos.y > lastPoint.y + SNAP_THRESHOLD || cursorPos.y < lastPoint.y - SNAP_THRESHOLD)
            outputCursor.x = lastPoint.x;
    }
    
    return outputCursor;
}
