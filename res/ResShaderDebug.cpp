#include "File.h"
#include "ResShaderDebug.h"

namespace res {

ResShaderDebug::ResShaderDebug() :
    ResShader(g_ReadFile("data/debug.vs"), g_ReadFile("data/debug.fs")),
    coord_loc { glGetAttribLocation(program, "attr_coord") },
    color_loc { glGetAttribLocation(program, "attr_color") }
{
    if (coord_loc == -1 || color_loc == -1) {
        DIAG_ERROR_EXIT("Failed finding locations in GLSL program.\n");
    }
}

}
