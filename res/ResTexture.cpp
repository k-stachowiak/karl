#include "Diagnostics.h"
#include "ResTexture.h"

namespace res {

ResTexture::ResTexture(const std::string& filename) :
    al_bitmap { al_load_bitmap(filename.c_str()) }
{
    DIAG_ASSERT(static_cast<bool>(al_bitmap));

    glBindTexture(GL_TEXTURE_2D, GetGlId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
}

GLuint ResTexture::GetGlId() const
{
    return al_get_opengl_texture(al_bitmap.get());
}

}
