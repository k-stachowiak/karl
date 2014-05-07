#include <cstdio>

#include <allegro5/allegro_ttf.h>

#include "resources.h"

namespace {

void PrintShaderErrorLog(GLuint shader)
{
	GLint log_size;
	char *log_buffer;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
	log_buffer = (char*)malloc(log_size);

	glGetShaderInfoLog(shader, log_size, &log_size, log_buffer);
	fprintf(stderr, "Shader error : %s\n", log_buffer);

	free(log_buffer);
}

void PrintProgramErrorLog(GLuint program)
{
	GLint log_size;
	char *log_buffer;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
	log_buffer = (char*)malloc(log_size);

	glGetProgramInfoLog(program, log_size, &log_size, log_buffer);
	fprintf(stderr, "Shader error : %s\n", log_buffer);

	free(log_buffer);
}

bool MakeShader(const char *vsource, const char *fsource, struct Shader *shader)
{
	GLint result;

	shader->vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader->vshader, 1, &vsource, NULL);
	glCompileShader(shader->vshader);
	glGetShaderiv(shader->vshader, GL_COMPILE_STATUS, &result);
	if (!result) {
		PrintShaderErrorLog(shader->vshader);
		glDeleteShader(shader->vshader);
		return false;
	}

	shader->fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader->fshader, 1, &fsource, NULL);
	glCompileShader(shader->fshader);
	glGetShaderiv(shader->fshader, GL_COMPILE_STATUS, &result);
	if (!result) {
		PrintShaderErrorLog(shader->fshader);
		glDeleteShader(shader->vshader);
		glDeleteShader(shader->fshader);
		return false;
	}

	shader->program = glCreateProgram();
	glAttachShader(shader->program, shader->vshader);
	glAttachShader(shader->program, shader->fshader);
	glLinkProgram(shader->program);
	glGetProgramiv(shader->program, GL_LINK_STATUS, &result);
	if (!result) {
		PrintProgramErrorLog(shader->program);
		glDeleteShader(shader->vshader);
		glDeleteShader(shader->fshader);
		glDeleteProgram(shader->program);
		return false;
	}

	glDetachShader(shader->program, shader->vshader);
	glDetachShader(shader->program, shader->fshader);

	shader->coord_loc = glGetAttribLocation(shader->program, "attr_coord");
	shader->color_loc = glGetAttribLocation(shader->program, "attr_color");
	shader->model_loc = glGetUniformLocation(shader->program, "uni_model");
	shader->view_loc = glGetUniformLocation(shader->program, "uni_view");
	shader->projection_loc = glGetUniformLocation(shader->program, "uni_projection");

	if (shader->coord_loc == -1 ||
		shader->color_loc == -1 ||
		shader->model_loc == -1 ||
		shader->view_loc == -1 ||
		shader->projection_loc == -1) {
		return false;
	}

	return true;
}

void DestroyShader(struct Shader *shader)
{
	glDeleteShader(shader->vshader);
	glDeleteShader(shader->fshader);
	glDeleteProgram(shader->program);
}

bool MakeSimpleShader(struct Shader *shader)
{
	const char *vsource =
		"#version 330\n"
		"attribute vec3 attr_coord;\n"
		"attribute vec3 attr_color;\n"
		"uniform mat4 uni_model;\n"
		"uniform mat4 uni_view;\n"
		"uniform mat4 uni_projection;\n"
		"out vec3 frag_color;\n"
		"void main(void) {\n"
		"    frag_color = attr_color;\n"
		"    gl_Position = uni_projection * uni_view * uni_model * vec4(attr_coord, 1.0);\n"
		"}";

	const char *fsource =
		"#version 330\n"
		"in vec3 frag_color;\n"
		"void main(void) {\n"
		"    gl_FragColor = vec4(frag_color, 1.0);\n"
		"}";

	return MakeShader(vsource, fsource, shader);
}

}

Resources::Resources() :
	res_font_big { al_load_font("data/prstartk.ttf", -30, 0) }
{
	// TODO: Get rid of these asserts.
	assert(res_font_big);
	assert(MakeSimpleShader(&res_simple_shader));
}

Resources::~Resources()
{
	DestroyShader(&res_simple_shader);
}
