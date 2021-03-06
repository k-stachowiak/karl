#ifndef CMP_PHYSICS_H
#define CMP_PHYSICS_H

#include "Auto.h"
#include "Common.h"

namespace cmp {

glm::mat4 g_ComputeBodyMatrix(dBodyID body);

struct CmpPhysics {

    glm::vec3 prev_location;
    glm::quat prev_rotation;

    virtual ~CmpPhysics() {}

    virtual dBodyID GetBody() const = 0;

    virtual bool HasTrack(dBodyID) const { return false; }
    virtual void UpdateFrame();

    glm::vec3 GetLocation() const;
    glm::quat GetRotation() const;

    glm::vec3 GetDirection() const;
    glm::vec3 GetRotationAngles() const;

    glm::mat4 GetMatrix() const;
    glm::mat4 GetMatrix(FLOATING weight) const;
};

}

#endif

