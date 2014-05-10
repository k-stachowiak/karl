#include <algorithm>
#include <iterator>
#include <cmath>

#include "config.h"
#include "cmp.h"

namespace cmp {

// TODO: Remember to remove geoms from space, becaus now, the deleters don't do it.

static glm::vec3 verbose_cube_definition[36] = {

	/* To the front! */
	{ -1, -1, +1 },
	{ -1, +1, +1 },
	{ +1, +1, +1 },
	{ -1, -1, +1 },
	{ +1, +1, +1 },
	{ +1, -1, +1 },

	/* To the back! */
	{ +1, -1, -1 },
	{ +1, +1, -1 },
	{ -1, +1, -1 },
	{ +1, -1, -1 },
	{ -1, +1, -1 },
	{ -1, -1, -1 },

	/* To the right! */
	{ +1, -1, +1 },
	{ +1, +1, +1 },
	{ +1, +1, -1 },
	{ +1, -1, +1 },
	{ +1, +1, -1 },
	{ +1, -1, -1 },

	/* To the left! */
	{ -1, -1, -1 },
	{ -1, +1, -1 },
	{ -1, +1, +1 },
	{ -1, -1, -1 },
	{ -1, +1, +1 },
	{ -1, -1, +1 },

	/* To the bottom! */
	{ -1, -1, -1 },
	{ -1, -1, +1 },
	{ +1, -1, +1 },
	{ -1, -1, -1 },
	{ +1, -1, +1 },
	{ +1, -1, -1 },

	/* To the top! */
	{ -1, +1, +1 },
	{ -1, +1, -1 },
	{ +1, +1, -1 },
	{ -1, +1, +1 },
	{ +1, +1, -1 },
	{ +1, +1, +1 },
};

Appearance Appearance::MakeFlat(
		int lx, int ly,
		FLOATING r, FLOATING g, FLOATING b,
		FLOATING (*altitude)(int, int))
{
	Appearance result;

	for (int i = 0; i < lx; ++i) {
		for (int j = 0; j < ly; ++j) {

			const FLOATING base_x = (FLOATING)i + 0.5;
			const FLOATING base_y = (FLOATING)j + 0.5;

			result.vertexes.push_back(glm::vec3 { base_x - 0.5f, base_y - 0.5f, altitude(i, j) });
			result.vertexes.push_back(glm::vec3 { base_x - 0.5f, base_y + 0.5f, altitude(i, j + 1) });
			result.vertexes.push_back(glm::vec3 { base_x + 0.5f, base_y + 0.5f, altitude(i + 1, j + 1) });
			result.vertexes.push_back(glm::vec3 { base_x - 0.5f, base_y - 0.5f, altitude(i, j) });
			result.vertexes.push_back(glm::vec3 { base_x + 0.5f, base_y + 0.5f, altitude(i + 1, j + 1) });
			result.vertexes.push_back(glm::vec3 { base_x + 0.5f, base_y - 0.5f, altitude(i + 1, j) });

			result.colors.push_back(glm::vec3 { r, g, b });
			result.colors.push_back(glm::vec3 { r, g, b });
			result.colors.push_back(glm::vec3 { r, g, b });
			result.colors.push_back(glm::vec3 { r, g, b });
			result.colors.push_back(glm::vec3 { r, g, b });
			result.colors.push_back(glm::vec3 { r, g, b });
		}
	}

	return result;
}

Appearance Appearance::MakeBox(
		FLOATING lx, FLOATING ly, FLOATING lz,
		FLOATING r, FLOATING g, FLOATING b)
{
	Appearance result;

	std::copy(
		verbose_cube_definition,
		verbose_cube_definition + 36,
		std::back_inserter(result.vertexes));

	for (int i = 0; i < 36; ++i) {
		result.vertexes[i][0] *= lx / 2;
		result.vertexes[i][1] *= ly / 2;
		result.vertexes[i][2] *= lz / 2;
		result.colors.push_back({ r, g, b });
	}

	return result;
}

Appearance Appearance::MakeCar()
{
	const FLOATING clx = cfg_chassis_lx;
	const FLOATING cly = cfg_chassis_ly;
	const FLOATING clz = cfg_chassis_lz;
	const FLOATING tlx = cfg_track_lx;
	const FLOATING tly = cfg_track_ly;
	const FLOATING tlz = cfg_track_lz;

	Appearance result;

	/* Build chassis. */

	std::copy(
		verbose_cube_definition,
		verbose_cube_definition + 36,
		std::back_inserter(result.vertexes));

	for (int i = 0; i < 36; ++i) {
		result.vertexes[i][0] *= clx / 2;
		result.vertexes[i][1] *= cly / 2;
		result.vertexes[i][2] *= clz / 2;
		result.colors.push_back({ 0.25, 0, 0 });
	}

	/* Build track. */

	std::copy(
		verbose_cube_definition,
		verbose_cube_definition + 36,
		std::back_inserter(result.vertexes));

	for (int i = 36; i < 72; ++i) {
		result.vertexes[i][0] *= tlx / 2;
		result.vertexes[i][1] *= tly / 2;
		result.vertexes[i][2] *= tlz / 2;
		result.vertexes[i][0] += 0;
		result.vertexes[i][1] += cly / 2;
		result.vertexes[i][2] += -clz / 2;
		result.colors.push_back({ 0, 0, 0.25 });
	}

	std::copy(
		verbose_cube_definition,
		verbose_cube_definition + 36,
		std::back_inserter(result.vertexes));

	for (int i = 72; i < 108; ++i) {
		result.vertexes[i][0] *= tlx / 2;
		result.vertexes[i][1] *= tly / 2;
		result.vertexes[i][2] *= tlz / 2;
		result.vertexes[i][0] += 0;
		result.vertexes[i][1] += -cly / 2;
		result.vertexes[i][2] += -clz / 2;
		result.colors.push_back({ 0, 0, 0.25 });
	}

	return result;
}

void Physics::GetDirection(FLOATING &dx, FLOATING &dy, FLOATING &dz) const
{
	FLOATING ode_rot_mat[4 * 3];
	glm::mat4 rot_mat;
	glm::vec4 front_vec;

	memcpy(ode_rot_mat, GetRotation(), sizeof(ode_rot_mat));

	front_vec[0] = 1;
	front_vec[1] = 0;
	front_vec[2] = 0;
	front_vec[3] = 0;

	rot_mat[0] = { ode_rot_mat[0], ode_rot_mat[1], ode_rot_mat[2], 0 };
	rot_mat[1] = { ode_rot_mat[4], ode_rot_mat[5], ode_rot_mat[6], 0 };
	rot_mat[2] = { ode_rot_mat[8], ode_rot_mat[9], ode_rot_mat[10], 0 };

	front_vec = rot_mat * front_vec;

	dx = front_vec[0];
	dy = front_vec[1];
	dz = front_vec[2];
}

void Physics::GetRotationAngles(FLOATING &rx, FLOATING &ry, FLOATING &rz) const
{
	FLOATING dir_x, dir_y, dir_z;
	GetDirection(dir_x, dir_y, dir_z);
	rx = atan2(dir_z, dir_y);
	ry = atan2(dir_x, dir_z);
	rz = atan2(dir_y, dir_x);
}

PhysicsSimple PhysicsSimple::MakePlane(dSpaceID space)
{
	PhysicsSimple result;
	result.geom.reset(dCreatePlane(space, 0, 0, 1, 0));
	result.body = nullptr;
	return result;
}

PhysicsSimple PhysicsSimple::MakeBox(
			dWorldID world, dSpaceID space,
			FLOATING mass,
			FLOATING x, FLOATING y, FLOATING z,
			FLOATING lx, FLOATING ly, FLOATING lz)
{
	PhysicsSimple result;

	dMass dm;
	dMassSetBoxTotal(&dm, mass, lx, ly, lz);

	result.body.reset(dBodyCreate(world));
	dBodySetPosition(result.body.get(), x, y, z);
	dBodySetMass(result.body.get(), &dm);

	result.geom.reset(dCreateBox(space, lx, ly, lz));
	dGeomSetBody(result.geom.get(), result.body.get());

	return result;
}

PhysicsCar::PhysicsCar(
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

bool PhysicsCar::HasTrack(dBodyID maybe_track) const
{
	return ltrack_body.get() == maybe_track || rtrack_body.get() == maybe_track;
}

}
