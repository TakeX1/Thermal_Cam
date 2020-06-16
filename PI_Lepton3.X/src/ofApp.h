#pragma once

#include "ofMain.h"
#include "ofxOsc.h"


// send host (aka ip address)
//#define HOST "192.168.0.8"

/// send port
#define SPORT 8090
#define RPORT 8091
// demonstrates sending OSC messages with an ofxOscSender,
// use in conjunction with the oscReceiveExample
class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofTrueTypeFont font,font1;
		ofxOscSender sender;
		ofxOscReceiver receiver;
		ofBuffer imgAsBuffer;
		
		string arg_x;
		string HOST="192.168.0.12";
    
    ofxOscMessage mm;
    
    ofPixels pixels;
		
		
		
};
