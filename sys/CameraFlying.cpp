#include "Config.h"
#include "CameraFlying.h"

CameraFlying::CameraFlying() :
    m_location { 0, 0, 0.75f },
    m_rotation { 0, 0, 0 },
    m_view {},
    m_projection {
        glm::perspective(
            cfg_cam_fovy,
            cfg_screen_w / cfg_screen_h,
            cfg_cam_near,
            cfg_cam_far) }
{}

void CameraFlying::Update(FLOATING weight)
{
    glm::vec3 inter_location = (
        weight * m_prev_location +
        (1 - weight) * m_location);

    glm::vec3 inter_rotation = (
        weight * m_prev_rotation +
        (1 - weight) * m_rotation);

    m_view = glm::mat4{};
    m_view = glm::rotate(m_view, -inter_rotation[0], glm::vec3 { 1, 0, 0 });
    m_view = glm::rotate(m_view, -inter_rotation[1], glm::vec3 { 0, 1, 0 });
    m_view = glm::rotate(m_view, 3.1415f / 2, glm::vec3 { 0, 1, 0 });
    m_view = glm::rotate(m_view, -3.1415f / 2, glm::vec3 { 1, 0, 0 });
    m_view = glm::translate(m_view, -inter_location);
}

void CameraFlying::Move(FLOATING dx, FLOATING dy)
{
    m_prev_location = m_location;
    m_location[0] += dx;
    m_location[1] += dy;
}

void CameraFlying::Walk(FLOATING front, FLOATING right)
{
    FLOATING dx, dy;
    CastRotatedCoords(front, right, m_rotation[1], dx, dy);
    Move(dx, dy);
}

void CameraFlying::Rotate(FLOATING pitch, FLOATING yaw)
{
    m_prev_rotation = m_rotation;
    m_rotation[0] += pitch;
    m_rotation[1] += yaw;
}

