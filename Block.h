#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>

enum BlockType {
    AIR,
    GRASS,
    DIRT,
    STONE
};

class Block {
public:
    BlockType type;
    glm::vec3 position;

    Block(BlockType t, glm::vec3 pos)
        : type(t), position(pos) {}

    bool isVisible() const {
        return type != AIR;
    }
};

#endif // BLOCK_H