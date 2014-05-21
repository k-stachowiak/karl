#ifndef CAM_FLYING_H
#define CAM_FLYING_H

#include "Camera.h"

class CamFlying : public Camera {

    glm::vec3 m_location, m_prev_location;
    glm::vec3 m_rotation, m_prev_rotation;

public:
    CamFlying();

    void Update(FLOATING weight) override;

    void Move(FLOATING dx, FLOATING dy);
    void Walk(FLOATING front, FLOATING right);
    void Rotate(FLOATING pitch, FLOATING yaw);
};

#endif
