#pragma once

#include "ofMain.h"
#include "Particle.h"

using namespace glm;

class ParticleSystem {
public:
	void setup();
	void update(float amplitude, float frequency, float scale);
	void draw();

private:
	vector<Particle> myParticles;
	ofMesh myMesh;
};
