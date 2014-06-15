#include "CmpApprDebug.h"

namespace cmp {

void CmpApprDebug::m_PrepareBuffers(
    const std::vector<res::ResShaderDebug::Vertex>& vertexes)
{
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(res::ResShaderDebug::Vertex) * vertexes.size(),
        &vertexes[0],
        GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CmpApprDebug::m_PrepareArrayObject(
    GLint location_loc, GLint color_loc)
{
    glGenVertexArrays(1, &m_vao);
    DIAG_ASSERT(m_vao != 0);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(location_loc);
    glEnableVertexAttribArray(color_loc);

    glVertexAttribPointer(
        location_loc, 3, GL_FLOAT, GL_FALSE,
        sizeof(res::ResShaderDebug::Vertex),
        reinterpret_cast<void*>(
            offsetof(res::ResShaderDebug::Vertex, attr_location)));

    glVertexAttribPointer(
        color_loc, 3, GL_FLOAT, GL_FALSE,
        sizeof(res::ResShaderDebug::Vertex),
        reinterpret_cast<void*>(
            offsetof(res::ResShaderDebug::Vertex, attr_color)));

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

CmpApprDebug::CmpApprDebug(
        const std::vector<res::ResShaderDebug::Vertex>& vertexes,
        GLint location_loc, GLint color_loc) :
    m_num_primitives { vertexes.size() }
{
    m_PrepareBuffers(vertexes);
    m_PrepareArrayObject(location_loc, color_loc);
}

CmpApprDebug::~CmpApprDebug()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_vbo);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vao);
}

}
