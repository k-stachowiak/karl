#include <cstdio>

#include "GeomFac.h"
#include "Ent.h"

namespace {
    long next_id = 1;
}

namespace ent {

EntGround::EntGround(
        dWorldID, dSpaceID space,
        GLint location_loc, GLint color_loc) :
    id { next_id++ },
    appr { g_GenerateGroundDebugVertexes(3, 20, 0.0, 0.25, 0.0),
           g_GenerateGroundDebugIndexes(3, 20),
           location_loc, color_loc }
{
    phys = cmp::CmpPhysicsSimple::MakePlane(space);
}

EntTank::EntTank(dWorldID world, dSpaceID space) :
    id { next_id++ },
    phys { world, space, 1.5, 1.5, 2 }
{
    appr = cmp::CmpAppearance::MakeCar();
}

}
