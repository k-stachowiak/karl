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

EntTank::EntTank(
        dWorldID world, dSpaceID space,
        GLint location_loc, GLint color_loc) :
    id { next_id++ },
    phys { world, space, 1.5, 1.5, 2 },
    // Move all this global crap into resources class or delete.
    appr { g_GenerateCarDebugVertexes(),
           g_GenerateCarDebugIndexes(),
           location_loc, color_loc }
{}

EntTank2::EntTank2(
        dWorldID world, dSpaceID space,
        const res::ResModelTank& model,
        GLint location_loc, GLint tex_coord_loc,
        GLuint texture_id) :
    id { next_id++ }, // TODO: Store ID in resources?
    phys { world, space, 3, 3, 1,
        model.coll_geoms.at(res::ResModelTank::Piece::COL_LTRACK),
        model.coll_geoms.at(res::ResModelTank::Piece::COL_RTRACK),
        model.coll_geoms.at(res::ResModelTank::Piece::COL_CHASSIS) },
    appr { model.GetAllVertexes(),
           location_loc, tex_coord_loc,
           texture_id }
{
}

}
