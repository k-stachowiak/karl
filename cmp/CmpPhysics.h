#ifndef CMP_PHYSICS_H
#define CMP_PHYSICS_H

#include "Auto.h"
#include "Common.h"

namespace cmp {

struct CmpPhysics {

    glm::vec3 prev_location;
    glm::quat prev_rotation;

    virtual ~CmpPhysics() {}

    virtual bool HasBody() const = 0;
    virtual glm::vec3 GetLocation() const = 0;
    virtual glm::quat GetRotation() const = 0;

    virtual bool HasTrack(dBodyID) const { return false; }

    glm::vec3 GetDirection() const;
    glm::vec3 GetRotationAngles() const;
};

}

#endif

