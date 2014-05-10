#include <cstdio>
#include <array>

#include <allegro5/allegro_ttf.h>

#include "diagnostics.h"
#include "resources.h"

namespace {

const char *g_simple_vsource =
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
//	"    gl_Position = vec4(attr_coord, 1.0) * uni_model * uni_view * uni_projection;\n"
	"}";

const char *g_simple_fsource =
	"#version 330\n"
	"in vec3 frag_color;\n"
	"void main(void) {\n"
	"    gl_FragColor = vec4(frag_color, 1.0);\n"
	"}";

}

void Shader::m_PrintShaderErrorLog(GLuint shader)
{
	GLint log_size;
	char *log_buffer;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
	log_buffer = (char*)malloc(log_size);

	glGetShaderInfoLog(shader, log_size, &log_size, log_buffer);
	fprintf(stderr, "Shader error : %s\n", log_buffer);

	free(log_buffer);
}

void Shader::m_PrintProgramErrorLog(GLuint program)
{
	GLint log_size;
	char *log_buffer;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
	log_buffer = (char*)malloc(log_size);

	glGetProgramInfoLog(program, log_size, &log_size, log_buffer);
	fprintf(stderr, "Shader error : %s\n", log_buffer);

	free(log_buffer);
}

Shader::Shader(const std::string& vsource, const std::string& fsource)
{
	GLint result;

	const char *vsource_array[1] { vsource.c_str() };
	const char *fsource_array[1] { fsource.c_str() };

	vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, vsource_array, NULL);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &result);
	if (!result) {
		m_PrintShaderErrorLog(vshader);
		glDeleteShader(vshader);
		DIAG_ERROR_EXIT("Failed initializing GLSL vertex shader.\n");
	}

	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, fsource_array, NULL);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &result);
	if (!result) {
		m_PrintShaderErrorLog(fshader);
		glDeleteShader(vshader);
		glDeleteShader(fshader);
		DIAG_ERROR_EXIT("Failed initializing GLSL fragment shader.\n");
	}

	program = glCreateProgram();
	glAttachShader(program, vshader);
	glAttachShader(program, fshader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (!result) {
		m_PrintProgramErrorLog(program);
		glDeleteShader(vshader);
		glDeleteShader(fshader);
		glDeleteProgram(program);
		DIAG_ERROR_EXIT("Failed initializing GLSL program.\n");
	}

	glDetachShader(program, vshader);
	glDetachShader(program, fshader);

	coord_loc = glGetAttribLocation(program, "attr_coord");
	color_loc = glGetAttribLocation(program, "attr_color");
	model_loc = glGetUniformLocation(program, "uni_model");
	view_loc = glGetUniformLocation(program, "uni_view");
	projection_loc = glGetUniformLocation(program, "uni_projection");

	if (coord_loc == -1 ||
		color_loc == -1 ||
		model_loc == -1 ||
		view_loc == -1 ||
		projection_loc == -1) {
			DIAG_ERROR_EXIT("Failed finding locations in GLSL program.\n");
	}
}

Shader::~Shader()
{
	glDeleteShader(vshader);
	glDeleteShader(fshader);
	glDeleteProgram(program);
}

Resources::Resources() :
	res_font_big { al_load_font("data/prstartk.ttf", -30, 0) },
	res_simple_shader { new Shader { g_simple_vsource, g_simple_fsource } }
{
	if (!res_font_big) {
		DIAG_ERROR_EXIT("Failed loading font.\n");
	}
}

Resources::~Resources()
{
}
