#include <algorithm>

#include "Config.h"
#include "GeomFac.h"

namespace {

std::vector<glm::vec3> g_cube {

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

std::vector<glm::vec3> g_MakeCar() {

    const FLOATING clx = cfg_chassis_lx;
    const FLOATING cly = cfg_chassis_ly;
    const FLOATING clz = cfg_chassis_lz;
    const FLOATING tlx = cfg_track_lx;
    const FLOATING tly = cfg_track_ly;
    const FLOATING tlz = cfg_track_lz;

    std::vector<glm::vec3> result;

    /* Build chassis. */

    std::copy(begin(g_cube), end(g_cube), std::back_inserter(result));
    for (int i = 0; i < 36; ++i) {
        result[i][0] *= clx / 2;
        result[i][1] *= cly / 2;
        result[i][2] *= clz / 2;
    }

    /* Build tracks. */

    std::copy(begin(g_cube), end(g_cube), std::back_inserter(result));
    for (int i = 36; i < 72; ++i) {
        result[i][0] *= tlx / 2;
        result[i][1] *= tly / 2;
        result[i][2] *= tlz / 2;
        result[i][0] += 0;
        result[i][1] += cly / 2;
        result[i][2] += -clz / 2;
    }

    std::copy(begin(g_cube), end(g_cube), std::back_inserter(result));
    for (int i = 72; i < 108; ++i) {
        result[i][0] *= tlx / 2;
        result[i][1] *= tly / 2;
        result[i][2] *= tlz / 2;
        result[i][0] += 0;
        result[i][1] += -cly / 2;
        result[i][2] += -clz / 2;
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

std::vector<cmp::VtxDebug> g_GenerateCarDebugVertexes()
{
    std::vector<cmp::VtxDebug> result;

    auto raw_vertexes = g_MakeCar();

    for (unsigned i = 0; i < raw_vertexes.size(); ++i) {
        const auto& v = raw_vertexes[i];
        auto found = std::find_if(
                begin(result), end(result),
                [&v](const cmp::VtxDebug& outv) {
            return outv.attr_location == v;
        });
        if (found == end(result)) {
            if (i < 36) {
                result.push_back({ v, { 0.75f, 0, 0 } });
            } else {
                result.push_back({ v, { 0, 0, 0.75f } });
            }
        }
    }

    return result;
}

std::vector<unsigned> g_GenerateCarDebugIndexes()
{
    std::vector<glm::vec3> raw_vertexes = g_MakeCar();
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

