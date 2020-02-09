#pragma once

#include "ofApp.h"

//--------------------------------------------------------------
float remapNoise(float x, float min, float max) {
	return ofMap(ofNoise(x), 0.2, 0.8, min, max);
}

//--------------------------------------------------------------
float remapNoise(float x) {
	return remapNoise(x, 0.0, 1.0);
}

//--------------------------------------------------------------
float noiseWithOctaves(float x, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofNoise(freq * x);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result;
}

//--------------------------------------------------------------
float noiseWithOctaves(vec2 p, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofNoise(p);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result + 0.5;
}
//--------------------------------------------------------------
float noiseWithOctaves(vec3 p, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofNoise(p);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result + 0.5;
}
//--------------------------------------------------------------
float noiseWithOctaves(vec4 p, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofNoise(p);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result + 0.5;
}

//--------------------------------------------------------------
float noiseWithOctavesRemapped(float x, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofMap(ofNoise(freq * x), 0.2, 0.8, -0.2, 0.2);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result + 0.5;
}

//--------------------------------------------------------------
float noiseWithOctavesRemapped(vec2 p, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofMap(ofNoise(freq * p), 0.2, 0.8, -0.2, 0.2);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result + 0.5;
}

//--------------------------------------------------------------
float noiseWithOctavesRemapped(vec3 p, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofMap(ofNoise(freq * p), 0.2, 0.8, -0.2, 0.2);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result + 0.5;
}

//--------------------------------------------------------------
float noiseWithOctavesRemapped(vec4 p, int numOctaves) {
	float result = 0.0;

	float freq = 1.0;
	float amp = 1.0;
	for (int i = 0; i < numOctaves; i++) {
		result += amp * ofMap(ofNoise(freq * p), 0.2, 0.8, -0.2, 0.2);
		freq *= 2.0;
		amp *= 0.5;
	}

	return result + 0.5;
}

//--------------------------------------------------------------
float fourier(float x, int numHarmonics) {
	float result = 0.0;
	for (int i = 0; i < numHarmonics; i++) {
		int n = 2 * i + 1;
		//int n = i + 1;
		result += (1.0f / n) * sinf(x * n);
	}

	return result;
}

//--------------------------------------------------------------
float bias(float x, float b)
{
	return x / (((1.0 / b - 2.0)*(1.0 - x)) + 1.0);
}

//--------------------------------------------------------------
float gain(float x, float g)
{
	if (x < 0.5)
		return bias(x * 2.0, g) / 2.0;
	else
		return bias(x * 2.0 - 1.0, 1.0 - g) / 2.0 + 0.5;
}
