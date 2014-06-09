#include <algorithm>
#include <iterator>

#include "ResModelTank.h"

namespace {

template <class T, class DISCARD>
std::vector<T> g_FlattenMap(const std::map<DISCARD, std::vector<T>>& map)
{
    std::vector<T> result;
    for (const auto& pr : map) {
        std::copy(
            begin(pr.second),
            end(pr.second),
            std::back_inserter(result));
    }
    return result;
}

}

namespace res {

std::map<std::string, ResModelTank::Piece> ResModelTank::stringPieceMap {
    { "Body", ResModelTank::Piece::BODY },
    { "LTrack", ResModelTank::Piece::LTRACK},
    { "RTrack", ResModelTank::Piece::RTRACK},
    { "Muzzle", ResModelTank::Piece::MUZZLE },
    { "Turret", ResModelTank::Piece::TURRET },
    { "jMuzzle", ResModelTank::Piece::JOINT_MUZZLE },
    { "jTurret", ResModelTank::Piece::JOINT_TURRET },
    { "cChassis", ResModelTank::Piece::COL_CHASSIS },
    { "cLTrack", ResModelTank::Piece::COL_LTRACK },
    { "cRTrack", ResModelTank::Piece::COL_RTRACK }
};

std::vector<ResShaderTank::Vertex> ResModelTank::GetAllVertexes() const
{
    return g_FlattenMap(vertexes);
}

std::vector<glm::vec3> ResModelTank::GetAllCollGeoms() const
{
    return g_FlattenMap(coll_geoms);
}

}
