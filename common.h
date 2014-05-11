#ifndef COMMON_H
#define COMMON_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define FLOATING float

float Q_rsqrt( float number );

void cast_rotated_coords(FLOATING up, FLOATING right, FLOATING angle, FLOATING &dx, FLOATING &dy);

#endif
