#pragma once

namespace core
{
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
        int width;
        int height;
    };

    namespace alg
    {
        mat identity();

        vec norm(const vec& v);

        vec vec_mult(const vec& v, const mat& m);
        vec dir_mult(const vec& v, const mat& m);
        mat mat_mult(const mat& left, const mat& right);

        double mat_det(const mat& m);
        mat mat_inv(const mat& m);

        mat translation(const vec& offset);
        mat rotation(const vec& axis, double angle);
        mat scale(const vec& dims);

        mat perspective(double fov, double aspect, double near, double far);

        screen_point vec_project(const vec& v, const mat& prj, viewport viewport);
    }
}
