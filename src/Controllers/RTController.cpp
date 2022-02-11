
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
                        buildRoom();
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
            _model.getSoundSource().grab(position);
            _model.getListener().grab(position);
            
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
            _model.getSoundSource().move(position);
            _model.getListener().move(position);

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
            _model.getSoundSource().release();
            _model.getListener().release();
            
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
    _worldView.drawStatusBar(_currentState);
    
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
            _worldView.drawNormalState(_model.getRoom(), _model.getWorldScale(), _model.getSoundSource(), _model.getListener());
            break;
        }
            
        case SIM_RUNNING:
        case SIM_PAUSED:
        case SIM_DONE:
        {
            _worldView.drawSimulateState(_model.getRoom(), _model.getWorldScale(), _model.getSoundSource(), _model.getListener(), _model.getRays());
            _worldView.drawSimulationProgress(_model.getCurrentSimulationTime() / _model.getSimulationTime());
            _graphView.draw(_model.getImpulseResponse(LEFT), _model.getImpulseResponse(RIGHT));

            break;
        }
            
        default:
            break;
    }
}

void RTController::setup(const float worldScale, const float simTime, const float timeStep, const size_t numRays)
{
    _model.setWorldScale(worldScale);
    _model.setSimulationTime(simTime);
    _model.setTimeStep(timeStep);
    _model.setNumRays(numRays);
}

void RTController::update()
{
    switch (_currentState)
    {
        //  Get the latest ray data from the solver when running the simulation
        case SIM_RUNNING:
        {
            _counter++;
            if (_counter >= 60)
            {
                _counter = 0;
                if (_model.getSimulationStatus())
                    _model.updateSnapshot();
                else
                    _currentState = SIM_DONE;
            }
            
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

void RTController::onStartSimClicked()
{
    //  The simulator must be in NORMAL mode (ie. a room, source and listener must be present)
    if (_currentState == NORMAL || _currentState == SIM_DONE)
    {
        _model.startRayTrace();
        _currentState = SIM_RUNNING;
        _graphView.setup();
    }
}

void RTController::onPauseSimClicked()
{
    if (_currentState == SIM_RUNNING)
    {
        _model.pauseRayTrace(true);
        _currentState = SIM_PAUSED;
    }
    
    else
    {
        _model.pauseRayTrace(false);
        _currentState = SIM_RUNNING;
    }
}

void RTController::onStopSimClicked()
{
    if (_currentState == SIM_RUNNING || _currentState == SIM_PAUSED)
    {
        _model.stopRayTrace();
        _currentState = NORMAL;
    }
}

void RTController::onSimTimeSliderChanged(float& value)
{
    _model.setSimulationTime(value);
}

void RTController::onNumRaysChanged(size_t& value)
{
    _model.setNumRays(value);
}

void RTController::onTimeStepChanged(float& value)
{
    _model.setTimeStep(value);
}

void RTController::onWriteIRClicked()
{
    //  IRs can only be written to file AFTER a simulation is complete
    if (_currentState == SIM_DONE)
    {
        //  We first need to get the directory where the user wants to write the IR file
        auto result = ofSystemLoadDialog("Choose Directory", true, "");
        auto filePath = result.getPath();
        
//        _currentState = IR_WRITE;
        _currentIRBeingWritten = LEFT;
        
        _fileWriter.writeIRToFile(_model.getImpulseResponse(LEFT), filePath + "/left_ir.txt", true);
        _fileWriter.writeIRToFile(_model.getImpulseResponse(RIGHT), filePath + "/right_ir.txt", true);
    }
}

ofVec2f RTController::snapCursor(const ofVec2f& cursorPos)
{
    ofVec2f outputCursor = cursorPos;
    const auto vertices = _model.getRoomVertices();
    
    if (!vertices.empty())
    {
        const auto lastPoint = vertices.back();
        
        if ((cursorPos.x > lastPoint.x + SNAP_THRESHOLD || cursorPos.x < lastPoint.x - SNAP_THRESHOLD) && (cursorPos.y >= lastPoint.y - SNAP_THRESHOLD && cursorPos.y <= lastPoint.y + SNAP_THRESHOLD))
            outputCursor.y = lastPoint.y;
        if ((cursorPos.y > lastPoint.y + SNAP_THRESHOLD || cursorPos.y > lastPoint.y - SNAP_THRESHOLD) && (cursorPos.x >= lastPoint.x - SNAP_THRESHOLD && cursorPos.x <= lastPoint.x + SNAP_THRESHOLD))
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

void RTController::buildRoom()
{
    _currentState = NORMAL;
    
    _model.buildRoom();
    _model.clearRoomVertices();
    
    auto windowOrigin = _worldView.getWindowOrigin();
    auto windowDimensions = _worldView.getWindowDimensions();
    auto windowHalfPoint = ofVec2f{windowOrigin.x + (windowDimensions.x / 2), windowOrigin.y + (windowDimensions.y / 2)};
    
    _model.addSoundSource(windowHalfPoint);
    _model.addListener(windowHalfPoint + ofVec2f{100, 0});
}
