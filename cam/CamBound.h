#ifndef CAM_BOUND_H
#define CAM_BOUND_H

#include "Camera.h"

class CamBound : public Camera {

    FLOATING m_offset;
    glm::vec3 m_location, m_prev_location;
    glm::vec3 m_rotation, m_prev_rotation;

public:
    CamBound(FLOATING offset, FLOATING altitude);
    void Update(FLOATING weight) override;

    void SetLocation(FLOATING x, FLOATING y);
    void Rotate(FLOATING pitch, FLOATING yaw);
};

#endif
