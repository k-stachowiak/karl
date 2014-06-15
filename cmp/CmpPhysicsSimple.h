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

    dBodyID GetBody() const override { return body.get(); }


};

}

#endif

