#include "Noise.h"
#include "SimplexNoise.h"
#include "../environment/terrain/chunks/ChunkGenerator.h"

Noise::Noise(int octaves, int amplitude, int smoothness, long seed) : octaves(octaves), amplitude(amplitude),
                                                                      smoothness(smoothness), seed(seed) {}

float Noise::getNoise(float x, float z) const {
    return (SimplexNoise::noise((x + (float)seed) / (float)smoothness, (z + (float)seed) / (float)smoothness)) * (float)amplitude;
}

float Noise::get(int x, int z) {
    return get(float(x), (float)z);
}

float Noise::get(float x, float z) {
    float height = 0.0f;
    float nx = x / CHUNK_SIZE;
    float nz = z / CHUNK_SIZE;
    for (int i = 0; i < octaves; i++) {
        height += getNoise(nx * ((float)i + 1), nz * ((float)i + 1)) * (1.0f / ((float)i + 1));
    }
    return height;
}

