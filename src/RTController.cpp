
#include "RTController.h"

const float RTController::SNAP_THRESHOLD = 50.0;

void RTController::mouseMoved(const ofVec2f& position)
{
    switch (_currentState)
    {
        case ROOM_BUILD:
        {
            if (_worldView.withinBounds(position))
            {
                auto cursorPos = position;
                
                if (_drawStraightLines)
                {
                    cursorPos = snapCursor(cursorPos);
                    cursorPos = snapCursorToFirstPoint(cursorPos);
                }
                
                _worldView.setCursor(cursorPos);
            }
            
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
                {
                    point = snapCursor(point);
                    point = snapCursorToFirstPoint(point);
                }
                
                //  First check to see if the point is the first point
                //  If it is, then that means the room is closed and we can start building the room and move onto the NORMAL state
                const auto points = _model.getRoomVertices();
                if (!points.empty())
                {
                    if (point == points.at(0))
                    {
                        _currentState = NORMAL;
                        
                        _model.buildRoom(_worldView.getWindowOrigin());
                        _model.clearRoomVertices();
                        
                        break;
                    }
                }
                    
                _model.addRoomVertex(point);
            }
            
            break;
        }
            
        case NORMAL:
        {
            //  Grab sources or listeners (if applicable)
            for (auto& source: _model.getSoundSources())
                source.grab(position);
            
            for (auto& listener: _model.getListeners())
                listener.grab(position);
            
            break;
        }
            
        default:
            break;
    }
}

void RTController::mouseDragged(const ofVec2f& position, const int button)
{
    switch (_currentState)
    {
        case START:
            break;
            
        case NORMAL:
        {
            for (auto& source : _model.getSoundSources())
                source.move(position);
            
            for (auto& listener : _model.getListeners())
                listener.move(position);
            break;
        }
            
        default:
            break;
    }
}

void RTController::mouseReleased(const ofVec2f& position, const int button)
{
    switch (_currentState)
    {
        case START:
            break;
            
        case NORMAL:
        {
            for (auto& source : _model.getSoundSources())
                source.release();
            
            for (auto& listener : _model.getListeners())
                listener.release();
            
            break;
        }
            
        default:
            break;
    }
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
            //  Package data relevant to drawing the incomplete room
            auto data = std::make_tuple(_model.getRoomVertices(), _model.getWorldScale());
            _worldView.drawRoomSoFar(data);
            break;
        }
            
        case NORMAL:
        {
            //  Package data for drawing the room
            auto data = std::make_tuple(_model.getRoom(), _model.getWorldScale(), _model.getSoundSources(), _model.getListeners());
            _worldView.drawNormalState(data);
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

void RTController::onWorldScaleSliderChanged(float& value)
{
    _model.setWorldScale(value);
}

void RTController::onClearRoomClicked()
{
    _currentState = START;
    _model.reset();
}

void RTController::onAddSourceClicked()
{
    if (_currentState == NORMAL)
        _model.addSoundSource();
}

void RTController::onAddListenerClicked()
{
    if (_currentState == NORMAL)
        _model.addListener();
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


ofVec2f RTController::snapCursorToFirstPoint(const ofVec2f& cursorPos)
{
    const auto points = _model.getRoomVertices();
    if (!points.empty())
    {
        const auto firstPoint = points.front();
        if (cursorPos.x <= firstPoint.x + SNAP_THRESHOLD &&
            cursorPos.x >= firstPoint.x - SNAP_THRESHOLD &&
            cursorPos.y <= firstPoint.y + SNAP_THRESHOLD &&
            cursorPos.y >= firstPoint.y - SNAP_THRESHOLD)
        {
            return firstPoint;
        }
    }
    
    return cursorPos;
}
