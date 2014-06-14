#include "Config.h"
#include "CmpPhysicsTank.h"

namespace cmp {

CmpPhysicsTank::TriMeshPiece::TriMeshPiece(
        dWorldID world, dSpaceID space,
        FLOATING cx, FLOATING cy, FLOATING cz,
        const std::vector<glm::vec3>& vertexes) :
    vex { vertexes },
    tmd { dGeomTriMeshDataCreate() }
{
    // Initialize the fake indexes for the trimesh index based representation.
    // NOTE: This can be packed if required as an optimization.
    for (unsigned i = 0; i < vertexes.size(); ++i) {
        ind.push_back(i);
    }

    // Prepare the data for the trimesh geom.
    dGeomTriMeshDataBuildSingle(tmd.get(),
        &vex[0], sizeof(decltype(vex)::value_type), vex.size(),
        &ind[0], ind.size(), sizeof(decltype(ind)::value_type));

    // Create the geom itself.
    geom.reset(dCreateTriMesh(space, tmd.get(), nullptr, nullptr, nullptr));

    // Create the body.
    glm::vec3 bound_min, bound_max;
    for (const auto& v : vex) {
        for (int i = 0; i < 3; ++i) {
            if (v[i] < bound_min[i]) {
                bound_min[i] = v[i];
            }
            if (v[i] > bound_max[i]) {
                bound_max[i] = v[i];
            }
        }
    }

    FLOATING lx = bound_max[0] - bound_min[0];
    FLOATING ly = bound_max[1] - bound_min[1];
    FLOATING lz = bound_max[2] - bound_min[2];

    dMass dm;
    dMassSetBoxTotal(&dm, 100, lx, ly, lz);

    FLOATING x = cx + bound_min[0] + lx / 2;
    FLOATING y = cy + bound_min[1] + ly / 2;
    FLOATING z = cz + bound_min[2] + lz / 2;

    body.reset(dBodyCreate(world));
    dBodySetPosition(body.get(), x, y, z);
    dBodySetMass(body.get(), &dm);

    // Attach the body to the geom.
    dGeomSetBody(geom.get(), body.get());

    // Set initial "prevoius transform".
    StoreTransform();
}

void CmpPhysicsTank::TriMeshPiece::StoreTransform()
{
    prev_transform = g_ComputeBodyMatrix(body.get());
}

CmpPhysicsTank::CmpPhysicsTank(
        dWorldID world, dSpaceID space,
        FLOATING cx, FLOATING cy, FLOATING cz,
        const std::vector<glm::vec3>& ltrack_vertexes,
        const std::vector<glm::vec3>& rtrack_vertexes,
        const std::vector<glm::vec3>& body_vertexes) :
    m_ltrack_piece { world, space, cx, cy, cz, ltrack_vertexes },
    m_rtrack_piece { world, space, cx, cy, cz, rtrack_vertexes },
    m_chassis_piece { world, space, cx, cy, cz, body_vertexes }
{
    m_ljoint.reset(dJointCreateFixed(world, 0));
    dJointAttach(m_ljoint.get(), m_chassis_piece.body.get(), m_ltrack_piece.body.get());
    dJointSetFixed(m_ljoint.get());

    m_rjoint.reset(dJointCreateFixed(world, 0));
    dJointAttach(m_rjoint.get(), m_chassis_piece.body.get(), m_rtrack_piece.body.get());
    dJointSetFixed(m_rjoint.get());
}

bool CmpPhysicsTank::HasTrack(dBodyID body) const
{
    return m_ltrack_piece.body.get() == body ||
           m_rtrack_piece.body.get() == body;
}

void CmpPhysicsTank::UpdateFrame()
{
    CmpPhysics::UpdateFrame();
    m_ltrack_piece.StoreTransform();
    m_rtrack_piece.StoreTransform();
    m_chassis_piece.StoreTransform();
}

void CmpPhysicsTank::ApplyDriveForces(FLOATING boost, FLOATING turn)
{
    FLOATING lfx, lfy, rfx, rfy;

    glm::vec3 rot = GetRotationAngles();

    g_CastRotatedCoords(
        boost * cfg_tank_boost_force + turn * cfg_tank_turn_force,
        0, rot.z, rfx, rfy);

    g_CastRotatedCoords(
        boost * cfg_tank_boost_force - turn * cfg_tank_turn_force,
        0, rot.z, lfx, lfy);

    dBodyAddForce(m_rtrack_piece.body.get(), rfx, rfy, 0);
    dBodyAddForce(m_ltrack_piece.body.get(), lfx, lfy, 0);

}

}
