#include "CmpApprTank.h"

namespace cmp {

void CmpApprTank::m_PrepareBuffers(
    const std::vector<res::ResShaderTank::Vertex>& vertexes)
{
    glGenBuffers(1, &m_vbo);
    DIAG_ASSERT(m_vbo != 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(res::ResShaderTank::Vertex) * vertexes.size(),
        &vertexes[0],
        GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CmpApprTank::m_PrepareArrayObject(
    GLint location_loc,
    GLint tex_coord_loc)
{
    glGenVertexArrays(1, &m_vao);
    DIAG_ASSERT(m_vao != 0);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(location_loc);
    glEnableVertexAttribArray(tex_coord_loc);

    glVertexAttribPointer(
        location_loc, 3, GL_FLOAT, GL_FALSE,
        sizeof(res::ResShaderTank::Vertex),
        reinterpret_cast<void*>(
            offsetof(res::ResShaderTank::Vertex, attr_location)));

    glVertexAttribPointer(
        tex_coord_loc, 2, GL_FLOAT, GL_FALSE,
        sizeof(res::ResShaderTank::Vertex),
        reinterpret_cast<void*>(
            offsetof(res::ResShaderTank::Vertex, attr_tex_coord)));

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

CmpApprTank::CmpApprTank(
        const std::vector<res::ResShaderTank::Vertex>& vertexes,
        GLint location_loc, GLint tex_coord_loc,
        GLuint texture_id) :
    m_tid { texture_id },
    m_num_primitives { vertexes.size() }
{
    m_PrepareBuffers(vertexes);
    m_PrepareArrayObject(location_loc, tex_coord_loc);
}

CmpApprTank::~CmpApprTank()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_vbo);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vao);
}

}
