#ifndef CMP_PHYSICS_SIMPLE_H
#define CMP_PHYSICS_SIMPLE_H

#include "Auto.h"
#include "Common.h"
#include "CmpPhysics.h"

namespace cmp {

struct CmpPhysicsSimple : public CmpPhysics {

    OdeBody body;
    OdeGeom geom;

    static CmpPhysicsSimple MakePlane(dSpaceID space);
    static CmpPhysicsSimple MakeBox(
        dWorldID world, dSpaceID space,
        FLOATING mass,
        FLOATING x, FLOATING y, FLOATING z,
        FLOATING lx, FLOATING ly, FLOATING lz);

    bool HasBody() const override { return (bool)body; }

    glm::vec3 GetLocation() const override
    {
        const FLOATING *pos = dBodyGetPosition(body.get());
        return { pos[0], pos[1], pos[2] };
    }

    glm::quat GetRotation() const override
    {
        const FLOATING* q = dBodyGetQuaternion(body.get());
        return { q[0], q[1], q[2], q[3] };
    }
};

}

#endif

