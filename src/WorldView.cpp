
#include "WorldView.h"

const ofVec2f WorldView::_WINDOW_OFFSET = ofVec2f{300, 200};
const ofVec2f WorldView::_WINDOW_DIMENSIONS = ofVec2f{2000, 800};
const ofVec2f WorldView::_STATUS_BAR_OFFSET = ofVec2f{300, 20};
const ofVec2f WorldView::_STATUS_BAR_DIMENSIONS = ofVec2f{2000, 100};
const float WorldView::CROSSHAIR_LENGTH = 50.0;
const float WorldView::_STATUS_BAR_COL_LENGTH = 300.0;

void WorldView::setCursor(const ofVec2f& position)
{
    _cursorPosition = position;
}

void WorldView::drawStatusBar(const RTState state) const{
    ofSetColor(255, 255, 255, 40);
    ofDrawRectangle(_STATUS_BAR_OFFSET, _STATUS_BAR_DIMENSIONS.x, _STATUS_BAR_DIMENSIONS.y);
    
    std::string stateString = "Current Mode: ";
    const ofVec2f simulationIndOffset(30, 60);
    const float simulationIndRadius = 20;
    const float paddingY = 20;
    
    switch (state)
    {
        case START:
        {
            stateString += "Start";
            ofSetColor(127, 127, 127);
            ofSetLineWidth(5);
            ofNoFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            break;
        }
            
        case ROOM_BUILD:
        {
            stateString += "Build Room";
            
            ofSetColor(127, 127, 127);
            ofSetLineWidth(5);
            ofNoFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            
            //  Draw cursor text
            ofSetColor(255, 255, 255);
            ofDrawBitmapString("Cursor Pos: ", _STATUS_BAR_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + paddingY);
            break;
        }
            
        case NORMAL:
        {
            stateString += "Ready";
            
            ofSetColor(236, 106, 94);
            ofFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            
            ofSetColor(255, 255, 255);
            ofDrawBitmapString("Simulation:\nStopped/Not Started", _STATUS_BAR_OFFSET.x + 70, _STATUS_BAR_OFFSET.y + simulationIndOffset.y);
            ofDrawBitmapString("Simulation Progress:", _STATUS_BAR_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + paddingY);
            break;
        }
            
        case SIM_RUNNING:
        {
            stateString += "Simulate";
            
            ofSetColor(244, 190, 79);
            ofFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            
            ofSetColor(255, 255, 255);
            ofDrawBitmapString("Simulation:\nRunning", _STATUS_BAR_OFFSET.x + 70, _STATUS_BAR_OFFSET.y + simulationIndOffset.y);
            ofDrawBitmapString("Simulation Progress:", _STATUS_BAR_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + paddingY);
            break;
        }
            
        case SIM_PAUSED:
        {
            stateString += "Simulate";
            
            ofSetColor(215, 95, 0);
            ofFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            
            ofSetColor(255, 255, 255);
            ofDrawBitmapString("Simulation:\nPaused", _STATUS_BAR_OFFSET.x + 70, _STATUS_BAR_OFFSET.y + simulationIndOffset.y);
            ofDrawBitmapString("Simulation Progress:", _STATUS_BAR_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + paddingY);
            break;
        }
            
        case SIM_DONE:
        {
            stateString += "Simulate";
            
            ofSetColor(97, 197, 85);
            ofFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            
            ofSetColor(255, 255, 255);
            ofDrawBitmapString("Simulation:\nDONE", _STATUS_BAR_OFFSET.x + 70, _STATUS_BAR_OFFSET.y + simulationIndOffset.y);
            ofDrawBitmapString("Simulation Progress:", _STATUS_BAR_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + paddingY);
            break;
        }
            
        default:
            break;
    }
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(stateString, _STATUS_BAR_OFFSET.x + 5, _STATUS_BAR_OFFSET.y + paddingY);
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
            ofVec2f pointWorldView = prevPoint - _WINDOW_OFFSET;
            std::string coordinateString = "( " + to_string(pointWorldView.x) + " , " + to_string(pointWorldView.y) + " )";
            ofDrawBitmapString(coordinateString, prevPoint.x, prevPoint.y - 10);
            
            auto currentPoint = points.at(i);
            pointWorldView = currentPoint - _WINDOW_OFFSET;
            coordinateString = "( " + to_string(pointWorldView.x) + " , " + to_string(pointWorldView.y) + " )";
            ofDrawBitmapString(coordinateString, currentPoint.x, currentPoint.y - 10);
            
            ofDrawLine(prevPoint, currentPoint);
            prevPoint = currentPoint;
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
    drawCursorPosInStatusBar(_cursorPosition - _WINDOW_OFFSET);
}

void WorldView::drawNormalState(const std::tuple<const Room&, const float, const Source&, const std::vector<Listener>&>& data) const
{
    drawWindow();
    
    //  Unpack the tuple
    const Room& room = std::get<0>(data);
    const float worldScale = std::get<1>(data);
    const Source source = std::get<2>(data);
    const std::vector<Listener>& listeners = std::get<3>(data);
    
    //  Draw walls
    ofSetLineWidth(5.0);
    
    const auto& walls = room.getWalls();
    
    for (auto& wall : walls)
    {
        //  Wall coordinates are in room space, not pixel space so we need to make the conversion here
        const auto startPoint = wall.getStart();
        const auto endPoint = wall.getEnd();
        
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
    if (source.getVisibility())
    {
        ofSetColor(source.getColor());
        ofFill();
        ofDrawCircle(source.getCoordinates(), source.getRadius());
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

void WorldView::drawSimulateState(const SimulationData& data) const
{
    //  Unpack the tuple
    const Room& room = std::get<0>(data);
    const float worldScale = std::get<1>(data);
    const Source source = std::get<2>(data);
    const std::vector<Listener>& listeners = std::get<3>(data);
    const std::vector<Ray>& rays = std::get<4>(data);
    
    drawNormalState(std::make_tuple(room, worldScale, source, listeners));
    
    //  Draw the rays
    ofSetLineWidth(0.5);
    for (const auto& ray : rays)
    {
        ofDrawCircle(ray.getPosition(), 2);
//        ofVec2f prevPoint = ray.getRayPaths().at(0);
//        for (auto i = 1; i < ray.getRayPaths().size(); ++i)
//        {
//            ofDrawLine(prevPoint, ray.getRayPaths().at(i));
//            prevPoint = ray.getRayPaths().at(i);
//        }
//
//        ofDrawLine(prevPoint, ray.getPosition());
    }
}

//  Draw the simulation progress bar on the status bar
void WorldView::drawSimulationProgress(const float timeRatio) const
{
    const float progressBarWidth = 500.0;
    const float progressBarHeight = 30.0;
    
    ofSetColor(255, 255, 255, 40);
    ofDrawRectangle(_WINDOW_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + 30, progressBarWidth, progressBarHeight);
    ofSetColor(255, 0, 128);
    ofDrawRectangle(_WINDOW_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + 30, progressBarWidth * timeRatio, progressBarHeight);
    
    ofSetColor(255, 255, 255);
    std::string progressString = to_string(timeRatio * 100.0) + " %";
    ofDrawBitmapString(progressString, _WINDOW_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + 80);
}

void WorldView::drawSimulateStateDebug(const SimulationDataDebug& data) const
{
    //  Unpack the tuple
    const Room& room = std::get<0>(data);
    const float worldScale = std::get<1>(data);
    const Source source = std::get<2>(data);
    const std::vector<Listener>& listeners = std::get<3>(data);
    const ofVec2f rayPos = std::get<4>(data);
    
    drawNormalState(std::make_tuple(room, worldScale, source, listeners));
    
    ofSetColor(255, 255, 255);
    ofDrawCircle(rayPos, 25);
}


void WorldView::drawWindow() const
{
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("World View", _WINDOW_OFFSET.x, _WINDOW_OFFSET.y - 10);
    
    ofFill();
    ofSetColor(255, 255, 255, 80);
    ofDrawRectangle(_WINDOW_OFFSET.x, _WINDOW_OFFSET.y, _WINDOW_DIMENSIONS.x, _WINDOW_DIMENSIONS.y);
}

void WorldView::drawCursorPosInStatusBar(const ofVec2f pos) const
{
    ofSetColor(255, 255, 255);
    std::string posString = "x: " + to_string(pos.x) + "\n" + "y: " + to_string(pos.y);
    ofDrawBitmapString(posString, _STATUS_BAR_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + 40);
}

bool WorldView::withinBounds(const ofVec2f& position) const
{
    if (position.x >= _WINDOW_OFFSET.x &&
        position.x <= _WINDOW_OFFSET.x + _WINDOW_DIMENSIONS.x &&
        position.y >= _WINDOW_OFFSET.y &&
        position.y <= _WINDOW_OFFSET.y + _WINDOW_DIMENSIONS.y)

        return true;

    return false;
}
