#include "CamFlying.h"

CamFlying::CamFlying() :
    m_location { 0, 0, 0.75f },
    m_rotation { 0, 0, 0 }
{}

void CamFlying::Update(FLOATING weight)
{
    glm::vec3 inter_location = (
        weight * m_prev_location +
        (1 - weight) * m_location);

    glm::vec3 inter_rotation = (
        weight * m_prev_rotation +
        (1 - weight) * m_rotation);

    t_view = glm::mat4{};
    t_view = glm::rotate(t_view, -inter_rotation[0], glm::vec3 { 1, 0, 0 });
    t_view = glm::rotate(t_view, -inter_rotation[1], glm::vec3 { 0, 1, 0 });
    t_view = glm::rotate(t_view, 3.1415f / 2, glm::vec3 { 0, 1, 0 });
    t_view = glm::rotate(t_view, -3.1415f / 2, glm::vec3 { 1, 0, 0 });
    t_view = glm::translate(t_view, -inter_location);
}

void CamFlying::Move(FLOATING dx, FLOATING dy)
{
    m_prev_location = m_location;
    m_location[0] += dx;
    m_location[1] += dy;
}

void CamFlying::Walk(FLOATING front, FLOATING right)
{
    FLOATING dx, dy;
    CastRotatedCoords(front, right, m_rotation[1], dx, dy);
    Move(dx, dy);
}

void CamFlying::Rotate(FLOATING pitch, FLOATING yaw)
{
    m_prev_rotation = m_rotation;
    m_rotation[0] += pitch;
    m_rotation[1] += yaw;
}

