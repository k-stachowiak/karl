#ifndef CMP_PHYSICS_CAR_H
#define CMP_PHYSICS_CAR_H

#include <memory>
#include <vector>

#include <ode/ode.h>

#include "Auto.h"
#include "Common.h"
#include "CmpPhysics.h"

namespace cmp {

struct CmpPhysicsCar : public CmpPhysics {

    OdeBody chassis_body;
    OdeGeom chassis_geom;
    OdeBody rtrack_body;
    OdeGeom rtrack_geom;
    OdeBody ltrack_body;
    OdeGeom ltrack_geom;
    OdeJoint rjoint;
    OdeJoint ljoint;

    CmpPhysicsCar(
        dWorldID world, dSpaceID space,
        FLOATING cx, FLOATING cy, FLOATING cz);

    bool HasBody() const override { return true; }

    glm::vec3 GetLocation() const override
    {
        const FLOATING *pos = dBodyGetPosition(chassis_body.get());
        return { pos[0], pos[1], pos[2] };
    }

    glm::quat GetRotation() const override
    {
        const FLOATING* q = dBodyGetQuaternion(chassis_body.get());
        return { q[0], q[1], q[2], q[3] };
    }

    bool HasTrack(dBodyID maybe_track) const override;

    dBodyID GetLTrackBody() const { return ltrack_body.get(); }
    dBodyID GetRTrackBody() const { return rtrack_body.get(); }
};

}

#endif
