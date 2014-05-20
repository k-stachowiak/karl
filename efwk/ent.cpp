#include <cstdio>

#include "ent.h"

namespace {
    long next_id = 1;
}

static FLOATING xy_to_zero(int, int)
{
    return 0;
}

EntGround::EntGround(dWorldID, dSpaceID space) :
    id { next_id++ }
{
    const int x_segments = 3;
    const int y_segments = 20;

    phys = cmp::PhysicsSimple::MakePlane(space);
    appr = cmp::Appearance::MakeFlat(x_segments, y_segments, 0, 0.25, 0, xy_to_zero);
}

sys::NdDrawing EntGround::MakeDrawingNode()
{
    return { id, &phys, &appr };
}

sys::NdPhysics EntGround::MakePhysicsNode()
{
    return { id, &phys };
}

EntTank::EntTank(dWorldID world, dSpaceID space) :
    id { next_id++ },
    phys { world, space, 1.5, 1.5, 2 }
{
    appr = cmp::Appearance::MakeCar();
}

sys::NdDrawing EntTank::MakeDrawingNode()
{
    return { id, &phys, &appr };
}

sys::NdPhysics EntTank::MakePhysicsNode()
{
    return { id, &phys };
}

