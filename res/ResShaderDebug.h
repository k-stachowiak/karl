#ifndef RES_SHADER_DEBUG_H
#define RES_SHADER_DEBUG_H

#include "ResShader.h"

namespace res {

class ResShaderDebug : public ResShader {
public:
    GLint coord_loc;
    GLint color_loc;
    ResShaderDebug();
};

}

#endif
