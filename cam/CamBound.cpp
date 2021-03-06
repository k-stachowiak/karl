#include "CamBound.h"

CamBound::CamBound(FLOATING offset, FLOATING altitude) :
    m_offset { offset }
{
    m_location[2] = altitude;
}

void CamBound::Update(FLOATING weight)
{
    glm::vec3 inter_location = (
        weight * m_prev_location +
        (1 - weight) * m_location);

    glm::vec3 inter_rotation = (
        weight * m_prev_rotation +
        (1 - weight) * m_rotation);

    t_view = glm::mat4{};

    // Step back some
    t_view = glm::translate(t_view, glm::vec3 { 0, 0, m_offset });

    // Apply the camera pitch rotation.
    t_view = glm::rotate(t_view, -inter_rotation[0], glm::vec3 { 1, 0, 0 });

    // Apply the camera yaw rotation.
    t_view = glm::rotate(t_view, -inter_rotation[1], glm::vec3 { 0, 1, 0 });

    // Make the camera look along the x axis.
    t_view = glm::rotate(t_view, 3.1415f / 2, glm::vec3 { 0, 1, 0 });
    t_view = glm::rotate(t_view, -3.1415f / 2, glm::vec3 { 1, 0, 0 });

    // Move to the location.
    t_view = glm::translate(t_view, -inter_location);
}

void CamBound::SetLocation(FLOATING x, FLOATING y)
{
    m_prev_location = m_location;
    m_location[0] = x;
    m_location[1] = y;
}

void CamBound::Rotate(FLOATING pitch, FLOATING yaw)
{
    m_prev_rotation = m_rotation;
    m_rotation[0] += pitch;
    m_rotation[1] += yaw;
}
