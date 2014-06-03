#ifndef RES_MODEL_LOADER_H
#define RES_MODEL_LOADER_H

#include <string>
#include <vector>
#include <map>

#include "Common.h"
#include "ResModelTank.h"
#include "ResShaderTank.h"

namespace res {

class ResModelLoader {

    struct ObjTankObject {
        std::vector<glm::vec3> vertexes;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> tex_coords;
        bool HasTexCoord() const { return !tex_coords.empty(); }
    };

    struct VertexesBag {
        std::vector<glm::vec3> vertexes;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> tex_coords;
    };

    struct FacesBag {
        std::vector<glm::ivec2> faces2;
        std::vector<glm::ivec3> faces3;
        void Clear() { faces2.clear(); faces3.clear(); }
        bool TwoProps() const { return !faces2.empty() && faces3.empty(); }
        bool ThreeProps() const { return faces2.empty() && !faces3.empty(); }
    };

    static ResModelTank m_CombineObjTankObjects(
        const std::map<std::string, ObjTankObject>& obj_map);

    static ObjTankObject m_BuildObjTankObject(
        const VertexesBag& v_bag,
        const FacesBag& f_bag);

    static std::map<std::string, ObjTankObject> m_LoadObjTankObjects(
        std::vector<std::string>::iterator first,
        std::vector<std::string>::iterator last);

public:
    static ResModelTank LoadObjTankModel(const std::string& source);
};

}

#endif
