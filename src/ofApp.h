#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ParticleSystem.h"

using namespace glm;

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
		
		ParticleSystem myParticleSystem;

		ofxLabel myFpsLabel;
		ofParameter<float> paramAmplitude;
		ofParameter<float> paramFrequency;
		ofParameter<float> paramScale;

        ofxLabel feedLabel;
        ofParameter<float>  paramFeedAlpha;
        ofParameter<float>  paramFeedMix;
        ofParameter<float>  paramFeedDispX;
        ofParameter<float>  paramFeedDispY;
        ofParameter<float>  paramFeedBrightness;
        ofParameter<float>  paramFeedContrast;
        ofParameter<ofFloatColor>  paramFeedHsv;
        ofxButton  paramFeedReset;
        ofxToggle  paramDrawPart;
        ofxToggle  paramDrawClear;

		ofxPanel myGui;

		ofEasyCam myCamera;

        //shaders
        ofShader feedHsvShader;
        ofShader feedbackShader;
        //Feedback FBO
        ofFbo buffer0;
        ofFbo buffer1;
};
