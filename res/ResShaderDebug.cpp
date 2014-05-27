#include "File.h"
#include "ResShaderDebug.h"

namespace res {

ResShaderDebug::ResShaderDebug() :
    ResShader(g_ReadFile("data/debug.vs"), g_ReadFile("data/debug.fs")),
    coord_loc { glGetAttribLocation(program, "attr_coord") },
    color_loc { glGetAttribLocation(program, "attr_color") }
{
    t_AssertLocations(coord_loc, color_loc);
}

}
