#ifndef ENT_H
#define ENT_H

#include <ode/ode.h>

#include "common.h"
#include "CmpPhysicsSimple.h"
#include "sys_drawing.h"
#include "sys_physics.h"
#include "CmpPhysicsSimple.h"
#include "CmpPhysicsCar.h"

struct EntGround {
    long id;
    cmp::CmpPhysicsSimple phys;
    cmp::CmpAppearance appr;

    EntGround(dWorldID world, dSpaceID space);
    sys::NdDrawing MakeDrawingNode();
    sys::NdPhysics MakePhysicsNode();
};

struct EntTank {
    long id;
    cmp::CmpPhysicsCar phys;
    cmp::CmpAppearance appr;

    EntTank(dWorldID world, dSpaceID space);
    sys::NdDrawing MakeDrawingNode();
    sys::NdPhysics MakePhysicsNode();
};

#endif
