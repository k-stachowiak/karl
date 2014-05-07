#ifndef RESOURCES_H
#define RESOURCES_H

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_opengl.h>

#include "auto.h"

struct Shader {
	GLuint vshader;
	GLuint fshader;
	GLuint program;
	GLint coord_loc, color_loc;
	GLint model_loc, view_loc, projection_loc;

	// TODO: Implement automatic management.
};

struct Resources {
	AlFont res_font_big;
	struct Shader res_simple_shader;
	Resources();
	~Resources();
};

#endif
