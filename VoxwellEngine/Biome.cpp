//
// Created by Griffin Dunaif on 3/17/21.
//

#include "Biome.h"

Biome::Biome(glm::ivec3 location, glm::ivec3 chunk_dim, glm::ivec2 biome_dim)
: _location(location), _chunk_dim(chunk_dim), _biome_dim(biome_dim), _world_space_mapping(nullptr),
_biome_space_mapping(nullptr)
{
    int biome_width = biome_dim.x;
    int biome_depth = biome_dim.y;

    _chunks.resize(biome_width * biome_depth);

    for (int x = 0; x < biome_width; ++x) {
        for (int y = 0; y < biome_depth; ++y) {
            int index = chunk_index(x, y);
            unique_ptr<Chunk> c = make_unique<Chunk>(
                    world_units_to_world_space(glm::ivec2(x, y)),
                    chunk_dim.x, chunk_dim.y, chunk_dim.z);
            _chunks[index] = move(c);
        }
    }
}

void Biome::populate() {
    if (!_world_space_mapping) {
        return;
    }

    int biome_width = _biome_dim.x;
    int biome_depth = _biome_dim.y;
    for (int x = 0; x < biome_width; ++x) {
        for (int y = 0; y < biome_depth; ++y) {
            int index = chunk_index(x, y);
            unique_ptr<Chunk>& c = _chunks[index];

            c->set_world_space_mapping(_world_space_mapping);
            c->populate();
        }
    }
}

void Biome::render(VoxwellEngine &engine) {
    int biome_width = _biome_dim.x;
    int biome_depth = _biome_dim.y;
    for (int x = 0; x < biome_width; ++x) {
        for (int y = 0; y < biome_depth; ++y) {
            int index = chunk_index(x, y);
            unique_ptr<Chunk> &c = _chunks[index];
            c->render(engine);
        }
    }
}

void Biome::set_world_space_mapping(bool (*func)(glm::ivec3)) {
    _world_space_mapping = func;
}

glm::vec3 Biome::world_units_to_world_space(glm::ivec2 world_units) {
    return _location + glm::ivec3(world_units.x * _chunk_dim.x, 0, world_units.y * _chunk_dim.z);
}


int Biome::chunk_index(int x, int y) {
    return x + _biome_dim.x * y;
}