#include "ChunkManager.h"

ChunkManager::ChunkManager(TerrainGenerator& terrainGen){
    initializeChunks(terrainGen);
}

void ChunkManager::initializeChunks(TerrainGenerator& terrainGen) {
    // Adjust the range here based on desired chunk grid dimensions
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 1; ++y) {
            for (int z = 0; z < 3; ++z) {
                glm::vec3 pos(x * CHUNK_SIZE, y * MAX_HEIGHT, z * CHUNK_SIZE);
                chunks.emplace_back(pos, terrainGen);  // Initialize each Chunk with TerrainGenerator
            }
        }
    }
}

void ChunkManager::renderChunks(Shader& shaderProgram) {
    for (Chunk& chunk : chunks) {
        chunk.render(shaderProgram);
    }
}

