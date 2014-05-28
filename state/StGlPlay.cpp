#include "Config.h"
#include "StGlPlay.h"
#include "ResShaderTank.h"
#include "ResTexture.h"

namespace {

    struct vertex {
        glm::vec3 coords;
        glm::vec2 tcoord;
    };

    vertex vertexes[] {
        { { -1, -1, 0 }, { 0, 0 } },
        { { -1, +1, 0 }, { 0, 1 } },
        { { +1, +1, 0 }, { 1, 1 } },

        { { -1, -1, 0 }, { 0, 0 } },
        { { +1, +1, 0 }, { 1, 1 } },
        { { +1, -1, 0 }, { 1, 0 } }
    };

    glm::mat4 identity;
    glm::mat4 projection;

    GLuint vao;
    GLuint vbo;

    GLint vloc;
    GLint tcloc;

    GLint modloc, viewloc, projloc, texloc;
}

namespace state {

StGlPlay::StGlPlay(res::Resources& resources) :
    m_done { false },
    m_resources { resources },
    m_texture { "data/tank.png" }
{
    projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);

    glUseProgram(m_resources.res_tank_shader->program);
    vloc = m_resources.res_tank_shader->coord_loc;
    tcloc = m_resources.res_tank_shader->tex_coord_loc;
    texloc = m_resources.res_tank_shader->texture_loc;
    modloc = m_resources.res_tank_shader->model_loc;
    viewloc = m_resources.res_tank_shader->view_loc;
    projloc = m_resources.res_tank_shader->projection_loc;

    glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(identity));
    glUniformMatrix4fv(modloc, 1, GL_FALSE, glm::value_ptr(identity));
    glUniformMatrix4fv(projloc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(texloc, GL_TEXTURE0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture.GetGlId());

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(vloc);
    glEnableVertexAttribArray(tcloc);
    glVertexAttribPointer(vloc, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glVertexAttribPointer(tcloc, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)sizeof(glm::vec3));

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
    glDrawArrays(GL_TRIANGLES, 0, 6);
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
