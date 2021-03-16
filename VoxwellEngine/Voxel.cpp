//
// Created by Griffin Dunaif on 3/10/21.
//

#include "Voxel.h"

Voxel::Voxel() {
}

Voxel::Voxel(long x, long y, long z) :
_x(x), _y(y), _z(z), _visible(true)
{
}

void Voxel::set_visibility(bool is_visible) {
    _visible = is_visible;
}

bool Voxel::is_visible() {
    return _visible;
}

size_t Voxel::render(VoxwellEngine& engine) {
    if (_visible) {
        cube c;
        c.translate(glm::vec3(_x, _y, _z));
        size_t id = engine.create_render_object(c.getVerts(), c.getIndices());
        RenderObject &obj = engine.get_render_object(id);
        obj.setModelMatrix(c.getTranslation());
        return id;
    }

    // TODO make optional
    return 0;
}
