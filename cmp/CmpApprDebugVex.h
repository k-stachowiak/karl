#ifndef CMP_APPR_DEBUG_VEX_H
#define CMP_APPR_DEBUG_VEX_H

#include <vector>

#include "ResShaderDebug.h"

namespace cmp {

class CmpApprDebugVex {
    void m_PrepareBuffers(
        const std::vector<res::ResShaderDebug::Vertex>& vertexes);

    void m_PrepareArrayObject(GLint location_loc, GLint color_loc);

public:
    GLuint m_vao;
    GLuint m_vbo;
    unsigned m_num_primitives;

    CmpApprDebugVex(
        const std::vector<res::ResShaderDebug::Vertex>& vertexes,
        GLint location_loc, GLint color_loc);

    ~CmpApprDebugVex();
};

}

#endif
