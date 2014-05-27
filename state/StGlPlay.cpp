#include "Config.h"
#include "StGlPlay.h"

namespace {

    struct vertex {
        glm::vec3 coords;
        glm::vec3 color;
    };

    vertex vertexes[] {
        { { -1, -1, 0 }, { 1, 0, 0 } },
        { { -1, +1, 0 }, { 0, 1, 0 } },
        { { +1, +1, 0 }, { 0, 0, 1 } },
        { { +1, -1, 0 }, { 1, 1, 0 } }
    };

    unsigned int indexes[] = {
        0, 1, 2,
        0, 2, 3
    };

    glm::mat4 identity;
    glm::mat4 projection;

    GLuint vao;
    GLuint vbo;
    GLuint ibo;

    GLint vloc;
    GLint cloc;

    GLint modloc, viewloc, projloc;
}

namespace state {

StGlPlay::StGlPlay(res::Resources& resources) :
    m_done { false },
    m_resources { resources }
{
    projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);

    glUseProgram(m_resources.res_debug_shader->program);
    vloc = m_resources.res_debug_shader->coord_loc;
    cloc = m_resources.res_debug_shader->color_loc;
    modloc = m_resources.res_debug_shader->model_loc;
    viewloc = m_resources.res_debug_shader->view_loc;
    projloc = m_resources.res_debug_shader->projection_loc;

    glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(identity));
    glUniformMatrix4fv(modloc, 1, GL_FALSE, glm::value_ptr(identity));
    glUniformMatrix4fv(projloc, 1, GL_FALSE, glm::value_ptr(projection));

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(vloc);
    glEnableVertexAttribArray(cloc);
    glVertexAttribPointer(vloc, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glVertexAttribPointer(cloc, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)sizeof(glm::vec3));

    glBindVertexArray(0);

    glViewport(0, 0, cfg_screen_w, cfg_screen_h);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

StTransition StGlPlay::Tick(double)
{
    return m_done
        ? StTransition { StTransition::State::END }
        : StTransition { StTransition::State::THIS_STATE };
}

void StGlPlay::Draw(double)
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void StGlPlay::KeyUp(int key)
{
    if (key == ALLEGRO_KEY_ESCAPE) {
        m_done = true;
    }
}

bool StGlPlay::MouseMove(int dx, int dy)
{
    return false; // Don't reset mouse.
}

}
