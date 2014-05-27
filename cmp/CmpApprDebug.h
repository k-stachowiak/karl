#ifndef CMP_APPR_DEBUG_H
#define CMP_APPR_DEBUG_H

#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#include "Common.h"

namespace cmp {

class CmpApprDebug {
public:
    struct Vertex {
        glm::vec3 attr_location;
        glm::vec3 attr_color;
    };

private:
    void m_PrepareBuffers(
        const std::vector<Vertex>& vertexes,
        const std::vector<unsigned>& indexes);

    void m_PrepareArrayObject(GLint location_loc, GLint color_loc);

public:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;
    unsigned m_num_primitives;

    CmpApprDebug(
        const std::vector<Vertex>& vertexes,
        const std::vector<unsigned>& indexes,
        GLint location_loc, GLint color_loc);
    ~CmpApprDebug();
};

}

#endif
