#include <algorithm>

#include "GeomFac.h"

namespace {

static glm::vec3 cube[36] = {

    /* To the front! */
    { -1, -1, +1 },
    { -1, +1, +1 },
    { +1, +1, +1 },
    { -1, -1, +1 },
    { +1, +1, +1 },
    { +1, -1, +1 },

    /* To the back! */
    { +1, -1, -1 },
    { +1, +1, -1 },
    { -1, +1, -1 },
    { +1, -1, -1 },
    { -1, +1, -1 },
    { -1, -1, -1 },

    /* To the right! */
    { +1, -1, +1 },
    { +1, +1, +1 },
    { +1, +1, -1 },
    { +1, -1, +1 },
    { +1, +1, -1 },
    { +1, -1, -1 },

    /* To the left! */
    { -1, -1, -1 },
    { -1, +1, -1 },
    { -1, +1, +1 },
    { -1, -1, -1 },
    { -1, +1, +1 },
    { -1, -1, +1 },

    /* To the bottom! */
    { -1, -1, -1 },
    { -1, -1, +1 },
    { +1, -1, +1 },
    { -1, -1, -1 },
    { +1, -1, +1 },
    { +1, -1, -1 },

    /* To the top! */
    { -1, +1, +1 },
    { -1, +1, -1 },
    { +1, +1, -1 },
    { -1, +1, +1 },
    { +1, +1, -1 },
    { +1, +1, +1 },
};

std::vector<glm::vec3> g_MakeFlat(int lx, int ly)
{
    std::vector<glm::vec3> result;
    for (int i = 0; i < lx; ++i) {
        for (int j = 0; j < ly; ++j) {
            const FLOATING base_x = (FLOATING)i + 0.5;
            const FLOATING base_y = (FLOATING)j + 0.5;
            result.push_back(glm::vec3 { base_x - 0.5f, base_y - 0.5f, 0 } );
            result.push_back(glm::vec3 { base_x - 0.5f, base_y + 0.5f, 0 } );
            result.push_back(glm::vec3 { base_x + 0.5f, base_y + 0.5f, 0 } );
            result.push_back(glm::vec3 { base_x - 0.5f, base_y - 0.5f, 0 } );
            result.push_back(glm::vec3 { base_x + 0.5f, base_y + 0.5f, 0 } );
            result.push_back(glm::vec3 { base_x + 0.5f, base_y - 0.5f, 0 } );
        }
    }
    return result;
}

}

std::vector<cmp::VtxDebug> g_GenerateGroundDebugVertexes(
        int lx, int ly,
        FLOATING r, FLOATING g, FLOATING b)
{
    std::vector<cmp::VtxDebug> result;

    auto raw_vertexes = g_MakeFlat(lx, ly);

    for (const auto& v : raw_vertexes) {
        auto found = std::find_if(
                begin(result), end(result),
                [&v](const cmp::VtxDebug& outv) {
            return outv.attr_location == v;
        });
        if (found == end(result)) {
            result.push_back({ v, { r, g, b } });
        }
    }

    return result;
}

std::vector<unsigned> g_GenerateGroundDebugIndexes(int lx, int ly)
{
    std::vector<glm::vec3> raw_vertexes = g_MakeFlat(lx, ly);
    std::vector<glm::vec3> packed_vertexes;
    std::vector<unsigned> result;

    for (const auto& v : raw_vertexes) {
        auto found = std::find(begin(packed_vertexes), end(packed_vertexes), v);
        if (found == end(packed_vertexes)) {
            result.push_back(packed_vertexes.size());
            packed_vertexes.push_back(v);
        } else {
            result.push_back(std::distance(begin(packed_vertexes), found));
        }
    }

    return result;
}
