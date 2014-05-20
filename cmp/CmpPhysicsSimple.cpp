#include <algorithm>
#include "config.h"
#include "CmpPhysicsSimple.h"

namespace cmp {

CmpPhysicsSimple CmpPhysicsSimple::MakePlane(dSpaceID space)
{
    CmpPhysicsSimple result;
    result.geom.reset(dCreatePlane(space, 0, 0, 1, 0));
    result.body = nullptr;
    return result;
}

CmpPhysicsSimple CmpPhysicsSimple::MakeBox(
            dWorldID world, dSpaceID space,
            FLOATING mass,
            FLOATING x, FLOATING y, FLOATING z,
            FLOATING lx, FLOATING ly, FLOATING lz)
{
    CmpPhysicsSimple result;

    dMass dm;
    dMassSetBoxTotal(&dm, mass, lx, ly, lz);

    result.body.reset(dBodyCreate(world));
    dBodySetPosition(result.body.get(), x, y, z);
    dBodySetMass(result.body.get(), &dm);

    result.geom.reset(dCreateBox(space, lx, ly, lz));
    dGeomSetBody(result.geom.get(), result.body.get());

    return result;
}

}

