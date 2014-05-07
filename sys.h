#ifndef SYS_H
#define SYS_H

#include <vector>

#include <ode/ode.h>

#include "auto.h"
#include "cmp.h"
#include "resources.h"

namespace sys {

struct NdDrawing {
	long id;
	cmp::Physics *phys;
	cmp::Appearance *appr;
};

class Drawing {

	Resources& m_resources;

	void m_CameraInit();
	void m_CameraUpdateViewMatrix();
	void m_CameraApply(const Shader &shader);

	void m_ShaderBegin(const Shader &shader);
	void m_ShaderEnd(const Shader &shader);

	void m_FrameBegin();
	void m_FrameEnd();

	void m_ComputeModelMatrix(const NdDrawing& node, Mat4& model);
	void m_DrawMesh(const Shader &shader, const NdDrawing& node);

public:
	std::vector<NdDrawing> nodes;

	struct {
		Vec3 location;
		Vec3 rotation;
		Mat4 view;
		Mat4 projection;
	} camera;

	Drawing(Resources& resources);

	void CameraMove(FLOATING dx, FLOATING dy, FLOATING dz);
	void CameraWalk(FLOATING front, FLOATING side);
	void CameraRotate(FLOATING pitch, FLOATING yaw, FLOATING roll);

	void Perform();
};

struct NdPhysics {
	long id;
	cmp::Physics *phys;
};

class Physics {

	OdeWorld m_world;
	OdeSpace m_space;
	OdeJointGroup m_contact_group;

	struct HasTrack {
		dBodyID maybe_track;
		HasTrack(dBodyID new_maybe_track) : maybe_track { new_maybe_track } {}
		bool operator()(const NdPhysics& node)
		{
			return node.phys->HasTrack(maybe_track);
		}
	};

	// TODO: Make static all functions that don't depend on the state.
	static void m_ComputeFDir1(
		FLOATING dir_x, FLOATING dir_y,
		FLOATING nor_x, FLOATING nor_y, FLOATING nor_z,
		FLOATING &fdir1_x, FLOATING &fdir1_y, FLOATING &fdir1_z);

	void m_OnTrackNonTrackContact(
		dBodyID track, struct NdPhysics track_node,
		dBodyID nontrack, dContact &contact);

	void m_OnDefaultContact(dBodyID b1, dBodyID b2, dContact &contact);

public:
	// TODO: Encapsulate these.
	std::vector<NdPhysics> nodes;

	Physics();
	~Physics();

	void Perform(double dt);

	void OnCollision(dGeomID geom_1, dGeomID geom_2);

	dWorldID GetWorld() const;
	dSpaceID GetSpace() const;
};

}

#endif
