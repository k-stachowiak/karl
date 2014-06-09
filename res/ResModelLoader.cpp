#include <cctype>
#include <cassert>
#include <algorithm>
#include <numeric>

#include "Diagnostics.h"
#include "ResModelLoader.h"

namespace {

std::vector<std::string> Explode(const std::string& str, char delim)
{
    auto tip = begin(str);
    auto seam = std::find(begin(str), end(str), delim);

    std::vector<std::string> result;

    while (seam != end(str)) {
        result.emplace_back(tip, seam);
        tip = seam + 1;
        seam = std::find(seam + 1, end(str), delim);
    }

    return result;
}

bool IsSmoothing(const std::string& line)
{
    return line[0] == 's';
}

bool IsComment(const std::string& line)
{
    return line[0] == '#';
}

bool IsObject(const std::string& line, std::string& name)
{
    if (line[0] != 'o') {
        return false;
    }

    char c_name[1024];
    std::sscanf(line.c_str(), "o %s", c_name);
    name = c_name;
    return true;
}

bool IsVertex(const std::string& line, FLOATING& x, FLOATING& y, FLOATING& z)
{
    return std::sscanf(line.c_str(), "v %f %f %f", &x, &y, &z) == 3;
}

bool IsNormal(const std::string& line, FLOATING& x, FLOATING& y, FLOATING& z)
{
    return std::sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z) == 3;
}

bool IsTexCoord(const std::string& line, FLOATING& s, FLOATING& t)
{
    return std::sscanf(line.c_str(), "vt %f %f", &s, &t) == 2;
}

bool IsFace2(const std::string& line,
        unsigned& v0, unsigned& n0,
        unsigned& v1, unsigned& n1,
        unsigned& v2, unsigned& n2)
{
    return std::sscanf(line.c_str(),
        "f %d//%d %d//%d %d//%d",
        &v0, &n0, &v1, &n1, &v2, &n2) == 6;
}

bool IsFace3(const std::string& line,
        unsigned& v0, unsigned& t0, unsigned& n0,
        unsigned& v1, unsigned& t1, unsigned& n1,
        unsigned& v2, unsigned& t2, unsigned& n2)
{
    return std::sscanf(line.c_str(),
        "f %d/%d/%d %d/%d/%d %d/%d/%d",
        &v0, &t0, &n0, &v1, &t1, &n1, &v2, &t2, &n2) == 9;
}

}

namespace res {

std::vector<ResShaderTank::Vertex> ResModelLoader::m_BuildDrawablePiece(
        const ObjTankObject& object)
{
    assert(object.HasTexCoord());
    assert(object.vertexes.size() == object.normals.size() &&
           object.normals.size() == object.tex_coords.size());

    std::vector<ResShaderTank::Vertex> vertexes;
    for (unsigned i = 0; i != object.vertexes.size(); ++i) {
        vertexes.push_back(ResShaderTank::Vertex {
            object.vertexes[i], object.tex_coords[i],
        });
    }
    return vertexes;
}

std::vector<glm::vec3> ResModelLoader::m_BuildCollidablePiece(
        const ObjTankObject& object)
{
    return object.vertexes;
}

glm::vec3 ResModelLoader::m_BuildJointPiece(
        const ObjTankObject& object)
{
    assert(!object.HasTexCoord());
    glm::vec3 sum = std::accumulate(
        begin(object.vertexes), end(object.vertexes), glm::vec3 {});
    return sum * (1.0f / object.vertexes.size());
}

ResModelTank ResModelLoader::m_CombineObjTankObjects(
        const std::map<std::string, ObjTankObject>& obj_map)
{
    ResModelTank result;

    for (const auto& pr : obj_map) {

        const std::string& name = pr.first;
        const ObjTankObject& object = pr.second;
        const ResModelTank::Piece key = ResModelTank::stringPieceMap[name];

        if (name[0] == 'c') {
            result.coll_geoms[key] = m_BuildCollidablePiece(object);

        } else if (name[0] == 'j') {
            result.joints[key] = m_BuildJointPiece(object);

        } else {
            result.vertexes[key] = m_BuildDrawablePiece(object);

        }
    }

    return result;
}

ResModelLoader::ObjTankObject ResModelLoader::m_BuildObjTankObject(
        const VertexesBag& v_bag,
        const FacesBag& f_bag)
{
    ObjTankObject obj;

    if (f_bag.TwoProps()) {
        for (const auto& ind : f_bag.faces2) {
            obj.vertexes.push_back(v_bag.vertexes[ind[0] - 1]);
            obj.normals.push_back(v_bag.normals[ind[1] - 1]);
        }

    } else if (f_bag.ThreeProps()) {
        for (const auto& ind : f_bag.faces3) {
            obj.vertexes.push_back(v_bag.vertexes[ind[0] - 1]);
            obj.tex_coords.push_back(v_bag.tex_coords[ind[1] - 1]);
            obj.normals.push_back(v_bag.normals[ind[2] - 1]);
        }

    } else {
        DIAG_ERROR_EXIT("Logic error while loading model.");

    }

    return obj;
}

std::map<std::string, ResModelLoader::ObjTankObject>
ResModelLoader::m_LoadObjTankObjects(
        const std::vector<std::string>::iterator first,
        const std::vector<std::string>::iterator last)
{
    std::map<std::string, ObjTankObject> result;

    VertexesBag v_bag;
    FacesBag f_bag;

    std::string previous_name;
    FLOATING x, y, z, s, t;
    unsigned v0, t0, n0, v1, t1, n1, v2, t2, n2;

    auto lineIt = first;
    while (lineIt != last) {

        std::string current_name;

        if (IsObject(*lineIt, current_name)) {
            if (!previous_name.empty()) {
                result[previous_name] = m_BuildObjTankObject(v_bag, f_bag);
                f_bag.Clear();
            }
            previous_name = current_name;

        } else if (IsVertex(*lineIt, x, y, z)) {
            v_bag.vertexes.emplace_back(x, y, z);

        } else if (IsNormal(*lineIt, x, y, z)) {
            v_bag.normals.emplace_back(x, y, z);

        } else if (IsTexCoord(*lineIt, s, t)) {
            v_bag.tex_coords.emplace_back(s, t);

        } else if (IsFace3(*lineIt, v0, t0, n0, v1, t1, n1, v2, t2, n2)) {
            f_bag.faces3.emplace_back(v0, t0, n0);
            f_bag.faces3.emplace_back(v1, t1, n1);
            f_bag.faces3.emplace_back(v2, t2, n2);

        } else if (IsFace2(*lineIt, v0, n0, v1, n1, v2, n2)) {
            f_bag.faces2.emplace_back(v0, n0);
            f_bag.faces2.emplace_back(v1, n1);
            f_bag.faces2.emplace_back(v2, n2);

        } else if (IsSmoothing(*lineIt) || IsComment(*lineIt)) {
            // NULL;
        }

        ++lineIt;
    }

    // Write last object.
    result[previous_name] = m_BuildObjTankObject(v_bag, f_bag);

    return result;
}

ResModelTank ResModelLoader::LoadObjTankModel(const std::string& source) {
    std::vector<std::string> lines = Explode(source, '\n');
    auto object_map = m_LoadObjTankObjects(begin(lines), end(lines));
    auto model = m_CombineObjTankObjects(object_map);
    return model;
}

}
