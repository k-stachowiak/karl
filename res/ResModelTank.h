#ifndef RES_MODEL_TANK_H
#define RES_MODEL_TANK_H

#include <vector>
#include <map>
#include <string>

#include "Common.h"
#include "ResShaderTank.h"

namespace res {

struct ResModelTank {

    enum class Piece {
        BODY,
        LTRACK,
        RTRACK,
        MUZZLE,
        TURRET,
        JOINT_MUZZLE,
        JOINT_TURRET,
        COL_CHASSIS,
        COL_LTRACK,
        COL_RTRACK
    };

    static std::map<std::string, Piece> stringPieceMap;
    static std::map<Piece, std::string> pieceStringMap;

    std::map<Piece, std::vector<ResShaderTank::Vertex>> vertexes;
    std::map<Piece, std::vector<glm::vec3>> coll_geoms;
    std::map<Piece, glm::vec3> joints;

    std::vector<ResShaderTank::Vertex> GetAllVertexes() const;
};

}

#endif
