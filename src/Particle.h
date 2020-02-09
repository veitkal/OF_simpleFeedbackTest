#pragma once

#include "ofMain.h"

using namespace glm;

class Particle {
public:
	void setup(vec3 initPos);
	void update(float amplitude, float frequency, float scale);
	void draw();
	vec3 getPos();

private:
	vec3 myPos;
	vec3 myVel;
	float mySize;
};
