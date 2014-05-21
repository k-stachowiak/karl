#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include "Config.h"

class Camera {
protected:
    glm::mat4 t_view;
    glm::mat4 t_projection;

public:
    Camera() :
        t_view {},
        t_projection {
            glm::perspective(
                cfg_cam_fovy,
                cfg_screen_w / cfg_screen_h,
                cfg_cam_near,
                cfg_cam_far) }
    {}

    virtual ~Camera() {}
    virtual void Update(FLOATING weight) = 0;

    const glm::mat4& GetViewMatrix() { return t_view; }
    const glm::mat4& GetProjectionMatrix() { return t_projection; }
};

#endif
