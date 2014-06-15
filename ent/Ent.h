#ifndef ENT_H
#define ENT_H

#include <ode/ode.h>

#include "Common.h"
#include "CmpPhysicsSimple.h"
#include "CmpPhysicsCar.h"
#include "CmpPhysicsTank.h"
#include "CmpApprDebug.h"
#include "CmpApprTank.h"
#include "ResModelTank.h"

namespace ent {

struct EntGround {
    long id;
    cmp::CmpPhysicsSimple phys;
    cmp::CmpApprDebug apprd;
    EntGround(
        dWorldID world, dSpaceID space,
        GLint location_loc, GLint color_loc);
};

struct EntTank {
    long id;
    cmp::CmpPhysicsCar phys;
    cmp::CmpApprDebug apprd;
    EntTank(
        dWorldID world, dSpaceID space,
        GLint location_loc, GLint color_loc);
};

struct EntTank2 {
    long id;
    cmp::CmpPhysicsTank phys;
    cmp::CmpApprTank apprt;
    cmp::CmpApprDebug apprd;
    EntTank2(
        dWorldID world, dSpaceID space,
        const res::ResModelTank& model,
        GLint tank_location_loc, GLint tank_tex_coord_loc,
        GLint debug_location_loc, GLint debug_color_loc,
        GLuint texture_id);
};

}

#endif
