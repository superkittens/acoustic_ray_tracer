#include "MainWindow.h"


void MainWindow::setup()
{
}

void MainWindow::mouseMoved(const ofVec2f& position)
{
    _controller.mouseMoved(position);
}

void MainWindow::mouseClicked(const ofVec2f& position)
{

}

void MainWindow::mouseDragged(const ofVec2f& position)

{
    
}

void MainWindow::draw()
{
    _controller.draw();
}