#include <algorithm>
#include <iterator>
#include <cmath>

#include "Config.h"
#include "CmpPhysicsCar.h"

namespace cmp {

CmpPhysicsCar::CmpPhysicsCar(
        dWorldID world, dSpaceID space,
        FLOATING cx, FLOATING cy, FLOATING cz)
{
    const FLOATING clx = cfg_chassis_lx;
    const FLOATING cly = cfg_chassis_ly;
    const FLOATING clz = cfg_chassis_lz;
    const FLOATING tlx = cfg_track_lx;
    const FLOATING tly = cfg_track_ly;
    const FLOATING tlz = cfg_track_lz;

    dMass chassis_mass, track_mass;

    /* Configure chassis. */

    chassis_body.reset(dBodyCreate(world));
    dMassSetBoxTotal(&chassis_mass, 100, clx, cly, clz);
    dBodySetMass(chassis_body.get(), &chassis_mass);
    dBodySetMaxAngularSpeed(chassis_body.get(), cfg_tank_max_ang_speed);

    chassis_geom.reset(dCreateBox(space, clx, cly, clz));
    dGeomSetBody(chassis_geom.get(), chassis_body.get());
    dGeomSetPosition(chassis_geom.get(), cx, cy, cz);

    /* Configure tracks. */

    rtrack_body.reset(dBodyCreate(world));
    dMassSetBoxTotal(&track_mass, 10, tlx, tly, tlz);
    dBodySetMass(rtrack_body.get(), &track_mass);

    rtrack_geom.reset(dCreateBox(space, tlx, tly, tlz));
    dGeomSetBody(rtrack_geom.get(), rtrack_body.get());
    dGeomSetPosition(rtrack_geom.get(), cx + 0, cy + cly / 2, cz - clz / 2);

    ltrack_body.reset(dBodyCreate(world));
    dMassSetBoxTotal(&track_mass, 10, tlx, tly, tlz);
    dBodySetMass(ltrack_body.get(), &track_mass);

    ltrack_geom.reset(dCreateBox(space, tlx, tly, tlz));
    dGeomSetBody(ltrack_geom.get(), ltrack_body.get());
    dGeomSetPosition(ltrack_geom.get(), cx + 0, cy - cly / 2, cz - clz / 2);

    /* Connect joints. */

    rjoint.reset(dJointCreateFixed(world, 0));
    dJointAttach(rjoint.get(), chassis_body.get(), rtrack_body.get());
    dJointSetFixed(rjoint.get());

    ljoint.reset(dJointCreateFixed(world, 0));
    dJointAttach(ljoint.get(), chassis_body.get(), ltrack_body.get());
    dJointSetFixed(ljoint.get());
}

bool CmpPhysicsCar::HasTrack(dBodyID maybe_track) const
{
    return ltrack_body.get() == maybe_track || rtrack_body.get() == maybe_track;
}

void CmpPhysicsCar::ApplyDriveForces(FLOATING boost, FLOATING turn)
{
    FLOATING lfx, lfy, rfx, rfy;

    glm::vec3 rot = GetRotationAngles();

    g_CastRotatedCoords(
        boost * cfg_tank_boost_force + turn * cfg_tank_turn_force,
        0, rot.z, rfx, rfy);

    g_CastRotatedCoords(
        boost * cfg_tank_boost_force - turn * cfg_tank_turn_force,
        0, rot.z, lfx, lfy);

    dBodyAddForce(rtrack_body.get(), rfx, rfy, 0);
    dBodyAddForce(ltrack_body.get(), lfx, lfy, 0);
}

}
