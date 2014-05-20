#include <algorithm>
#include <iterator>

#include "Config.h"
#include "CmpAppearance.h"

namespace cmp {

static glm::vec3 verbose_cube_definition[36] = {

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

CmpAppearance CmpAppearance::MakeFlat(
        int lx, int ly,
        FLOATING r, FLOATING g, FLOATING b,
        FLOATING (*altitude)(int, int))
{
    CmpAppearance result;

    for (int i = 0; i < lx; ++i) {
        for (int j = 0; j < ly; ++j) {

            const FLOATING base_x = (FLOATING)i + 0.5;
            const FLOATING base_y = (FLOATING)j + 0.5;

            result.vertexes.push_back(glm::vec3 { base_x - 0.5f, base_y - 0.5f, altitude(i, j) });
            result.vertexes.push_back(glm::vec3 { base_x - 0.5f, base_y + 0.5f, altitude(i, j + 1) });
            result.vertexes.push_back(glm::vec3 { base_x + 0.5f, base_y + 0.5f, altitude(i + 1, j + 1) });
            result.vertexes.push_back(glm::vec3 { base_x - 0.5f, base_y - 0.5f, altitude(i, j) });
            result.vertexes.push_back(glm::vec3 { base_x + 0.5f, base_y + 0.5f, altitude(i + 1, j + 1) });
            result.vertexes.push_back(glm::vec3 { base_x + 0.5f, base_y - 0.5f, altitude(i + 1, j) });

            result.colors.push_back(glm::vec3 { r, g, b });
            result.colors.push_back(glm::vec3 { r, g, b });
            result.colors.push_back(glm::vec3 { r, g, b });
            result.colors.push_back(glm::vec3 { r, g, b });
            result.colors.push_back(glm::vec3 { r, g, b });
            result.colors.push_back(glm::vec3 { r, g, b });
        }
    }

    return result;
}

CmpAppearance CmpAppearance::MakeBox(
        FLOATING lx, FLOATING ly, FLOATING lz,
        FLOATING r, FLOATING g, FLOATING b)
{
    CmpAppearance result;

    std::copy(
        verbose_cube_definition,
        verbose_cube_definition + 36,
        std::back_inserter(result.vertexes));

    for (int i = 0; i < 36; ++i) {
        result.vertexes[i][0] *= lx / 2;
        result.vertexes[i][1] *= ly / 2;
        result.vertexes[i][2] *= lz / 2;
        result.colors.push_back({ r, g, b });
    }

    return result;
}

CmpAppearance CmpAppearance::MakeCar()
{
    const FLOATING clx = cfg_chassis_lx;
    const FLOATING cly = cfg_chassis_ly;
    const FLOATING clz = cfg_chassis_lz;
    const FLOATING tlx = cfg_track_lx;
    const FLOATING tly = cfg_track_ly;
    const FLOATING tlz = cfg_track_lz;

    CmpAppearance result;

    /* Build chassis. */

    std::copy(
        verbose_cube_definition,
        verbose_cube_definition + 36,
        std::back_inserter(result.vertexes));

    for (int i = 0; i < 36; ++i) {
        result.vertexes[i][0] *= clx / 2;
        result.vertexes[i][1] *= cly / 2;
        result.vertexes[i][2] *= clz / 2;
        result.colors.push_back({ 0.25, 0, 0 });
    }

    /* Build track. */

    std::copy(
        verbose_cube_definition,
        verbose_cube_definition + 36,
        std::back_inserter(result.vertexes));

    for (int i = 36; i < 72; ++i) {
        result.vertexes[i][0] *= tlx / 2;
        result.vertexes[i][1] *= tly / 2;
        result.vertexes[i][2] *= tlz / 2;
        result.vertexes[i][0] += 0;
        result.vertexes[i][1] += cly / 2;
        result.vertexes[i][2] += -clz / 2;
        result.colors.push_back({ 0, 0, 0.25 });
    }

    std::copy(
        verbose_cube_definition,
        verbose_cube_definition + 36,
        std::back_inserter(result.vertexes));

    for (int i = 72; i < 108; ++i) {
        result.vertexes[i][0] *= tlx / 2;
        result.vertexes[i][1] *= tly / 2;
        result.vertexes[i][2] *= tlz / 2;
        result.vertexes[i][0] += 0;
        result.vertexes[i][1] += -cly / 2;
        result.vertexes[i][2] += -clz / 2;
        result.colors.push_back({ 0, 0, 0.25 });
    }

    return result;
}

}

