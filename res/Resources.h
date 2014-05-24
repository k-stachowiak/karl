#ifndef RESOURCES_H
#define RESOURCES_H

#include <memory>

#include "Auto.h"
#include "ResShaderDebug.h"

namespace res {

class Resources {
public:
    std::unique_ptr<ResShaderDebug> res_debug_shader;
    Resources();
};

}

#endif
