#include "Chunk.h"
#include "ChunkManager.h"
#include <glm/gtc/noise.hpp>
#include <glm/gtc/type_ptr.hpp>

GLfloat vertices[] = {
    // Coordinates          // Colors         // Texture Coords
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,  0.0f, 1.0f
};

GLuint indices[] = {
    0, 1, 2, 0, 2, 3, // Back face
    4, 5, 6, 4, 6, 7, // Front face
    0, 3, 7, 0, 7, 4, // Left face
    1, 5, 6, 1, 6, 2, // Right face
    0, 1, 5, 0, 5, 4, // Bottom face
    3, 2, 6, 3, 6, 7  // Top face
};

glm::vec3 getColorByBlockType(BlockType type) {
    switch (type) {
    case GRASS: return glm::vec3(0.0f, 1.0f, 0.0f);
    case DIRT: return glm::vec3(0.545f, 0.271f, 0.075f);
    case STONE: return glm::vec3(0.5f, 0.5f, 0.5f);
    default: return glm::vec3(1.0f, 1.0f, 1.0f);
    }
}

Chunk::Chunk(glm::vec3 pos, TerrainGenerator& terrainGen) : position(pos), vbo(vertices, sizeof(vertices)), ebo(indices, sizeof(indices)) {
    generateTerrain(terrainGen);

    // Setup VAO, VBO, and EBO for this chunk
    vao.Bind();
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}



Chunk::~Chunk() {
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}

void Chunk::generateTerrain(TerrainGenerator& terrainGen) {
    int estimatedSize = CHUNK_SIZE * CHUNK_SIZE * MAX_HEIGHT;
    blocks.reserve(estimatedSize);

    // Generate terrain using the TerrainGenerator for height data
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            int height = terrainGen.GetHeight(glm::vec2(position.x + x, position.z + z));

            for (int y = 0; y < MAX_HEIGHT; ++y) {
                BlockType type;
                if (y < height - 2) type = STONE;
                else if (y < height - 1) type = DIRT;
                else if (y < height) type = GRASS;
                else type = AIR;

                if (type != AIR) {
                    blocks.emplace_back(type, glm::vec3(x, y, z) + position);
                }
            }
        }
    }
}

void Chunk::render(Shader& shaderProgram) {
    vao.Bind();
    ebo.Bind();

    for (const Block& block : blocks) {
        if (block.type == AIR) continue;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), block.position);
        shaderProgram.setMat4("model", model);
        shaderProgram.setVec3("color", getColorByBlockType(block.type));

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    }
    vao.Unbind();

}
