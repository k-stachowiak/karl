#ifndef CMP_APPR_TANK_VEX_H
#define CMP_APPR_TANK_VEX_H

#include <vector>

#include "ResShaderTank.h"

namespace cmp {

class CmpApprTankVex {
    void m_PrepareBuffers(
        const std::vector<res::ResShaderTank::Vertex>& vertexes);

    void m_PrepareArrayObject(GLint location_loc, GLint tex_coord_loc);

public:
    GLuint m_vao;
    GLuint m_vbo;
    unsigned m_num_primitives;

    CmpApprTankVex(
        const std::vector<res::ResShaderTank::Vertex>& vertexes,
        GLint location_loc, GLint tex_coord_loc);

    ~CmpApprTankVex();
};

}

#endif
