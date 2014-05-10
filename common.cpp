#include <cstring>

#include <cmath>
#include <cstdio>

#include "common.h"

/* This is obviously not mine.
 * If you don't recognize it, look up "fast inverse square root".
 */
float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//      y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

void cast_rotated_coords(
		FLOATING up, FLOATING right, FLOATING angle,
		FLOATING &dx, FLOATING &dy)
{
	dx = up * cos(angle) + right * sin(angle);
	dy = up * -sin(angle) + right * cos(angle);
}
