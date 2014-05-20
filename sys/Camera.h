#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"

class Camera {
public:
    virtual ~Camera() {}
    virtual void Update(FLOATING weight) = 0;
    virtual const glm::mat4& GetViewMatrix() = 0;
    virtual const glm::mat4& GetProjectionMatrix() = 0;
};

#endif
