#include "TerrainGenerator.h"

#include <glm/gtc/noise.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/hash.hpp>

#include <random>

int TerrainGenerator::GetHeight(glm::vec2 pos)
{
	// Get noise height directly, no interpolation needed
	return static_cast<int>(GetNoiseHeight(pos));
}


float TerrainGenerator::GetNoiseHeight(glm::vec2 pos)
{
	// Check cache
	float cache = GetFromCache(pos);
	if (cache > 0.0f)
		return cache;

	// Calculate height based on basic Perlin noise
	float height = (glm::perlin(pos / noiseScale) + 1.0f) / 2.0f * maxHeight;

	// Add to cache and return
	AddToCache(pos, height);
	return height;
}

void TerrainGenerator::AddToCache(glm::vec2 pos, float height)
{
	if (cacheSize_ >= cacheCapacity)
		cacheSize_ = 0; // Reset cache

	// Add to cache
	cache_[cacheSize_] = { height, pos };
	cacheSize_++;
}

float TerrainGenerator::GetFromCache(glm::vec2 pos)
{
	// Search from end
	for (int i = cacheSize_ - 1; i >= 0; i--)
	{
		if (cache_[i].pos == pos)
			return cache_[i].height;
	}
	return 0.0f;
}
