#ifndef CHUNK_H
#define CHUNK_H

#include "Block.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtx/compatibility.hpp>
#include "shaderClass.h"
#include "TerrainGenerator.h"

const unsigned int CHUNK_SIZE = 32;
const unsigned int MAX_HEIGHT = 16;

class Chunk {
public:
    std::vector<Block> blocks;
    glm::vec3 position;

    VAO vao;
    VBO vbo;
    EBO ebo;

    Chunk(glm::vec3 pos, TerrainGenerator& terrainGen);
    ~Chunk();
    void generateTerrain(TerrainGenerator& terrainGen);
    void render(Shader& shaderProgram);

private:
    std::vector<bool> visibleFaces; 
    bool needsUpdate; 
};

#endif // CHUNK_H
