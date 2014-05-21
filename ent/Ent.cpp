#include <cstdio>

#include "Ent.h"

namespace {
    long next_id = 1;
}

namespace ent {

static FLOATING xy_to_zero(int, int)
{
    return 0;
}

EntGround::EntGround(dWorldID, dSpaceID space) :
    id { next_id++ }
{
    const int x_segments = 3;
    const int y_segments = 20;

    phys = cmp::CmpPhysicsSimple::MakePlane(space);
    appr = cmp::CmpAppearance::MakeFlat(
        x_segments,
        y_segments,
        0,
        0.25,
        0,
        xy_to_zero);
}

EntTank::EntTank(dWorldID world, dSpaceID space) :
    id { next_id++ },
    phys { world, space, 1.5, 1.5, 2 }
{
    appr = cmp::CmpAppearance::MakeCar();
}

}
