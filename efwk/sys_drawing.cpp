#include <cstdio>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#include "common.h"
#include "config.h"
#include "sys_drawing.h"
#include "resources.h"

/* Camera management.
 * ==================
 */

namespace sys {

Drawing::Camera::Camera() :
	location { 0, 0, -0.5f },
	rotation { 0, 0, 0 },
	view {},
	projection {
		glm::perspective(
			cfg_cam_fovy,
			cfg_screen_w / cfg_screen_h,
			cfg_cam_near,
			cfg_cam_far) }
{}

void Drawing::m_CameraUpdateViewMatrix()
{
	m_camera.view = glm::mat4{};
	m_camera.view = glm::rotate(m_camera.view, m_camera.rotation[0], glm::vec3 { 1, 0, 0 });
	m_camera.view = glm::rotate(m_camera.view, m_camera.rotation[1], glm::vec3 { 0, 1, 0 });
	m_camera.view = glm::rotate(m_camera.view, -3.1415f / 2, glm::vec3 { 1, 0, 0 });
	m_camera.view = glm::translate(m_camera.view, m_camera.location);
}

void Drawing::m_CameraApply(const Shader &shader)
{
	glUniformMatrix4fv(shader.view_loc, 1, GL_FALSE, glm::value_ptr(m_camera.view));
	glUniformMatrix4fv(shader.projection_loc, 1, GL_FALSE, glm::value_ptr(m_camera.projection));
}

void Drawing::m_ShaderBegin(const Shader &shader)
{
	glUseProgram(shader.program);
	glEnableVertexAttribArray(shader.coord_loc);
	glEnableVertexAttribArray(shader.color_loc);
}

void Drawing::m_ShaderEnd(const Shader &shader)
{
	glDisableVertexAttribArray(shader.coord_loc);
	glDisableVertexAttribArray(shader.color_loc);
}

void Drawing::m_FrameBegin()
{
	glViewport(0, 0, cfg_screen_w, cfg_screen_h);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Drawing::m_FrameEnd()
{
}

void Drawing::m_ComputeModelMatrix(const NdDrawing& node, glm::mat4& model)
{
	FLOATING location[3];
	FLOATING rotation[3 * 4];

	if (node.phys->HasBody()) {
		memcpy(location, node.phys->GetLocation(), sizeof(location));
		memcpy(rotation, node.phys->GetRotation(), sizeof(rotation));
		model[0][0] = rotation[0];
		model[0][1] = rotation[4];
		model[0][2] = rotation[8];
		model[0][3] = 0;
		model[1][0] = rotation[1];
		model[1][1] = rotation[5];
		model[1][2] = rotation[9];
		model[1][3] = 0;
		model[2][0] = rotation[2];
		model[2][1] = rotation[6];
		model[2][2] = rotation[10];
		model[2][3] = 0;
		model[3][0] = location[0];
		model[3][1] = location[1];
		model[3][2] = location[2];
		model[3][3] = 1;
	} else {
		model = glm::mat4{};
	}
}

void Drawing::m_DrawMesh(const Shader& shader, const NdDrawing& node)
{
	glm::mat4 model;
	m_ComputeModelMatrix(node, model);

	glUniformMatrix4fv(shader.model_loc, 1, GL_FALSE, glm::value_ptr(model));
	glVertexAttribPointer(shader.coord_loc, 3, GL_FLOAT, GL_FALSE, 0, &node.appr->vertexes[0]);
	glVertexAttribPointer(shader.color_loc, 3, GL_FLOAT, GL_FALSE, 0, &node.appr->colors[0]);

	glDrawArrays(GL_TRIANGLES, 0, node.appr->GetVertexCount());
}

/* API implementation.
 * ===================
 */

Drawing::Drawing(Resources& resources) :
	m_resources(resources)
{
	m_CameraUpdateViewMatrix();
}

void Drawing::CameraMove(FLOATING dx, FLOATING dy, FLOATING dz)
{
	m_camera.location[0] -= dx;
	m_camera.location[1] -= dy;
	m_camera.location[2] -= dz;
	m_CameraUpdateViewMatrix();
}

void Drawing::CameraWalk(FLOATING front, FLOATING side)
{
	FLOATING dx, dy;
	cast_rotated_coords(front, side, m_camera.rotation[1], dx, dy);
	CameraMove(dx, dy, 0);
}

void Drawing::CameraRotate(FLOATING pitch, FLOATING yaw, FLOATING roll)
{
	m_camera.rotation[0] -= pitch;
	m_camera.rotation[1] -= yaw;
	m_camera.rotation[2] -= roll;
	m_CameraUpdateViewMatrix();
}

void Drawing::Perform()
{
	m_FrameBegin();
	m_ShaderBegin(*m_resources.res_simple_shader);
	m_CameraApply(*m_resources.res_simple_shader);

	for (auto& node : m_nodes) {
		m_DrawMesh(*m_resources.res_simple_shader, node);
	}

	m_ShaderEnd(*m_resources.res_simple_shader);
	m_FrameEnd();
}

}
