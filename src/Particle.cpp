#include "Particle.h"

void Particle::setup(vec3 initPos) {
	myPos = initPos;
	myVel = vec3(0.0, 0.0, 0.0);
    mySize = 0.1;
}

void Particle::update(float amplitude, float frequency, float scale) {
	myPos.y = amplitude * ofNoise(vec2(myPos.x, myPos.z) / scale) * sin(frequency * ofGetElapsedTimef());
}

void Particle::draw() {
	ofDrawSphere(myPos, mySize);
}

vec3 Particle::getPos() {
	return myPos;
}
