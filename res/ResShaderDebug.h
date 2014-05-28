#ifndef RES_SHADER_DEBUG_H
#define RES_SHADER_DEBUG_H

#include "Common.h"
#include "ResShader.h"

namespace res {

class ResShaderDebug : public ResShader {
public:
    struct Vertex {
        glm::vec3 attr_location;
        glm::vec3 attr_color;
    };

    GLint coord_loc;
    GLint color_loc;
    ResShaderDebug();

    void Begin() const;
    void End() const;
};

}

#endif
