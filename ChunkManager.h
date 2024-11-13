#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "Chunk.h"
#include "TerrainGenerator.h"
#include <vector>

class ChunkManager {
public:
    std::vector<Chunk> chunks;

    ChunkManager(TerrainGenerator& terrainGen);
    void initializeChunks(TerrainGenerator& terrainGen);
    void renderChunks(Shader& shaderProgram); 
};

#endif // CHUNKMANAGER_H
