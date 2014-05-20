#include <cstdio>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#include "Common.h"
#include "Config.h"
#include "SysDrawing.h"
#include "Resources.h"

/* Camera management.
 * ==================
 */

namespace sys {

Drawing::Camera::Camera() :
    location { 0, 0, 0.75f },
    rotation { 0, 0, 0 },
    view {},
    projection {
        glm::perspective(
            cfg_cam_fovy,
            cfg_screen_w / cfg_screen_h,
            cfg_cam_near,
            cfg_cam_far) }
{}

void Drawing::Camera::Move(FLOATING dx, FLOATING dy)
{
    prev_location = location;
    location[0] += dx;
    location[1] += dy;
}

void Drawing::Camera::Walk(FLOATING front, FLOATING right)
{
    FLOATING dx, dy;
    CastRotatedCoords(front, right, rotation[1], dx, dy);
    Move(dx, dy);
}

void Drawing::Camera::Rotate(FLOATING pitch, FLOATING yaw)
{
    prev_rotation = rotation;
    rotation[0] += pitch;
    rotation[1] += yaw;
}

void Drawing::m_CameraUpdateViewMatrix(FLOATING weight)
{
    glm::vec3 inter_location = (
        weight * m_camera.prev_location +
        (1 - weight) * m_camera.location);

    glm::vec3 inter_rotation = (
        weight * m_camera.prev_rotation +
        (1 - weight) * m_camera.rotation);

    m_camera.view = glm::mat4{};
    m_camera.view = glm::rotate(m_camera.view, -inter_rotation[0], glm::vec3 { 1, 0, 0 });
    m_camera.view = glm::rotate(m_camera.view, -inter_rotation[1], glm::vec3 { 0, 1, 0 });
    m_camera.view = glm::rotate(m_camera.view, 3.1415f / 2, glm::vec3 { 0, 1, 0 });
    m_camera.view = glm::rotate(m_camera.view, -3.1415f / 2, glm::vec3 { 1, 0, 0 });
    m_camera.view = glm::translate(m_camera.view, -inter_location);
}

void Drawing::m_CameraApply(const Shader &shader, FLOATING weight)
{
    m_CameraUpdateViewMatrix(weight);
    glUniformMatrix4fv(shader.view_loc, 1, GL_FALSE, glm::value_ptr(m_camera.view));
    glUniformMatrix4fv(shader.projection_loc, 1, GL_FALSE, glm::value_ptr(m_camera.projection));
}

void Drawing::m_ShaderBegin(const Shader &shader)
{
    glUseProgram(shader.program);
    glEnableVertexAttribArray(shader.coord_loc);
    glEnableVertexAttribArray(shader.color_loc);
}

void Drawing::m_ShaderEnd(const Shader &shader)
{
    glDisableVertexAttribArray(shader.coord_loc);
    glDisableVertexAttribArray(shader.color_loc);
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

void Drawing::m_DrawMesh(const Shader& shader, const NdDrawing& node, FLOATING weight)
{
    glm::mat4 model;
    m_ComputeModelMatrix(node, model, weight);

    glUniformMatrix4fv(shader.model_loc, 1, GL_FALSE, glm::value_ptr(model));
    glVertexAttribPointer(shader.coord_loc, 3, GL_FLOAT, GL_FALSE, 0, &node.appr->vertexes[0]);
    glVertexAttribPointer(shader.color_loc, 3, GL_FLOAT, GL_FALSE, 0, &node.appr->colors[0]);

    glDrawArrays(GL_TRIANGLES, 0, node.appr->GetVertexCount());
}

/* API implementation.
 * ===================
 */

Drawing::Drawing(Resources& resources) :
    m_resources(resources)
{}

void Drawing::CameraMove(FLOATING dx, FLOATING dy)
{
    m_camera.Move(dx, dy);
}

void Drawing::CameraWalk(FLOATING front, FLOATING right)
{
    m_camera.Walk(front, right);
}

void Drawing::CameraRotate(FLOATING pitch, FLOATING yaw)
{
    m_camera.Rotate(pitch, yaw);
}

void Drawing::Perform(double weight)
{
    m_FrameBegin();
    m_ShaderBegin(*m_resources.res_simple_shader);
    m_CameraApply(*m_resources.res_simple_shader, weight);

    for (auto& node : m_nodes) {
        m_DrawMesh(*m_resources.res_simple_shader, node, weight);
    }

    m_ShaderEnd(*m_resources.res_simple_shader);
    m_FrameEnd();
}

}
