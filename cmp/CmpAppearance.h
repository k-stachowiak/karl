#ifndef CMP_APPEARANCE_H
#define CMP_APPEARANCE_H

#include <vector>
#include "Common.h"

namespace cmp {

struct CmpAppearance {

    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec3> colors;

    static CmpAppearance MakeBox(
        FLOATING lx, FLOATING ly, FLOATING lz,
        FLOATING r, FLOATING g, FLOATING b);

    static CmpAppearance MakeCar();

    unsigned GetVertexCount() const { return vertexes.size(); }
};

}

#endif

