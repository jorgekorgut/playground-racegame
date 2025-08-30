
#include "Noise.h"
#include <cmath>

float Noise::PerlinOctave(float x, float y, float initialFrequency, float initialAmplitude)
{
    float val = 0;

    for (int i = 0; i < 8; i++)
    {
        val += Perlin(x * initialFrequency, y * initialFrequency) * initialAmplitude;

        initialFrequency *= 2;
        initialAmplitude /= 2;
    }

	return val;
}

float Noise::Perlin(float x, float y)
{
    // Determine grid cell corner coordinates
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // Compute Interpolation weights
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // Compute and interpolate top two corners
    float n0 = DotGridGradient(x0, y0, x, y);
    float n1 = DotGridGradient(x1, y0, x, y);
    float ix0 = Interpolate(n0, n1, sx);

    // Compute and interpolate bottom two corners
    n0 = DotGridGradient(x0, y1, x, y);
    n1 = DotGridGradient(x1, y1, x, y);
    float ix1 = Interpolate(n0, n1, sx);

    // Final step: interpolate between the two previously interpolated values, now in y
    float value = Interpolate(ix0, ix1, sy);

    return value;
}

float Noise::DotGridGradient(int ix, int iy, float x, float y) {
    // Get gradient from integer coordinates
    glm::vec2 gradient = RandomGradient(ix, iy);

    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx * gradient.x + dy * gradient.y);
}

float Noise::Interpolate(float a0, float a1, float w)
{
    return (a1 - a0) * (3.0f - w * 2.0f) * w * w + a0;
}

glm::vec2 Noise::RandomGradient(int ix, int iy)
{
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= ((a << s) | (a >> (w - s)));
    b *= 1911520717;

    a ^= ((b << s) | (b >> (w - s)));
    a *= 2048419325;
    float random = a * (3.14159265f / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    glm::vec2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}
