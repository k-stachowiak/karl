#ifndef CAMERA_FLYING_H
#define CAMERA_FLYING_H

#include "Camera.h"

class CameraFlying : public Camera {

    glm::vec3 m_location, m_prev_location;
    glm::vec3 m_rotation, m_prev_rotation;

    glm::mat4 m_view, m_projection;

public:
    CameraFlying();

    void Update(FLOATING weight) override;
    const glm::mat4& GetViewMatrix() override;
    const glm::mat4& GetProjectionMatrix() override;

    void Move(FLOATING dx, FLOATING dy);
    void Walk(FLOATING front, FLOATING right);
    void Rotate(FLOATING pitch, FLOATING yaw);
};

#endif
