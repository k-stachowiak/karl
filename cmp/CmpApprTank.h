#ifndef CMP_APPR_TANK_H
#define CMP_APPR_TANK_H

#include <vector>

#include "ResShaderTank.h"

namespace cmp {

class CmpApprTank {
    void m_PrepareBuffers(
        const std::vector<res::ResShaderTank::Vertex>& vertexes);

    void m_PrepareArrayObject(GLint location_loc, GLint tex_coord_loc);

public:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_tid;
    unsigned m_num_primitives;

    CmpApprTank(
        const std::vector<res::ResShaderTank::Vertex>& vertexes,
        GLint location_loc, GLint tex_coord_loc,
        GLuint texture_id);

    ~CmpApprTank();
};

}

#endif
