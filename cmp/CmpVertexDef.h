#ifndef CMP_VERTEX_DEF_H
#define CMP_VERTEX_DEF_H

#include "Common.h"

namespace cmp {

    struct VtxDebug {
        glm::vec3 attr_location;
        glm::vec3 attr_color;
    };

    struct VtxSimple {
        glm::vec3 attr_location;
        glm::vec3 attr_normal;
        glm::vec2 attr_tex_coord;
    };

}

#endif
