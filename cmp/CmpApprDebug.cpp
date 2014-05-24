#include <stddef.h>

#include "CmpApprDebug.h"

namespace cmp {

void CmpApprDebug::m_PrepareBuffers(
        std::vector<VtxDebug> vertexes,
        std::vector<unsigned> indexes)
{
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    /*
    glBufferStorage(
        GL_ARRAY_BUFFER,
        sizeof(VtxDebug) * vertexes.size(),
        &vertexes[0],
        0);
        */
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    /*
    glBufferStorage(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned) * indexes.size(),
        &indexes[0],
        0);
        */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CmpApprDebug::m_PrepareArrayObject(GLint location_loc, GLint color_loc)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glVertexAttribPointer(location_loc, 3, GL_FLOAT, GL_FALSE, sizeof(VtxDebug),
            reinterpret_cast<void*>(offsetof(VtxDebug, attr_location)));

    glVertexAttribPointer(color_loc, 3, GL_FLOAT, GL_FALSE, sizeof(VtxDebug),
            reinterpret_cast<void*>(offsetof(VtxDebug, attr_color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

CmpApprDebug::CmpApprDebug(
        std::vector<VtxDebug> vertexes,
        std::vector<unsigned> indexes,
        GLint location_loc, GLint color_loc)
{
    m_PrepareBuffers(vertexes, indexes);
    m_PrepareArrayObject(location_loc, color_loc);
}

CmpApprDebug::~CmpApprDebug()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_ibo);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_vbo);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vao);
}

}
