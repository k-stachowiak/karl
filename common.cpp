#include <cstring>

#include <cmath>
#include <cstdio>

#include "common.h"

static struct Mat4 identity_matrix = {{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
}};

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

void mat4_identity(struct Mat4 &mat)
{
	mat = identity_matrix;
}

void mat4_multiply(Mat4 &mat, Mat4 &factor)
{
	int row, column, row_offset;
	Mat4 result;

	mat4_identity(result);

	for (row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4) {
		for (column = 0; column < 4; ++column) {
			result.data[row_offset + column] =
				(mat.data[row_offset + 0] * factor.data[column + 0]) +
				(mat.data[row_offset + 1] * factor.data[column + 4]) +
				(mat.data[row_offset + 2] * factor.data[column + 8]) +
				(mat.data[row_offset + 3] * factor.data[column + 12]);
		}
	}

	mat = result;
}

void mat4_translate(Mat4 &mat, FLOATING dx, FLOATING dy, FLOATING dz)
{
	mat.data[12] += dx;
	mat.data[13] += dy;
	mat.data[14] += dz;
}

void mat4_translatev(Mat4 &mat, const Vec3 &delta)
{
	mat4_translate(mat, delta.data[0], delta.data[1], delta.data[2]);
}

void mat4_rotate_x(Mat4& mat, FLOATING angle)
{
	FLOATING sine = (FLOATING)sin(angle);
	FLOATING cosine = (FLOATING)cos(angle);

	Mat4 rot;
	mat4_identity(rot);
	rot.data[5] = cosine;
	rot.data[6] = -sine;
	rot.data[9] = sine;
	rot.data[10] = cosine;

	mat4_multiply(mat, rot);
}

void mat4_rotate_y(Mat4& mat, FLOATING angle)
{
	FLOATING sine = (FLOATING)sin(angle);
	FLOATING cosine = (FLOATING)cos(angle);

	struct Mat4 rot;
	mat4_identity(rot);
	rot.data[0] = cosine;
	rot.data[8] = sine;
	rot.data[2] = -sine;
	rot.data[10] = cosine;

	mat4_multiply(mat, rot);
}

void mat4_rotate_z(Mat4& mat, FLOATING angle)
{
	FLOATING sine = (FLOATING)sin(angle);
	FLOATING cosine = (FLOATING)cos(angle);

	struct Mat4 rot;
	mat4_identity(rot);
	rot.data[0] = cosine;
	rot.data[1] = -sine;
	rot.data[4] = sine;
	rot.data[5] = cosine;

	mat4_multiply(mat, rot);
}

void mat4_ortho(Mat4 &mat, FLOATING left, FLOATING right, FLOATING bottom, FLOATING top)
{
	mat.data[0] = 2 / (right - left);
	mat.data[5] = 2 / (top - bottom);
	mat.data[10] = -1;
	mat.data[12] = - (right + left) / (right - left);
	mat.data[13] = - (top + bottom) / (top - bottom);
}

void mat4_perspective(Mat4 &mat, FLOATING fovy, FLOATING aspect, FLOATING near, FLOATING far)
{
	memset(mat.data, 0, sizeof(mat.data));

	const FLOATING y_scale = (FLOATING)(1.0 / cos(fovy * 3.1415 / 360));
	const FLOATING x_scale = y_scale / aspect;
	const FLOATING frustum_length = far - near;

	mat.data[0] = x_scale;
	mat.data[5] = y_scale;
	mat.data[10] = -((far + near) / frustum_length);
	mat.data[11] = -1;
	mat.data[14] = -((2 * near * far) / frustum_length);
}

void vec4_mat4_multiply(Vec4 &v, Mat4 &m)
{
	FLOATING res[4] = {
		v.data[0] * m.data[0] +
			 v.data[1] * m.data[1] +
			 v.data[2] * m.data[2] +
			 v.data[3] * m.data[3],
		v.data[0] * m.data[4] +
			 v.data[1] * m.data[5] +
			 v.data[2] * m.data[6] +
			 v.data[3] * m.data[7],
		v.data[0] * m.data[8] +
			 v.data[1] * m.data[9] +
			 v.data[2] * m.data[10] +
			 v.data[3] * m.data[11],
		v.data[0] * m.data[12] +
			 v.data[1] * m.data[13] +
			 v.data[2] * m.data[14] +
			 v.data[3] * m.data[15]
	};
	// TODO: memcpy? memset? rly?
	memcpy(v.data, res, sizeof(res));
}

void cast_rotated_coords(
		FLOATING up, FLOATING right, FLOATING angle,
		FLOATING &dx, FLOATING &dy)
{
	dx = up * cos(angle) + right * sin(angle);
	dy = up * sin(angle) + right * cos(angle);
}
