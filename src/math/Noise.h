#pragma once

class Noise {

private:
    int octaves;
    int amplitude;
    int smoothness;
    long seed;

    [[nodiscard]] float getNoise(float x, float z) const;


public:
    explicit Noise(int octaves = 1, int amplitude = 1, int smoothness = 1, long seed = 0);

    float get(int x, int z);
    float get(float x, float z);

};