#include "MainWindow.h"

const float MainWindow::START_TIME_STEP = 0.00002267;
const float MainWindow::MAX_SCALE = 1.0;
const float MainWindow::MAX_SIM_TIME = 10.0;
const int MainWindow::MAX_NUM_RAYS = 10000000;
const float MainWindow::MIN_SCALE = 0.001;
const float MainWindow::MIN_SIM_TIME = 0.1;
const int MainWindow::MIN_NUM_RAYS = 1;
const float MainWindow::SLIDER_WIDTH = 0;
const float MainWindow::SLIDER_HEIGHT = 100;


void MainWindow::setup()
{
    _roomBuildPanel.setup("Room Build Menu", "room_build_settings.xml", 10, 10);
    _roomBuildPanel.add(_createRoomButton.setup("Create Room"));
    _roomBuildPanel.add(_clearRoomButton.setup("Clear"));
    _roomBuildPanel.add(_worldScaleSlider.setup("Scale (m / px", MIN_SCALE, MIN_SCALE, MAX_SCALE, SLIDER_WIDTH, SLIDER_HEIGHT));

    _createRoomButton.addListener(&_controller, &RTController::onCreateRoomClicked);
    _worldScaleSlider.addListener(&_controller, &RTController::onWorldScaleSliderChanged);
    _clearRoomButton.addListener(&_controller, &RTController::onClearRoomClicked);
    
    _simulationPanel.setup("Simulation Menu", "sim_settings.xml", 10, 220);
    _simulationPanel.add(_startSimButton.setup("Start"));
    _simulationPanel.add(_pauseSimButton.setup("Pause"));
    _simulationPanel.add(_stopSimButton.setup("Stop"));
    _simulationPanel.add(_simTimeSlider.setup("Sim Time [sec]", MIN_SIM_TIME, MIN_SIM_TIME, MAX_SIM_TIME, SLIDER_WIDTH, SLIDER_HEIGHT));
    _simulationPanel.add(_numRaysLabel.setup("", "Num Rays", SLIDER_WIDTH, SLIDER_HEIGHT / 3));
    _simulationPanel.add(_numRaysField.setup(MIN_NUM_RAYS, SLIDER_WIDTH, SLIDER_HEIGHT));
    _simulationPanel.add(_timeStepLabel.setup("", "Time Step [sec]", SLIDER_WIDTH, SLIDER_HEIGHT / 3));
    _simulationPanel.add(_timeStepField.setup(START_TIME_STEP, SLIDER_WIDTH, SLIDER_HEIGHT));
    
    _startSimButton.addListener(&_controller, &RTController::onStartSimClicked);
    _pauseSimButton.addListener(&_controller, &RTController::onPauseSimClicked);
    _stopSimButton.addListener(&_controller, &RTController::onStopSimClicked);
    _simTimeSlider.addListener(&_controller, &RTController::onSimTimeSliderChanged);
    _numRaysField.addListener(&_controller, &RTController::onNumRaysChanged);
    _timeStepField.addListener(&_controller, &RTController::onTimeStepChanged);
    
    _controller.setup(MIN_SCALE, MIN_SIM_TIME, START_TIME_STEP, MIN_NUM_RAYS);
}

void MainWindow::mouseMoved(const ofVec2f& position)
{
    _controller.mouseMoved(position);
}

void MainWindow::mouseClicked(const ofVec2f& position, const int button)
{
    _controller.mouseClicked(position, button);
}

void MainWindow::mouseDragged(const ofVec2f& position, const int button)
{
    _controller.mouseDragged(position, button);
}

void MainWindow::mouseReleased(const ofVec2f& position, const int button)
{
    _controller.mouseReleased(position, button);
}

void MainWindow::keyPressed(const int key)
{
    _controller.keyPressed(key);
}

void MainWindow::keyReleased(const int key)
{
    _controller.keyReleased(key);
}

void MainWindow::draw()
{
    _controller.draw();
    _roomBuildPanel.draw();
    _simulationPanel.draw();
}

void MainWindow::update()
{
    _controller.update();
}
