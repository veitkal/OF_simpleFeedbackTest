#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Set background colour to black
	ofBackground(0);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);

	// Setup particle system
	myParticleSystem.setup();

	// Setup EasyCam
	myCamera.setAutoDistance(false);
	myCamera.setPosition(vec3(0.0, 10.0, -100.0));
	myCamera.setTarget(vec3(0.0, 0.0, 0.0));

	// Setup GUI
	myGui.setup();
	myGui.add(myFpsLabel.setup("FPS", ofToString(ofGetFrameRate(), 2)));
    myGui.add(paramDrawPart.setup("Draw Particles", true));
    myGui.add(paramAmplitude.set("Amplitude", 5.0, 0.0, 20.0));
	myGui.add(paramFrequency.set("Frequency", 2.0, 0.0, 10.0));
	myGui.add(paramScale.set("Scale", 10.0, 0.0, 50.0));


    myGui.add(feedLabel.setup("Feedback ctrl", ""));
    myGui.add(paramDrawClear.setup("Clear Auto", true));
    myGui.add(paramFeedMixToggle.setup("Toggle mix mode", true));
    myGui.add(paramFeedReset.setup("feedReset"));
    myGui.add(paramFeedMix.set("feedMix", 1., -5., 10.));
    myGui.add(paramFeedAlpha.set("feedAlpha", 1., 0., 1.));
    myGui.add(paramFeedDispX.set("feedDispX", 1., -5., 5.));
    myGui.add(paramFeedDispY.set("feedDispY", 1., -5., 5.));
    myGui.add(paramFeedBrightness.set("feedBrightness", 0., -1., 1.));
    myGui.add(paramFeedContrast.set("feedContrast", 1., 0., 10.));
    myGui.add(paramFeedHsv.set("Feedback Color", ofFloatColor(1.0, 0.5, 1.0)));

    //loading shaders
    feedbackShader.load("shadersGL2/feedback");
//    feedHsvShader.load("shadersGL2/hsvShader");

    //setup allocate and clear Fbo
    buffer0.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    buffer1.allocate(ofGetWindowWidth(), ofGetWindowHeight());

    buffer0.begin();
    ofClear(0,0,0,255);
    buffer0.end();

    buffer1.begin();
    ofClear(0,0,0,255);
    buffer1.end();
}

//--------------------------------------------------------------
void ofApp::update(){
	// Update the particles
	myParticleSystem.update(paramAmplitude, paramFrequency, paramScale);

	// Update the frames per second label in the GUI
	myFpsLabel = ofToString(ofGetFrameRate(), 2);

	// Disable mouse input for the camera if the mouse is over the GUI panel
	if (myGui.getShape().inside(ofGetMouseX(), ofGetMouseY())) {
		myCamera.disableMouseInput();
	}
	else {
		myCamera.enableMouseInput();
	}

    //resetting feedback
    if(paramFeedReset) {
    buffer0.begin();
    ofClear(0,0,0,255);
    buffer0.end();

    buffer1.begin();
    ofClear(0,0,0,255);
    buffer1.end();
    }

    if(paramFeedAlpha == 0) {
    buffer0.begin();
    ofClear(0,0,0,255);
    buffer0.end();

    buffer1.begin();
    ofClear(0,0,0,255);
    buffer1.end();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    buffer0.begin();
    ofClear(0,0,0,255);
    buffer0.end();


    //starting drawing buffer
    buffer0.begin();

    //start the shader
    feedbackShader.begin();

    //drawing feedback buffer
    buffer1.draw(0,0);

    //feedback uniforms: mixer, alpha, displace
    feedbackShader.setUniform1f("uFeedMix",paramFeedMix);
    feedbackShader.setUniform1f("uFeedAlpha",paramFeedAlpha);
    feedbackShader.setUniform4f("uFeedHsv",paramFeedHsv);
    feedbackShader.setUniform1f("uFeedBrightness",paramFeedBrightness);
    feedbackShader.setUniform1f("uFeedContrast",paramFeedContrast);
    feedbackShader.setUniform1i("uFeedMixToggle",paramFeedMixToggle);

    vec2 feedDisp = vec2(paramFeedDispX,paramFeedDispY);
    //ofVec2 feedDis;
    //feedDisp.set(paramFeedDispX,paramFeedDispY);
    feedbackShader.setUniform2f("uFeedDisp",feedDisp);

    //end of the shadr
    feedbackShader.end();


    // Draw the particles or anything else
	myCamera.begin();
    if(paramDrawPart) {
    myParticleSystem.draw();
    }
	myCamera.end();

    //ending drawing buffer
    buffer0.end();

    //displaying drawing buffer
    buffer0.draw(0,0);


    //drawing first buffer to second to get feedback
    buffer1.begin();
    buffer0.draw(0,0);
    buffer1.end();

	// Draw the GUI elements
	myGui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
