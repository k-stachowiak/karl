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

    dBodyID GetBody() const override { return chassis_body.get(); }

    bool HasTrack(dBodyID maybe_track) const override;

    void ApplyDriveForces(FLOATING boost, FLOATING turn);
};

}

#endif
