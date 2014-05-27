#ifndef CMP_APPR_DEBUG_IND_H
#define CMP_APPR_DEBUG_IND_H

#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#include "ResShaderDebug.h"

namespace cmp {

class CmpApprDebugInd {
    void m_PrepareBuffers(
        const std::vector<res::ResShaderDebug::Vertex>& vertexes,
        const std::vector<unsigned>& indexes);

    void m_PrepareArrayObject(GLint location_loc, GLint color_loc);

public:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;
    unsigned m_num_primitives;

    CmpApprDebugInd(
        const std::vector<res::ResShaderDebug::Vertex>& vertexes,
        const std::vector<unsigned>& indexes,
        GLint location_loc, GLint color_loc);
    ~CmpApprDebugInd();
};

}

#endif
