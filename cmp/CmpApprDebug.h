#ifndef CMP_APPR_DEBUG_H
#define CMP_APPR_DEBUG_H

#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#include "CmpVertexDef.h"

namespace cmp {

class CmpApprDebug {

    void m_PrepareBuffers(
        const std::vector<VtxDebug>& vertexes,
        const std::vector<unsigned>& indexes);

    void m_PrepareArrayObject(GLint location_loc, GLint color_loc);

public:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;
    unsigned m_num_primitives;

    CmpApprDebug(
        const std::vector<VtxDebug>& vertexes,
        const std::vector<unsigned>& indexes,
        GLint location_loc, GLint color_loc);
    ~CmpApprDebug();
};

}

#endif
