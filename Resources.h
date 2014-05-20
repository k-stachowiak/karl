#ifndef RESOURCES_H
#define RESOURCES_H

#include <memory>

#include <allegro5/allegro_opengl.h>

#include "Auto.h"

class Shader {

    static void m_PrintShaderErrorLog(GLuint shader);
    static void m_PrintProgramErrorLog(GLuint program);

public:
    GLuint vshader;
    GLuint fshader;
    GLuint program;
    GLint coord_loc, color_loc;
    GLint model_loc, view_loc, projection_loc;

    Shader(const std::string& vsource, const std::string& fsource);
    ~Shader();
};

struct Resources {
    std::unique_ptr<Shader> res_simple_shader;
    Resources();
    ~Resources();
};

#endif
