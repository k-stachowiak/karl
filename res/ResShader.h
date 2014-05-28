#ifndef RES_SHADER_H
#define RES_SHADER_H

#include <string>
#include <algorithm>
#include <initializer_list>

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#include "Diagnostics.h"

namespace res {

class ResShader {

    GLuint vshader;
    GLuint fshader;

    static void m_PrintShaderErrorLog(GLuint shader);
    static void m_PrintProgramErrorLog(GLuint program);

    void m_LoadSources(const std::string& vsource, const std::string& fsource);
    void m_GetLocations();

protected:
    void t_AssertLocations() {}
    template <class ...T>
    void t_AssertLocations(GLint head, T... tail)
    {
        if (head == -1) {
            DIAG_ERROR_EXIT("Failed getting location from shader.");
        } else {
            t_AssertLocations(tail...);
        }
    }

public:
    GLuint program;
    GLint model_loc, view_loc, projection_loc;

    ResShader(const std::string& vsource, const std::string& fsource);
    ~ResShader();

    virtual void Begin() const = 0;
    virtual void End() const = 0;
};

}

#endif
