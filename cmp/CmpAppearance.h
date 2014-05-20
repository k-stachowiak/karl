#ifndef CMP_APPEARANCE_H
#define CMP_APPEARANCE_H

#include <vector>
#include "common.h"

namespace cmp {

struct CmpAppearance {

    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec3> colors;

    static CmpAppearance MakeFlat(
        int lx, int ly,
        FLOATING r, FLOATING g, FLOATING b,
        FLOATING (*altitude)(int, int));

    static CmpAppearance MakeBox(
        FLOATING lx, FLOATING ly, FLOATING lz,
        FLOATING r, FLOATING g, FLOATING b);

    static CmpAppearance MakeCar();

    unsigned GetVertexCount() const { return vertexes.size(); }
};

}

#endif

