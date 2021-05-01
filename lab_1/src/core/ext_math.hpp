#pragma once

struct vec
{
    double x;
    double y;
    double z;
};

struct mat
{
    double data[16];
};

struct screen_point
{
    int x;
    int y;
};

struct viewport
{
    int left;
    int top;
    unsigned int width;
    unsigned int height;
};

bool viewport_is_valid(const viewport& viewport);

mat mat_identity();

vec vec_create(double x, double y, double z);
vec norm(const vec& v);
double vec_length(const vec& v);

vec vec_mult(const vec& v, const mat& m);
vec dir_mult(const vec& v, const mat& m);
mat mat_mult(const mat& left, const mat& right);

double mat_det(const mat& m);
mat mat_inv(const mat& m);

mat mat_translation(const vec& offset);
mat mat_rotation(const vec& axis, double angle);
mat mat_scale(const vec& dims);

mat mat_perspective(double fov, double aspect, double near, double far);

screen_point vec_project(const vec& v, const mat& prj, viewport viewport);

constexpr viewport viewport_init(unsigned int width = 0, unsigned int height = 0)
{
    viewport v {};

    v.left = 0;
    v.top = 0;
    v.width = width;
    v.height = height;

    return v;
}
