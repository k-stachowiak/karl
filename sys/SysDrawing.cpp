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

void Drawing::m_FrameBegin()
{
    glViewport(0, 0, cfg_screen_w, cfg_screen_h);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glPolygonMode(GL_FRONT, GL_FILL);
}

void Drawing::m_FrameEnd()
{
}

void Drawing::m_DrawDebugNode(const NdDrawingDebug& node, FLOATING weight)
{
    glm::mat4 model = node.phys->GetMatrix(weight);
    glUniformMatrix4fv(
        m_resources.res_debug_shader->model_loc,
        1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(node.appr->m_vao);

    glDrawElements(
        GL_TRIANGLES,
        node.appr->m_num_primitives,
        GL_UNSIGNED_INT,
        0);

    glBindVertexArray(0);
}

void Drawing::m_DrawTankNode(const NdDrawingTank& node, FLOATING weight)
{
    glm::mat4 model = node.phys->GetMatrix(weight);
    glUniformMatrix4fv(
        m_resources.res_debug_shader->model_loc,
        1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(node.appr->m_vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, node.appr->m_tid);

    glDrawArrays(GL_TRIANGLES, 0, node.appr->m_num_primitives);

    glBindVertexArray(0);
}

/* API implementation.
 * ===================
 */

Drawing::Drawing(res::Resources& resources) :
    m_resources(resources),
    m_camera(nullptr)
{
}

void Drawing::Perform(double weight)
{
    m_FrameBegin();

    m_resources.res_debug_shader->Begin();
    m_CameraApply(*m_resources.res_debug_shader, weight);

    for (const auto& node : m_nodes_debug) {
        m_DrawDebugNode(node, weight);
    }

    m_resources.res_debug_shader->End();

    m_resources.res_tank_shader->Begin();
    m_CameraApply(*m_resources.res_tank_shader, weight);

    for (const auto& node : m_nodes_tank) {
        m_DrawTankNode(node, weight);
    }

    m_resources.res_tank_shader->End();

    m_FrameEnd();

}

}
