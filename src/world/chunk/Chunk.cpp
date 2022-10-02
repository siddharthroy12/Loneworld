#include "Chunk.hpp"
#include <string>

ChunkPosition::ChunkPosition(int x, int z) {
    this->x = x;
    this->z = z;
}

std::string ChunkPosition::stringify() {
    return std::to_string(this->x) + std::string("-") + std::to_string(this->z);
}

Chunk::Chunk(int seed, ChunkPosition position) {
    this->position = position;
}

void Chunk::draw() {
    DrawBoundingBox(this->getBoundingbox(), GREEN);
}

BoundingBox Chunk::getBoundingbox() {
    BoundingBox boundingBox;
    boundingBox.min = {(float)this->position.x * CHUNK_SIZE_XZ, 0.0f, (float)this->position.z * CHUNK_SIZE_XZ};
    boundingBox.max = boundingBox.min;
    boundingBox.max.x += CHUNK_SIZE_XZ;
    boundingBox.max.y += CHUNK_SIZE_Y;
    boundingBox.max.z += CHUNK_SIZE_XZ;

    return boundingBox;
}

Chunk::~Chunk() {
}
