#pragma once

#include <array>
#include <vector>

#include <glm/glm.hpp>

// Entry in cache
struct HeightCache
{
	float height; // height zero = disabled
	glm::vec2 pos;
};

// Defines method of terrain generation
class TerrainGenerator
{
public:
    int GetHeight(glm::vec2 pos);

private:
    static constexpr float noiseScale = 32.0f; // Scale for Perlin noise
    static constexpr float maxHeight = 16.0f;  // Max height for chunks

    static const unsigned cacheCapacity = 128;
    std::array<HeightCache, cacheCapacity> cache_;
    unsigned cacheSize_ = 0;

    float GetNoiseHeight(glm::vec2 pos); // Get height using simplified noise
    void AddToCache(glm::vec2 pos, float height); // Add height value to cache
    float GetFromCache(glm::vec2 pos); // Retrieve height value from cache
};