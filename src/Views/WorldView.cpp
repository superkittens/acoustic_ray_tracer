
#include "WorldView.h"

const ofVec2f WorldView::_WINDOW_OFFSET = ofVec2f{300, 170};
const ofVec2f WorldView::_WINDOW_DIMENSIONS = ofVec2f{2000, 800};
const ofVec2f WorldView::_STATUS_BAR_OFFSET = ofVec2f{300, 20};
const ofVec2f WorldView::_STATUS_BAR_DIMENSIONS = ofVec2f{2000, 100};
const float WorldView::_CROSSHAIR_LENGTH = 50.0;
const float WorldView::_STATUS_BAR_COL_LENGTH = 300.0;


void WorldView::setCursor(const ofVec2f& position)
{
    _cursorPosition = position;
}

//  The status bar gives useful information at different states of the simulator
void WorldView::drawStatusBar(const RTState state) const{
    ofSetColor(WHITE, 40);
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
            ofSetColor(GRAY);
            ofSetLineWidth(5);
            ofNoFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            break;
        }
            
        case ROOM_BUILD:
        {
            stateString += "Build Room";
            
            ofSetColor(GRAY);
            ofSetLineWidth(5);
            ofNoFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            
            //  Draw cursor text
            ofSetColor(WHITE);
            ofDrawBitmapString("Cursor Pos: ", _STATUS_BAR_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + paddingY);
            break;
        }
            
        case NORMAL:
        {
            stateString += "Ready";
            
            ofSetColor(RED);
            ofFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            
            ofSetColor(WHITE);
            ofDrawBitmapString("Simulation:\nStopped/Not Started", _STATUS_BAR_OFFSET.x + 70, _STATUS_BAR_OFFSET.y + simulationIndOffset.y);
            ofDrawBitmapString("Simulation Progress:", _STATUS_BAR_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + paddingY);
            break;
        }
            
        case SIM_RUNNING:
        {
            stateString += "Simulate";
            
            ofSetColor(YELLOW);
            ofFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            
            ofSetColor(WHITE);
            ofDrawBitmapString("Simulation:\nRunning", _STATUS_BAR_OFFSET.x + 70, _STATUS_BAR_OFFSET.y + simulationIndOffset.y);
            ofDrawBitmapString("Simulation Progress:", _STATUS_BAR_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + paddingY);
            break;
        }
            
        case SIM_PAUSED:
        {
            stateString += "Simulate";
            
            ofSetColor(ORANGE);
            ofFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            
            ofSetColor(WHITE);
            ofDrawBitmapString("Simulation:\nPaused", _STATUS_BAR_OFFSET.x + 70, _STATUS_BAR_OFFSET.y + simulationIndOffset.y);
            ofDrawBitmapString("Simulation Progress:", _STATUS_BAR_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + paddingY);
            break;
        }
            
        case SIM_DONE:
        {
            stateString += "Simulate";
            
            ofSetColor(GREEN);
            ofFill();
            ofDrawCircle(_STATUS_BAR_OFFSET.x + simulationIndOffset.x, _STATUS_BAR_OFFSET.y + simulationIndOffset.y, simulationIndRadius);
            
            ofSetColor(WHITE);
            ofDrawBitmapString("Simulation:\nDONE", _STATUS_BAR_OFFSET.x + 70, _STATUS_BAR_OFFSET.y + simulationIndOffset.y);
            ofDrawBitmapString("Simulation Progress:", _STATUS_BAR_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + paddingY);
            break;
        }
            
        default:
            break;
    }
    
    ofSetColor(WHITE);
    ofDrawBitmapString(stateString, _STATUS_BAR_OFFSET.x + 5, _STATUS_BAR_OFFSET.y + paddingY);
}

void WorldView::drawEmptyWindow() const
{
    drawWindow();
}

//  Called when the room is being built
//  The user defines the room's vertices and this function will draw lines between them to form walls
void WorldView::drawRoomSoFar(const std::tuple<const std::vector<ofVec2f>&, const float>& roomDrawData) const
{   
    //  Draw crosshairs on cursor
    drawWindow();
    ofSetColor(255, 255, 255);
    ofSetLineWidth(1.0);
    ofDrawLine(_cursorPosition.x, _cursorPosition.y - _CROSSHAIR_LENGTH, _cursorPosition.x, _cursorPosition.y + _CROSSHAIR_LENGTH);
    ofDrawLine(_cursorPosition.x - _CROSSHAIR_LENGTH, _cursorPosition.y, _cursorPosition.x + _CROSSHAIR_LENGTH, _cursorPosition.y);
    
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

//  Called when the room is fully build but no simulation is running
void WorldView::drawNormalState(const Room& room, const float scale, const Source& source, const Listener& listener) const
{
    drawWindow();
    
    //  Draw walls
    ofSetLineWidth(5.0);
    
    const auto& walls = room.getWalls();
    
    for (auto& wall : walls)
    {
        //  Wall coordinates are in room space, not pixel space so we need to make the conversion here
        const auto startPoint = wall.getStart();
        const auto endPoint = wall.getEnd();
        
        //  Draw wall
        ofSetColor(WHITE);
        ofDrawLine(startPoint, endPoint);
        
        //  Draw Normal Vector
        ofSetColor(RED);
        const auto normalStartPoint = 0.5 * wall.getVector() + startPoint;
        const auto normalEndPoint = normalStartPoint + (20.0 * wall.getNormalUnitVector());
        ofDrawLine(normalStartPoint, normalEndPoint);
        
        //  Draw length of wall
        ofSetColor(WHITE);
        std::string wallLengthString = to_string(wall.getLength() * scale) + " m";
        ofDrawBitmapString(wallLengthString, normalStartPoint.x + 10, normalStartPoint.y - 20);
    }
    
    //  Draw sources, listeners and their IDs
    if (source.getVisibility())
    {
        ofSetColor(source.getColor());
        ofFill();
        ofDrawCircle(source.getCoordinates(), source.getRadius());
    }

    ofSetColor(listener.getColor());
    ofDrawCircle(listener.getCoordinates(), listener.getRadius());
}

//  Draw the room and the acoustic rays as the simulation is running
//  This function is also called when the simulation is complete (when the program state is SIM_DONE)
void WorldView::drawSimulateState(const Room& room, const float scale, const Source& source, const Listener& listener, const std::vector<Ray>& rays) const
{
    drawNormalState(room, scale, source, listener);
    
    //  Draw the rays
    ofSetLineWidth(0.5);
    ofSetColor(WHITE);
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
    
    ofSetColor(WHITE, 40);
    ofDrawRectangle(_WINDOW_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + 30, progressBarWidth, progressBarHeight);
    ofSetColor(PINK);
    ofDrawRectangle(_WINDOW_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + 30, progressBarWidth * timeRatio, progressBarHeight);
    
    ofSetColor(WHITE);
    std::string progressString = to_string(timeRatio * 100.0) + " %";
    ofDrawBitmapString(progressString, _WINDOW_OFFSET.x + _STATUS_BAR_COL_LENGTH, _STATUS_BAR_OFFSET.y + 80);
}

//  For debugging purposes only
//  Draws a single ray
void WorldView::drawSimulateStateDebug(const SimulationDataDebug& data) const
{
    //  Unpack the tuple
    const Room& room = std::get<0>(data);
    const float worldScale = std::get<1>(data);
    const Source source = std::get<2>(data);
    const Listener& listener = std::get<3>(data);
    const ofVec2f rayPos = std::get<4>(data);
    
//    drawNormalState(std::make_tuple(room, worldScale, source, listener));
    
    ofSetColor(WHITE);
    ofDrawCircle(rayPos, 25);
}

//  Draw the window frame where the room lives
void WorldView::drawWindow() const
{
    ofSetColor(WHITE);
    ofDrawBitmapString("World View", _WINDOW_OFFSET.x, _WINDOW_OFFSET.y - 10);
    
    ofFill();
    ofSetColor(WHITE, 80);
    ofDrawRectangle(_WINDOW_OFFSET.x, _WINDOW_OFFSET.y, _WINDOW_DIMENSIONS.x, _WINDOW_DIMENSIONS.y);
}

void WorldView::drawCursorPosInStatusBar(const ofVec2f pos) const
{
    ofSetColor(WHITE);
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
