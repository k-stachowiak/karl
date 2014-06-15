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

std::vector<glm::vec2> g_cube_tex_coords {
    { 0, 0 }, { 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 1 }, { 1, 0 },
    { 0, 0 }, { 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 1 }, { 1, 0 },
    { 0, 0 }, { 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 1 }, { 1, 0 },
    { 0, 0 }, { 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 1 }, { 1, 0 },
    { 0, 0 }, { 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 1 }, { 1, 0 },
    { 0, 0 }, { 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 1 }, { 1, 0 },
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

std::vector<res::ResShaderDebug::Vertex> g_GenerateGroundDebugVertexes(
        int lx, int ly,
        FLOATING r, FLOATING g, FLOATING b)
{
    std::vector<res::ResShaderDebug::Vertex> result;

    auto raw_vertexes = g_MakeFlat(lx, ly);

    for (const auto& v : raw_vertexes) {
        result.push_back({ v, { r, g, b } });
    }

    return result;
}

std::vector<res::ResShaderDebug::Vertex> g_GenerateCarDebugVertexes()
{
    std::vector<res::ResShaderDebug::Vertex> result;

    auto raw_vertexes = g_MakeCar();

    for (unsigned i = 0; i < raw_vertexes.size(); ++i) {
        if (i < 36) {
            result.push_back({ raw_vertexes[i], { 0.75f, 0, 0 } });
        } else {
            result.push_back({ raw_vertexes[i], { 0, 0, 0.75f } });
        }
    }

    return result;
}

std::vector<res::ResShaderTank::Vertex> g_GenerateCubeVertexes(
        FLOATING lx, FLOATING ly, FLOATING lz)
{
    std::vector<res::ResShaderTank::Vertex> result;

    std::transform(
        begin(g_cube),
        end(g_cube),
        begin(g_cube_tex_coords),
        std::back_inserter(result),
        [](const glm::vec3& c, const glm::vec2& tc) {
            return res::ResShaderTank::Vertex { c, tc };
        });

    std::transform(begin(result), end(result), begin(result),
        [lx, ly, lz](res::ResShaderTank::Vertex v) {
            v.attr_location[0] *= lx * 0.5;
            v.attr_location[1] *= ly * 0.5;
            v.attr_location[2] *= lz * 0.5;
            return v;
        });

    return result;
}

