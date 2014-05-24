#ifndef RES_SHADER_H
#define RES_SHADER_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

namespace res {

class ResShader {

    GLuint vshader;
    GLuint fshader;

    static void m_PrintShaderErrorLog(GLuint shader);
    static void m_PrintProgramErrorLog(GLuint program);

public:
    GLuint program;
    GLint model_loc, view_loc, projection_loc;

    ResShader(const std::string& vsource, const std::string& fsource);
    ~ResShader();
};

}

#endif
