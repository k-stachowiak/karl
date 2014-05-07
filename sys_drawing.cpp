#include <cstdio>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#include "config.h"
#include "sys.h"
#include "resources.h"

/* Camera management.
 * ==================
 */

namespace sys {

void Drawing::m_CameraInit()
{
	camera.location.data[0] = 0;
	camera.location.data[1] = 0;
	camera.location.data[2] = -0.5;
	camera.rotation.data[0] = 0;
	camera.rotation.data[1] = 0;
	camera.rotation.data[2] = 0;
	m_CameraUpdateViewMatrix();

	mat4_identity(camera.projection);
	mat4_perspective(
		camera.projection,
		cfg_cam_fovy,
		cfg_screen_w / cfg_screen_h,
		cfg_cam_near,
		cfg_cam_far);
}

void Drawing::m_CameraUpdateViewMatrix()
{
	mat4_identity(camera.view);
	mat4_translatev(camera.view, camera.location);
	mat4_rotate_x(camera.view, 3.1415 / 2);
	mat4_rotate_y(camera.view, camera.rotation.data[1]);
	mat4_rotate_x(camera.view, camera.rotation.data[0]);
}

void Drawing::m_CameraApply(const Shader &shader)
{
	glUniformMatrix4fv(shader.view_loc, 1, GL_FALSE, camera.view.data);
	glUniformMatrix4fv(shader.projection_loc, 1, GL_FALSE, camera.projection.data);
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

void Drawing::m_ComputeModelMatrix(const NdDrawing& node, Mat4& model)
{
	FLOATING location[3];
	FLOATING rotation[3 * 4];

	if (node.phys->HasBody()) {
		memcpy(location, node.phys->GetLocation(), sizeof(location));
		memcpy(rotation, node.phys->GetRotation(), sizeof(rotation));
		model.data[0] =  rotation[0];
		model.data[1] =  rotation[4];
		model.data[2] =  rotation[8];
		model.data[3] =  0;
		model.data[4] =  rotation[1];
		model.data[5] =  rotation[5];
		model.data[6] =  rotation[9];
		model.data[7] =  0;
		model.data[8] =  rotation[2];
		model.data[9] =  rotation[6];
		model.data[10] = rotation[10];
		model.data[11] = 0;
		model.data[12] = location[0];
		model.data[13] = location[1];
		model.data[14] = location[2];
		model.data[15] = 1;
	} else {
		mat4_identity(model);
	}
}

void Drawing::m_DrawMesh(const Shader& shader, const NdDrawing& node)
{
	struct Mat4 model;
	m_ComputeModelMatrix(node, model);

	glUniformMatrix4fv(shader.model_loc, 1, GL_FALSE, model.data);
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
	m_CameraInit();
}

void Drawing::CameraMove(FLOATING dx, FLOATING dy, FLOATING dz)
{
	camera.location.data[0] -= dx;
	camera.location.data[1] -= dy;
	camera.location.data[2] -= dz;
	m_CameraUpdateViewMatrix();
}

void Drawing::CameraWalk(FLOATING front, FLOATING side)
{
	FLOATING dx, dy;
	cast_rotated_coords(front, side, camera.rotation.data[1], dx, dy);
	CameraMove(dx, dy, 0);
}

void Drawing::CameraRotate(FLOATING pitch, FLOATING yaw, FLOATING roll)
{
	camera.rotation.data[0] -= pitch;
	camera.rotation.data[1] -= yaw;
	camera.rotation.data[2] -= roll;
	m_CameraUpdateViewMatrix();
}

void Drawing::Perform()
{
	m_FrameBegin();
	m_ShaderBegin(m_resources.res_simple_shader);
	m_CameraApply(m_resources.res_simple_shader);

	for (auto& node : nodes) {
		m_DrawMesh(m_resources.res_simple_shader, node);
	}

	m_ShaderEnd(m_resources.res_simple_shader);
	m_FrameEnd();
}

}
