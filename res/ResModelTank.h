#ifndef RES_MODEL_TANK_H
#define RES_MODEL_TANK_H

#include <vector>
#include <map>
#include <string>

#include "Common.h"
#include "ResShaderTank.h"

namespace res {

struct ResModelTank {
    std::map<std::string, std::vector<ResShaderTank::Vertex>> vertexes;
    std::map<std::string, glm::vec3> joints;

    std::vector<ResShaderTank::Vertex> GetAllVertexes() const; // tODO: Implement
};

}

#endif
