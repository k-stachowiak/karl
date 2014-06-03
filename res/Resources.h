#ifndef RESOURCES_H
#define RESOURCES_H

#include <memory>

#include "Auto.h"
#include "ResShaderDebug.h"
#include "ResShaderTank.h"
#include "ResModelTank.h"
#include "ResTexture.h"

namespace res {

class Resources {
public:
    // TODO: Y unique ptrz???
    std::unique_ptr<ResShaderDebug> res_debug_shader;
    std::unique_ptr<ResShaderTank> res_tank_shader;
    std::unique_ptr<ResTexture> res_tank_texture;
    std::unique_ptr<ResModelTank> res_tank_model;

    Resources();
};

}

#endif
