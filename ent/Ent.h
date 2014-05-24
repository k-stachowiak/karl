#ifndef ENT_H
#define ENT_H

#include <ode/ode.h>

#include "Common.h"
#include "CmpPhysicsSimple.h"
#include "CmpPhysicsSimple.h"
#include "CmpPhysicsCar.h"
#include "CmpAppearance.h"
#include "CmpApprDebug.h"

namespace ent {

struct EntGround {
    long id;
    cmp::CmpPhysicsSimple phys;
    cmp::CmpAppearance appr;
    EntGround(dWorldID world, dSpaceID space);
};

struct EntTank {
    long id;
    cmp::CmpPhysicsCar phys;
    cmp::CmpAppearance appr;
    EntTank(dWorldID world, dSpaceID space);
};

}

#endif
