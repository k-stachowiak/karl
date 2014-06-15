#include "Config.h"
#include "CmpPhysics.h"

namespace {

glm::vec3 g_GetLocation(dBodyID body)
{
    const FLOATING* locationv = dBodyGetPosition(body);
    return { locationv[0], locationv[1], locationv[2] };
}

glm::quat g_GetRotation(dBodyID body)
{
    const FLOATING* rotationv = dBodyGetQuaternion(body);
    return { rotationv[0], rotationv[1], rotationv[2], rotationv[3] };
}

glm::vec3 g_InterpolateLocation(
        glm::vec3 previous, glm::vec3 current, FLOATING weight)
{
    return weight * previous + (1 - weight) * current;
}

glm::quat g_InterpolateRotation(
        glm::quat previous, glm::quat current, FLOATING weight)
{
    return glm::slerp(previous, current, weight);
}

glm::mat4 g_BuildMatrix(glm::vec3 loc, glm::quat rot)
{
    glm::mat4 result;
    result = glm::translate(result, loc);
    result *= glm::mat4_cast(rot);
    return result;
}

}

namespace cmp {

glm::mat4 g_ComputeBodyMatrix(dBodyID body)
{
    glm::vec3 location = g_GetLocation(body);
    glm::quat rotation = g_GetRotation(body);
    return g_BuildMatrix(location, rotation);
}

glm::mat4 g_ComputeBodyMatrix(dBodyID body,
        glm::vec3 prev_loc,
        glm::quat prev_rot,
        FLOATING weight)
{
    glm::vec3 cur_loc = g_GetLocation(body);
    glm::quat cur_rot = g_GetRotation(body);
    glm::vec3 location = g_InterpolateLocation(prev_loc, cur_loc, weight);
    glm::quat rotation = g_InterpolateRotation(prev_rot, cur_rot, weight);
    return g_BuildMatrix(location, rotation);
}

void CmpPhysics::UpdateFrame()
{
    if (auto body = GetBody()) {
        prev_location = g_GetLocation(body);
        prev_rotation = g_GetRotation(body);
    }
}

glm::vec3 CmpPhysics::GetLocation() const
{
    if (auto body = GetBody()) {
        return g_GetLocation(body);
    } else {
        return {};
    }
}

glm::quat CmpPhysics::GetRotation() const
{
    if (auto body = GetBody()) {
        return g_GetRotation(body);
    } else {
        return {};
    }
}

glm::vec3 CmpPhysics::GetDirection() const
{
    if (auto body = GetBody()) {
        glm::mat4 rot_mat = glm::mat4_cast(g_GetRotation(body));
        glm::vec4 front_vec { 1, 0, 0, 0 };
        front_vec = rot_mat * front_vec;
        return { front_vec[0], front_vec[1], front_vec[2] };
    } else {
        return {};
    }
}

glm::vec3 CmpPhysics::GetRotationAngles() const
{
    if (auto body = GetBody()) {
        return glm::eulerAngles(g_GetRotation(body));
    } else {
        return {};
    }
}

glm::mat4 CmpPhysics::GetMatrix() const
{
    if (auto body = GetBody()) {
        return g_ComputeBodyMatrix(body);
    } else {
        return {};
    }
}

glm::mat4 CmpPhysics::GetMatrix(FLOATING weight) const
{
    if (auto body = GetBody()) {
        return g_ComputeBodyMatrix(body, prev_location, prev_rotation, weight);
    } else {
        return {};
    }
}

}

