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

template <class K, class V>
std::map<V, K> g_ReverseMap(const std::map<K, V>& in) {
    std::map<V, K> out;
    for (const auto& pr : in) {
        if (out.find(pr.second) != end(out)) {
            DIAG_ERROR_EXIT("Attempt to reverse non-injective map.");
        }
        out[pr.second] = pr.first;
    }
    return out;
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

std::map<ResModelTank::Piece, std::string> ResModelTank::pieceStringMap =
    g_ReverseMap(ResModelTank::stringPieceMap);

std::vector<ResShaderTank::Vertex> ResModelTank::GetAllVertexes() const
{
    return g_FlattenMap(vertexes);
}

}
