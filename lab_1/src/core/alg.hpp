#pragma once

#include "basetypes.hpp"

namespace core::alg
{
    mat identity();

    vec norm(const vec& v);

    vec vec_mult(const vec& v, const mat& m);
    vec dir_mult(const vec& v, const mat& m);
    mat mat_mult(const mat& left, const mat& right);

    real mat_det(const mat& m);
    mat mat_inv(const mat& m);

    mat translation(const vec& offset);

    mat rotation_x(real angle);
    mat rotation_y(real angle);
    mat rotation_z(real angle);
    mat rotation(const vec& axis, real angle);

    mat scale(const vec& dims);

    mat perspective(angle fov, real aspect, real near, real far);

    screen_point vec_project(const vec& v, const mat& prj, viewport viewport);
}
