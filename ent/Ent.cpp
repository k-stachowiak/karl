#include <cstdio>
#include <algorithm>
#include <iterator>

#include "GeomFac.h"
#include "Ent.h"

namespace {

long next_id = 1;

std::vector<res::ResShaderDebug::Vertex> g_GenCollDebugVertexes(
        const res::ResModelTank& model)
{
    static auto make_vex = [](const glm::vec3& v) {
        return res::ResShaderDebug::Vertex { v, { 1.0f, 0, 0 } };
    };

    std::vector<res::ResShaderDebug::Vertex> result;

    const auto& ch = model.coll_geoms.at(res::ResModelTank::Piece::COL_CHASSIS);
    std::transform(begin(ch), end(ch), std::back_inserter(result), make_vex);

    const auto& lt = model.coll_geoms.at(res::ResModelTank::Piece::COL_LTRACK);
    std::transform(begin(lt), end(lt), std::back_inserter(result), make_vex);

    const auto& rt = model.coll_geoms.at(res::ResModelTank::Piece::COL_RTRACK);
    std::transform(begin(rt), end(rt), std::back_inserter(result), make_vex);

    return result;
}

}

namespace ent {

EntGround::EntGround(
        dWorldID, dSpaceID space,
        GLint location_loc, GLint color_loc) :
    id { next_id++ },
    apprd { g_GenerateGroundDebugVertexes(3, 20, 0.0, 0.25, 0.0),
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
    apprd { g_GenerateCarDebugVertexes(),
           location_loc, color_loc }
{}

EntTank2::EntTank2(
        dWorldID world, dSpaceID space,
        const res::ResModelTank& model,
        GLint tank_location_loc, GLint tank_tex_coord_loc,
        GLint debug_location_loc, GLint debug_color_loc,
        GLuint texture_id) :
    id { next_id++ }, // TODO: Store ID in resources?
    phys { world, space, 3, 3, 1,
        model.coll_geoms.at(res::ResModelTank::Piece::COL_LTRACK),
        model.coll_geoms.at(res::ResModelTank::Piece::COL_RTRACK),
        model.coll_geoms.at(res::ResModelTank::Piece::COL_CHASSIS) },
    apprt { model.GetAllVertexes(),
            tank_location_loc,
            tank_tex_coord_loc,
            texture_id },
    apprd { g_GenCollDebugVertexes(model),
            debug_location_loc,
            debug_color_loc }
{}

}
