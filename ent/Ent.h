#ifndef ENT_H
#define ENT_H

#include <ode/ode.h>

#include "Common.h"
#include "CmpPhysicsSimple.h"
#include "CmpPhysicsCar.h"
#include "CmpPhysicsTank.h"
#include "CmpApprDebugInd.h"
#include "CmpApprTankVex.h"
#include "ResModelTank.h"

namespace ent {

struct EntGround {
    long id;
    cmp::CmpPhysicsSimple phys;
    cmp::CmpApprDebugInd appr;
    EntGround(
        dWorldID world, dSpaceID space,
        GLint location_loc, GLint color_loc);
};

struct EntTank {
    long id;
    cmp::CmpPhysicsCar phys;
    cmp::CmpApprDebugInd appr;
    EntTank(
        dWorldID world, dSpaceID space,
        GLint location_loc, GLint color_loc);
};

struct EntTank2 {
    long id;
    cmp::CmpPhysicsTank phys;
    cmp::CmpApprTankVex appr;
    EntTank2(
        dWorldID world, dSpaceID space,
        const res::ResModelTank& model,
        GLint location_loc, GLint tex_coord_loc,
        GLuint texture_id);
};

}

#endif
