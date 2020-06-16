#include "ofMain.h"
#include "ofApp.h"

//========================================================================

int main(int argc,char *argv[]){

	ofSetupOpenGL(1200, 650, OF_WINDOW); // <-------- setup the GL context
     ofApp *app = new ofApp();
      printf("XXXargs=%s\n",argv[1]);
     app->arg_x=argv[1];
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(app);
	
}
