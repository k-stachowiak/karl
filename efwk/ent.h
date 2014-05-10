#ifndef ENT_H
#define ENT_H

#include <ode/ode.h>

#include "common.h"
#include "cmp.h"
#include "sys_drawing.h"
#include "sys_physics.h"

struct EntGround {
	long id;
	cmp::PhysicsSimple phys;
	cmp::Appearance appr;

	EntGround(dWorldID world, dSpaceID space);
	sys::NdDrawing MakeDrawingNode();
	sys::NdPhysics MakePhysicsNode();
};

struct EntTank {
	long id;
	cmp::PhysicsCar phys;
	cmp::Appearance appr;

	EntTank(dWorldID world, dSpaceID space);
	sys::NdDrawing MakeDrawingNode();
	sys::NdPhysics MakePhysicsNode();
};

#endif
