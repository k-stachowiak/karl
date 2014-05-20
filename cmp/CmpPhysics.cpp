#include "config.h"
#include "CmpPhysics.h"

namespace cmp {

glm::vec3 CmpPhysics::GetDirection() const
{
    glm::mat4 rot_mat = glm::mat4_cast(GetRotation());
    glm::vec4 front_vec { 1, 0, 0, 0 };
    front_vec = rot_mat * front_vec;
    return { front_vec[0], front_vec[1], front_vec[2] };
}

glm::vec3 CmpPhysics::GetRotationAngles() const
{
    return glm::eulerAngles(GetRotation());
}

}

