#ifndef CMP_APPR_DEBUG_H
#define CMP_APPR_DEBUG_H

#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#include "CmpVertexDef.h"

namespace cmp {

class CmpApprDebug {

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;

    void m_PrepareBuffers(
        std::vector<VtxDebug> vertexes,
        std::vector<unsigned> indexes);

    void m_PrepareArrayObject(GLint location_loc, GLint color_loc);

public:
    CmpApprDebug(
        std::vector<VtxDebug> vertexes,
        std::vector<unsigned> indexes,
        GLint location_loc, GLint color_loc);
    ~CmpApprDebug();
};

}

#endif
