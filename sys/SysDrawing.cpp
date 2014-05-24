#include <cstdio>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#include "Common.h"
#include "Diagnostics.h"
#include "Config.h"
#include "SysDrawing.h"
#include "Resources.h"

/* Camera management.
 * ==================
 */

namespace sys {

void Drawing::m_CameraApply(const res::ResShader &shader, FLOATING weight)
{
    DIAG_ASSERT(m_camera != nullptr);

    m_camera->Update(weight);

    glUniformMatrix4fv(
        shader.view_loc, 1, GL_FALSE,
        glm::value_ptr(m_camera->GetViewMatrix()));

    glUniformMatrix4fv(
        shader.projection_loc, 1, GL_FALSE,
        glm::value_ptr(m_camera->GetProjectionMatrix()));
}

void Drawing::m_ShaderBegin(const res::ResShaderDebug &shader)
{
    glUseProgram(shader.program);
    glEnableVertexAttribArray(shader.coord_loc);
    glEnableVertexAttribArray(shader.color_loc);
}

void Drawing::m_ShaderEnd(const res::ResShaderDebug &shader)
{
    glDisableVertexAttribArray(shader.coord_loc);
    glDisableVertexAttribArray(shader.color_loc);
    glUseProgram(0);
}

void Drawing::m_FrameBegin()
{
    glViewport(0, 0, cfg_screen_w, cfg_screen_h);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Drawing::m_FrameEnd()
{
}

void Drawing::m_ComputeModelMatrix(const NdDrawing& node, glm::mat4& model, FLOATING weight)
{
    if (node.phys->HasBody()) {

        glm::vec3 prev_location = node.phys->prev_location;
        glm::vec3 current_location = node.phys->GetLocation();
        glm::quat prev_rotation = node.phys->prev_rotation;
        glm::quat current_rotation = node.phys->GetRotation();

        glm::vec3 location = weight * prev_location + (1 - weight) * current_location;
        glm::quat rotation = glm::slerp(prev_rotation, current_rotation, weight);

        model = glm::mat4{};
        model = glm::translate(model, location);
        model *= glm::mat4_cast(rotation);

    } else {
        model = glm::mat4{};
    }
}

void Drawing::m_DrawDebugMesh(
        const res::ResShaderDebug& shader,
        const NdDrawing& node,
        FLOATING weight)
{
    glm::mat4 model;
    m_ComputeModelMatrix(node, model, weight);

    glUniformMatrix4fv(shader.model_loc, 1, GL_FALSE, glm::value_ptr(model));

    glVertexAttribPointer(
        shader.coord_loc, 3, GL_FLOAT, GL_FALSE, 0,
        &node.appr->vertexes[0]);

    glVertexAttribPointer(
        shader.color_loc, 3, GL_FLOAT, GL_FALSE, 0,
        &node.appr->colors[0]);

    glDrawArrays(GL_TRIANGLES, 0, node.appr->GetVertexCount());
}

/* API implementation.
 * ===================
 */

Drawing::Drawing(res::Resources& resources) :
    m_resources(resources),
    m_camera(nullptr)
{}

void Drawing::Perform(double weight)
{
    m_FrameBegin();
    m_ShaderBegin(*m_resources.res_debug_shader);
    m_CameraApply(*m_resources.res_debug_shader, weight);

    for (auto& node : m_nodes) {
        m_DrawDebugMesh(*m_resources.res_debug_shader, node, weight);
    }

    m_ShaderEnd(*m_resources.res_debug_shader);
    m_FrameEnd();
}

}
