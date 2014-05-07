#ifndef CMP_H
#define CMP_H

#include <memory>
#include <vector>

#include <ode/ode.h>

#include "auto.h"
#include "common.h"

/*
 * Components module.
 *
 * This module defines the components that can build up an entity.
 * The different component types corresponds to the basic aspects of the
 * game simulations. The main assumption is:
 *
 * - The components encapsulate the given aspect strongly.
 */



namespace cmp {

struct Appearance {

	std::vector<Vec3> vertexes;
	std::vector<Vec3> colors;

	static Appearance MakeFlat(
		int lx, int ly,
		FLOATING r, FLOATING g, FLOATING b,
		FLOATING (*altitude)(int, int));

	static Appearance MakeBox(
		FLOATING lx, FLOATING ly, FLOATING lz,
		FLOATING r, FLOATING g, FLOATING b);

	static Appearance MakeCar();

	unsigned GetVertexCount() const { return vertexes.size(); }
};

struct Physics {
	virtual ~Physics() {}

	virtual bool HasBody() const = 0;
	virtual const FLOATING *GetLocation() const = 0;
	virtual const FLOATING *GetRotation() const = 0;

	virtual bool HasTrack(dBodyID new_maybe_track) const { return false; }

	void GetDirection(FLOATING &dx, FLOATING &dy, FLOATING &dz) const;
	void GetRotationAngles(FLOATING &rx, FLOATING &ry, FLOATING &rz) const;
};

struct PhysicsSimple : public Physics {

	OdeBody body;
	OdeGeom geom;

	static PhysicsSimple MakePlane(dSpaceID space);
	static PhysicsSimple MakeBox(
		dWorldID world, dSpaceID space,
		FLOATING mass,
		FLOATING x, FLOATING y, FLOATING z,
		FLOATING lx, FLOATING ly, FLOATING lz);

	bool HasBody() const { return (bool)body; }
	const FLOATING *GetLocation() const { return dBodyGetPosition(body.get()); }
	const FLOATING *GetRotation() const { return dBodyGetRotation(body.get()); }
};

struct PhysicsCar : public Physics {

	OdeBody chassis_body;
	OdeGeom chassis_geom;
	OdeBody rtrack_body;
	OdeGeom rtrack_geom;
	OdeBody ltrack_body;
	OdeGeom ltrack_geom;
	OdeJoint rjoint;
	OdeJoint ljoint;

	PhysicsCar(
		dWorldID world, dSpaceID space,
		FLOATING cx, FLOATING cy, FLOATING cz);

	bool HasTrack(dBodyID maybe_track) const;

	bool HasBody() const { return true; }
	const FLOATING *GetLocation() const { return dBodyGetPosition(chassis_body.get()); }
	const FLOATING *GetRotation() const { return dBodyGetRotation(chassis_body.get()); }

	dBodyID GetLTrackBody() const { return ltrack_body.get(); }
	dBodyID GetRTrackBody() const { return rtrack_body.get(); }
};

}

#endif
