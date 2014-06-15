#ifndef CMP_APPR_DEBUG_H
#define CMP_APPR_DEBUG_H

#include <vector>

#include "ResShaderDebug.h"

namespace cmp {

class CmpApprDebug {
    void m_PrepareBuffers(
        const std::vector<res::ResShaderDebug::Vertex>& vertexes);

    void m_PrepareArrayObject(GLint location_loc, GLint color_loc);

public:
    GLuint m_vao;
    GLuint m_vbo;
    unsigned m_num_primitives;

    CmpApprDebug(
        const std::vector<res::ResShaderDebug::Vertex>& vertexes,
        GLint location_loc, GLint color_loc);

    ~CmpApprDebug();
};

}

#endif
