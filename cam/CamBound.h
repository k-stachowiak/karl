#ifndef CAM_BOUND_H
#define CAM_BOUND_H

#include "Camera.h"

class CamBound : public Camera {

    // TODO: The data here is the same as in the flying camera.
    //       consider putting the data in the base class - will this really
    //       ever be different?

    glm::vec3 m_location, m_prev_location;
    glm::vec3 m_rotation, m_prev_rotation;

    glm::mat4 m_view, m_projection;

public:
    void Update(FLOATING weight) override;
    const glm::mat4& GetViewMatrix() override { return m_view; }
    const glm::mat4& GetProjectionMatrix() override { return m_projection; }

    void SetAltitude(FLOATING altitude);
    void SetLocation(FLOATING x, FLOATING y);
    void Rotate(FLOATING pitch, FLOATING yaw);
};

#endif
