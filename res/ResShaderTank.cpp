#include "File.h"
#include "ResShaderTank.h"

namespace res {

ResShaderTank::ResShaderTank() :
    ResShader(g_ReadFile("data/tank.vs"), g_ReadFile("data/tank.fs")),
    coord_loc { glGetAttribLocation(program, "attr_coord") },
    tex_coord_loc { glGetAttribLocation(program, "attr_tex_coord") }
{
    t_AssertLocations(coord_loc, tex_coord_loc);
}

}
