#ifndef SYS_DRAWING_H
#define SYS_DRAWING_H

#include <vector>

#include "common.h"
#include "resources.h"
#include "cmp.h"

namespace sys {

struct NdDrawing {
	long id;
	cmp::Physics *phys;
	cmp::Appearance *appr;
};

class Drawing {

	Resources& m_resources;

	std::vector<NdDrawing> m_nodes;

	struct Camera {
		glm::vec3 location;
		glm::vec3 rotation;
		glm::mat4 view;
		glm::mat4 projection;
		Camera();
	} m_camera;

	void m_CameraUpdateViewMatrix();
	void m_CameraApply(const Shader &shader);

	static void m_ShaderBegin(const Shader &shader);
	static void m_ShaderEnd(const Shader &shader);

	static void m_FrameBegin();
	static void m_FrameEnd();

	static void m_ComputeModelMatrix(const NdDrawing& node, glm::mat4& model);
	static void m_DrawMesh(const Shader &shader, const NdDrawing& node);

public:
	Drawing(Resources& resources);

	void AddNode(const NdDrawing& node) { m_nodes.push_back(node); }

	void CameraMove(FLOATING dx, FLOATING dy, FLOATING dz);
	void CameraWalk(FLOATING front, FLOATING side);
	void CameraRotate(FLOATING pitch, FLOATING yaw, FLOATING roll);

	void Perform();
};

}

#endif
