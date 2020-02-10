#include "ParticleSystem.h"

//--------------------------------------------------------------
void ParticleSystem::setup() {
	int gridSizeX = 100;
	int gridSizeY = 100;

	// Initialize the particles
	for (int i=0; i<gridSizeX; i++)
		for (int j = 0; j < gridSizeY; j++) {
			vec3 pos = vec3(i - 0.5 * gridSizeX, 0.0, j - 0.5 * gridSizeY);
			Particle par;
			par.setup(pos);
			myParticles.push_back(par);
		}

	// Initialize the mesh
//  myMesh.setMode(OF_PRIMITIVE_LINES);
    //myMesh.setMode(OF_PRIMITIVE_POINTS);
    myMesh.setMode(OF_PRIMITIVE_TRIANGLES);

	// Create a vertex for each particle
	for (int i = 0; i < myParticles.size(); i++) {
		vec3 pos = myParticles[i].getPos();
		myMesh.addVertex(pos);
	}

	// Declare lines connecting the vertices in a square grid using the vertex indices
	// We add lines by creating a list of pairs of vertex indices that should be
	// connected by lines
	for (int i = 0; i < gridSizeX; i++)
		for (int j = 0; j < gridSizeY; j++) {
			int idx = j + gridSizeY * i;

			if (i < gridSizeX - 1) {
				myMesh.addIndex(idx);
				myMesh.addIndex(idx + gridSizeY);
			}

			if (j < gridSizeY - 1) {
				myMesh.addIndex(idx);
				myMesh.addIndex(idx + 1);
			}
		}

    for (int i = 0; i < gridSizeX; i++) {
        for (int j = 0; j < gridSizeY; j++) {
            int idx = j + gridSizeY * i;

            if (i < gridSizeX - 1 && j < gridSizeX - 1) {
                myMesh.addTriangle(idx, idx + 1, idx + gridSizeY);
                myMesh.addTriangle(idx + 1, idx + gridSizeY, idx + gridSizeY + 1);
            }

        }
    }
}

//--------------------------------------------------------------
void ParticleSystem::update(float amplitude, float frequency, float scale) {
	for (int i = 0; i < myParticles.size(); i++) {
		myParticles[i].update(amplitude, frequency, scale);
		myMesh.setVertex(i, myParticles[i].getPos());
	}
}

//--------------------------------------------------------------
void ParticleSystem::draw() {
    ofSetColor(255,255,255);
    myMesh.draw();
}
