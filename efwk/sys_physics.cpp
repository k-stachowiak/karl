#include <functional>
#include <algorithm>

#include <cassert>

#include "sys_physics.h"

using std::placeholders::_1;

namespace sys {

namespace {
	void g_CollisionCallback(void *data, dGeomID geom_1, dGeomID geom_2)
	{
		Physics* physics = (Physics*)data;
		physics->OnCollision(geom_1, geom_2);
	}
}

void Physics::m_ComputeFDir1(
		FLOATING dir_x, FLOATING dir_y,
		FLOATING nor_x, FLOATING nor_y, FLOATING nor_z,
		FLOATING &fdir1_x, FLOATING &fdir1_y, FLOATING &fdir1_z)
{
	FLOATING inv_len;

	/* Denormalized approximation. */
	fdir1_x = dir_x;
	fdir1_y = dir_y;
	fdir1_z = -(dir_x * nor_x + dir_y * nor_y) / nor_z;

	/* Normalize. */
	inv_len = Q_rsqrt(
		fdir1_x * fdir1_x +
		fdir1_y * fdir1_y +
		fdir1_z * fdir1_z);

	fdir1_x *= inv_len;
	fdir1_y *= inv_len;
	fdir1_z *= inv_len;
}

void Physics::m_OnTrackNonTrackContact(
		dBodyID track, struct NdPhysics track_node,
		dBodyID nontrack, dContact &contact)
{
	FLOATING dir_x, dir_y, dir_z;

	/* Compute the friction 1 direction. */
	track_node.phys->GetDirection(dir_x, dir_y, dir_z);
	m_ComputeFDir1(
		dir_x, dir_y,
		contact.geom.normal[0],
		contact.geom.normal[1],
		contact.geom.normal[2],
		contact.fdir1[0],
		contact.fdir1[1],
		contact.fdir1[2]);

	/* Setup contact surface. */
	contact.surface.mode =
		dContactMu2 |
		dContactSoftERP |
		dContactSoftCFM |
		dContactFDir1;
	contact.surface.mu = 0.75;
	contact.surface.mu2 = 3;
	contact.surface.soft_erp = 1.0;
	contact.surface.soft_cfm = 0.01;

	dJointID contact_joint = dJointCreateContact(
		m_world.get(),
		m_contact_group.get(),
		&contact);

	dJointAttach(contact_joint, track, nontrack);
}

void Physics::m_OnDefaultContact(dBodyID b1, dBodyID b2, dContact &contact)
{
	contact.surface.mode = dContactSoftERP | dContactSoftCFM;
	contact.surface.mu = 1;
	contact.surface.soft_erp = 1.0;
	contact.surface.soft_cfm = 0.001;

	dJointID contact_joint = dJointCreateContact(m_world.get(), m_contact_group.get(), &contact);
	dJointAttach(contact_joint, b1, b2);
}

Physics::Physics()
{
	dInitODE();

	m_world.reset(dWorldCreate());
	dWorldSetGravity(m_world.get(), 0, 0, -10);
	dWorldSetERP(m_world.get(), 0.2);
	dWorldSetCFM(m_world.get(), 10E-5);

	m_space.reset(dSimpleSpaceCreate(0));
	m_contact_group.reset(dJointGroupCreate(0));
}

Physics::~Physics()
{
	m_contact_group.reset();
	m_space.reset();
	m_world.reset();
	dCloseODE();
}

void Physics::OnCollision(dGeomID geom_1, dGeomID geom_2)
{
	const int max_contacts = 5;
	dContact contacts[max_contacts];
	int num_contacts = dCollide(
		geom_1, geom_2,
		max_contacts,
		&contacts[0].geom,
		sizeof(dContact));

	for (int i = 0; i < num_contacts; ++i) {

		dBodyID b1 = dGeomGetBody(contacts[i].geom.g1);
		dBodyID b2 = dGeomGetBody(contacts[i].geom.g2);

		if (dAreConnectedExcluding(b1, b2, dJointTypeContact)) {
			continue;
		}

		auto isTrack1 = [b1](const sys::NdPhysics& nd) { return nd.phys->HasTrack(b1); };
		auto isTrack2 = [b2](const sys::NdPhysics& nd) { return nd.phys->HasTrack(b2); };

		auto physIt1 = std::find_if(begin(m_nodes), end(m_nodes), isTrack1);
		auto physIt2 = std::find_if(begin(m_nodes), end(m_nodes), isTrack2);

		if (physIt1 != end(m_nodes) && physIt2 == end(m_nodes)) {
			m_OnTrackNonTrackContact(b1, *physIt1, b2, contacts[i]);

		} else if (physIt1 == end(m_nodes) && physIt2 != end(m_nodes)) {
			m_OnTrackNonTrackContact(b2, *physIt2, b1, contacts[i]);

		} else {
			m_OnDefaultContact(b1, b2, contacts[i]);

		}
	}
}

void Physics::Perform(double dt)
{
	dSpaceCollide(m_space.get(), this, g_CollisionCallback);
	dWorldStep(m_world.get(), dt);
	dJointGroupEmpty(m_contact_group.get());
}

// TODO: WTF are these getters!?
dWorldID Physics::GetWorld() const
{
	return m_world.get();
}

dSpaceID Physics::GetSpace() const
{
	return m_space.get();
}

}
