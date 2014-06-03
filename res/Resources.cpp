
#include <allegro5/allegro_ttf.h>

#include "Diagnostics.h"
#include "Resources.h"
#include "ResModelLoader.h"
#include "File.h"

namespace res {

Resources::Resources() :
    res_debug_shader { new ResShaderDebug },
    res_tank_shader { new ResShaderTank },
    res_tank_texture { new ResTexture { "data/tank2.png" } },
    res_tank_model { new ResModelTank(
        ResModelLoader::LoadObjTankModel(g_ReadFile("data/tank.obj"))
    )}
{}

}
