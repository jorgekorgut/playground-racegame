#pragma once
#include <glm/vec2.hpp>

class Noise {
public:
	static float PerlinOctave(float x, float y, float initialFrequency = 1, float initialAmplitude = 1);
	static float Perlin(float x, float y);
	
private:
	static glm::vec2 RandomGradient(int ix, int iy);
	static float DotGridGradient(int ix, int iy, float x, float y);
	static float Interpolate(float a0, float a1, float w);
};