#include "MainWindow.h"

const float MainWindow::MAX_SCALE = 10.0;
const float MainWindow::SLIDER_WIDTH = 0;
const float MainWindow::SLIDER_HEIGHT = 100;


void MainWindow::setup()
{
    _roomBuildPanel.setup();
    _roomBuildPanel.add(_createRoomButton.setup("Create Room"));
    _roomBuildPanel.add(_addSourceButton.setup(("Add Source")));
    _roomBuildPanel.add(_addListenerButton.setup("Add Listener"));
    _roomBuildPanel.add(_clearRoomButton.setup("Clear"));
    _roomBuildPanel.add(_worldScaleSlider.setup("Scale (m / px", 0.01, 0.1, MAX_SCALE, SLIDER_WIDTH, SLIDER_HEIGHT));

    _createRoomButton.addListener(&_controller, &RTController::onCreateRoomClicked);
    _worldScaleSlider.addListener(&_controller, &RTController::onWorldScaleSliderChanged);
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
}
