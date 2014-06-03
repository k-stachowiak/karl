#include <algorithm>
#include <iterator>

#include "ResModelTank.h"

namespace res {

std::vector<ResShaderTank::Vertex> ResModelTank::GetAllVertexes() const
{
    std::vector<ResShaderTank::Vertex> result;

    for (const auto& pr : vertexes) {
        std::copy(begin(pr.second), end(pr.second), std::back_inserter(result));
    }

    return result;
}

}
