#pragma once

#include "ofMain.h"
#include "MainWindow.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	private:
		// static const float MAX_SIMULATION_TIME;
		// static const float SAMPLING_FREQ;
		// World world;
		// std::shared_ptr<Listener> listener;
		// std::shared_ptr<Emitter> emitter;
		// std::unique_ptr<Solver> solver;

		// Positioning ind;

		// void drawIR();
		MainWindow _mainWindow;
};
