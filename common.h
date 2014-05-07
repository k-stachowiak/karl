#ifndef COMMON_H
#define COMMON_H

#define FLOATING float

// TODO: Turn these into typedefs.
struct Mat2 { FLOATING data[4]; };
struct Mat3 { FLOATING data[9]; };
struct Mat4 { FLOATING data[16]; };
struct Vec2 { FLOATING data[2]; };
struct Vec3 { FLOATING data[3]; };
struct Vec4 { FLOATING data[4]; };

float Q_rsqrt( float number );

void mat4_identity(Mat4 &mat);
void mat4_multiply(Mat4 &mat, Mat4 &factor);
void mat4_translate(Mat4 &mat, FLOATING dx, FLOATING dy, FLOATING dz);
void mat4_translatev(Mat4 &mat, const Vec3& delta);
void mat4_rotate_x(Mat4& mat, FLOATING angle);
void mat4_rotate_y(Mat4& mat, FLOATING angle);
void mat4_rotate_z(Mat4& mat, FLOATING angle);
void mat4_ortho(Mat4 &mat, FLOATING left, FLOATING right, FLOATING bottom, FLOATING top);
void mat4_perspective(Mat4 &mat, FLOATING fovy, FLOATING aspect, FLOATING near, FLOATING far);

void vec4_mat4_multiply(Vec4 &v, Mat4 &m);

void cast_rotated_coords(FLOATING up, FLOATING right, FLOATING angle, FLOATING &dx, FLOATING &dy);

#endif
