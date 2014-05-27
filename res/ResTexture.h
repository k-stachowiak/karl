#ifndef RES_TEXTURE_H
#define RES_TEXTURE_H

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#include "Auto.h"

namespace res {

class ResTexture {
    AlBitmap al_bitmap;
public:
    ResTexture(const std::string& filename);
    GLuint GetGlId() const;
};

}

#endif
