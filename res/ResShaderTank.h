#ifndef RES_SHADER_TANK_H
#define RES_SHADER_TANK_H

#include "Common.h"
#include "ResShader.h"

namespace res {

class ResShaderTank : public ResShader {
public:
    struct Vertex {
        glm::vec3 attr_location;
        glm::vec2 attr_tex_coord;
        // TODO: Add tank part identifier here.
    };

    GLint coord_loc;
    GLint tex_coord_loc;
    GLint texture_loc;

    ResShaderTank();

    void Begin() const;
    void End() const;
};

}

#endif
