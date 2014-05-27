#include <stddef.h>

#include "Diagnostics.h"
#include "CmpApprDebug.h"

namespace cmp {

void CmpApprDebug::m_PrepareBuffers(
        const std::vector<VtxDebug>& vertexes,
        const std::vector<unsigned>& indexes)
{
    glGenBuffers(1, &m_vbo);
    DIAG_ASSERT(m_vbo != 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(VtxDebug) * vertexes.size(),
        &vertexes[0],
        GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m_ibo);
    DIAG_ASSERT(m_ibo != 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned) * indexes.size(),
        &indexes[0],
        GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CmpApprDebug::m_PrepareArrayObject(GLint location_loc, GLint color_loc)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glEnableVertexAttribArray(location_loc);
    glEnableVertexAttribArray(color_loc);

    glVertexAttribPointer(location_loc, 3, GL_FLOAT, GL_FALSE, sizeof(VtxDebug),
            reinterpret_cast<void*>(offsetof(VtxDebug, attr_location)));

    glVertexAttribPointer(color_loc, 3, GL_FLOAT, GL_FALSE, sizeof(VtxDebug),
            reinterpret_cast<void*>(offsetof(VtxDebug, attr_color)));

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

CmpApprDebug::CmpApprDebug(
        const std::vector<VtxDebug>& vertexes,
        const std::vector<unsigned>& indexes,
        GLint location_loc, GLint color_loc) :
    m_num_primitives { indexes.size() }
{
    DIAG_MESSAGE("loading %d vertexes and %d indexes.\n", vertexes.size(), indexes.size());
    DIAG_MESSAGE("location_loc: %d, color_loc: %d.\n", location_loc, color_loc);
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
