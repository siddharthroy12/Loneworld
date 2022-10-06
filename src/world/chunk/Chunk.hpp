#ifndef CHUNK
#define CHUNK

#include <string>
#include "../../../libs/raylib/src/raylib.h"
#include "../../../libs/raylib/src/raymath.h"

#define CHUNK_SIZE_XZ 16
#define CHUNK_SIZE_Y 384

#define CHUNK_MESH_SIZE 16

struct ChunkPosition {
    ChunkPosition(int x, int z);
    int x;
    int z;
    std::string stringify();
};

class Chunk {
    public:
    Chunk(int seed, ChunkPosition position);
    void draw();
    ~Chunk();
    ChunkPosition position = ChunkPosition(0, 0);
    void updateMesh();
    bool needsToUpdateMesh = false;
    bool meshHasGenerated = false;
    BoundingBox getBoundingbox();
    private:
    int data[CHUNK_SIZE_XZ][CHUNK_SIZE_Y][CHUNK_SIZE_XZ];
    Model model;
};
#endif
