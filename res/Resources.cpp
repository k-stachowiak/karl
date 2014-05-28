
#include <allegro5/allegro_ttf.h>

#include "Diagnostics.h"
#include "Resources.h"

namespace res {

Resources::Resources() :
    res_debug_shader { new ResShaderDebug },
    res_tank_shader { new ResShaderTank },
    res_tank_texture { new ResTexture { "data/tank.png" } }
{}

}
