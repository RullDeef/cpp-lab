#include <cmath>
#include "ext_math.hpp"

using namespace core;

mat alg::identity()
{
    return mat {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

vec alg::norm(const vec& v)
{
    double len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return vec { v.x / len, v.y / len, v.z / len };
}

vec alg::vec_mult(const vec& v, const mat& m)
{
    return vec {
        v.x * m.data[0] + v.y * m.data[4] + v.z * m.data[ 8] + m.data[12],
        v.x * m.data[1] + v.y * m.data[5] + v.z * m.data[ 9] + m.data[13],
        v.x * m.data[2] + v.y * m.data[6] + v.z * m.data[10] + m.data[14]
    };
}

vec alg::dir_mult(const vec& v, const mat& m)
{
    return vec {
        v.x * m.data[0] + v.y * m.data[4] + v.z * m.data[8],
        v.x * m.data[1] + v.y * m.data[5] + v.z * m.data[9],
        v.x * m.data[2] + v.y * m.data[6] + v.z * m.data[10]
    };
}

mat alg::mat_mult(const mat& left, const mat& right)
{
    mat res {};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            res.data[4 * i + j] = 0;
            for (int k = 0; k < 4; k++)
                res.data[4 * i + j] += left.data[4 * i + k] * right.data[4 * k + j];
        }
    }

    return res;
}

double alg::mat_det(const mat& m)
{
    double det = 0;

    det += m.data[0] * m.data[5] * m.data[10] * m.data[15];
    det += m.data[1] * m.data[6] * m.data[11] * m.data[12];
    det += m.data[2] * m.data[7] * m.data[ 8] * m.data[13];
    det += m.data[3] * m.data[4] * m.data[ 9] * m.data[14];

    det -= m.data[0] * m.data[7] * m.data[10] * m.data[13];
    det -= m.data[1] * m.data[4] * m.data[11] * m.data[14];
    det -= m.data[2] * m.data[5] * m.data[ 8] * m.data[15];
    det -= m.data[3] * m.data[6] * m.data[ 9] * m.data[12];

    return det;
}

mat alg::mat_inv(const mat& m)
{
    mat inv;

    inv.data[0] = m.data[5] * m.data[10] * m.data[15] -
        m.data[5] * m.data[11] * m.data[14] -
        m.data[9] * m.data[6] * m.data[15] +
        m.data[9] * m.data[7] * m.data[14] +
        m.data[13] * m.data[6] * m.data[11] -
        m.data[13] * m.data[7] * m.data[10];

    inv.data[4] = -m.data[4] * m.data[10] * m.data[15] +
        m.data[4] * m.data[11] * m.data[14] +
        m.data[8] * m.data[6] * m.data[15] -
        m.data[8] * m.data[7] * m.data[14] -
        m.data[12] * m.data[6] * m.data[11] +
        m.data[12] * m.data[7] * m.data[10];

    inv.data[8] = m.data[4] * m.data[9] * m.data[15] -
        m.data[4] * m.data[11] * m.data[13] -
        m.data[8] * m.data[5] * m.data[15] +
        m.data[8] * m.data[7] * m.data[13] +
        m.data[12] * m.data[5] * m.data[11] -
        m.data[12] * m.data[7] * m.data[9];

    inv.data[12] = -m.data[4] * m.data[9] * m.data[14] +
        m.data[4] * m.data[10] * m.data[13] +
        m.data[8] * m.data[5] * m.data[14] -
        m.data[8] * m.data[6] * m.data[13] -
        m.data[12] * m.data[5] * m.data[10] +
        m.data[12] * m.data[6] * m.data[9];

    inv.data[1] = -m.data[1] * m.data[10] * m.data[15] +
        m.data[1] * m.data[11] * m.data[14] +
        m.data[9] * m.data[2] * m.data[15] -
        m.data[9] * m.data[3] * m.data[14] -
        m.data[13] * m.data[2] * m.data[11] +
        m.data[13] * m.data[3] * m.data[10];

    inv.data[5] = m.data[0] * m.data[10] * m.data[15] -
        m.data[0] * m.data[11] * m.data[14] -
        m.data[8] * m.data[2] * m.data[15] +
        m.data[8] * m.data[3] * m.data[14] +
        m.data[12] * m.data[2] * m.data[11] -
        m.data[12] * m.data[3] * m.data[10];

    inv.data[9] = -m.data[0] * m.data[9] * m.data[15] +
        m.data[0] * m.data[11] * m.data[13] +
        m.data[8] * m.data[1] * m.data[15] -
        m.data[8] * m.data[3] * m.data[13] -
        m.data[12] * m.data[1] * m.data[11] +
        m.data[12] * m.data[3] * m.data[9];

    inv.data[13] = m.data[0] * m.data[9] * m.data[14] -
        m.data[0] * m.data[10] * m.data[13] -
        m.data[8] * m.data[1] * m.data[14] +
        m.data[8] * m.data[2] * m.data[13] +
        m.data[12] * m.data[1] * m.data[10] -
        m.data[12] * m.data[2] * m.data[9];

    inv.data[2] = m.data[1] * m.data[6] * m.data[15] -
        m.data[1] * m.data[7] * m.data[14] -
        m.data[5] * m.data[2] * m.data[15] +
        m.data[5] * m.data[3] * m.data[14] +
        m.data[13] * m.data[2] * m.data[7] -
        m.data[13] * m.data[3] * m.data[6];

    inv.data[6] = -m.data[0] * m.data[6] * m.data[15] +
        m.data[0] * m.data[7] * m.data[14] +
        m.data[4] * m.data[2] * m.data[15] -
        m.data[4] * m.data[3] * m.data[14] -
        m.data[12] * m.data[2] * m.data[7] +
        m.data[12] * m.data[3] * m.data[6];

    inv.data[10] = m.data[0] * m.data[5] * m.data[15] -
        m.data[0] * m.data[7] * m.data[13] -
        m.data[4] * m.data[1] * m.data[15] +
        m.data[4] * m.data[3] * m.data[13] +
        m.data[12] * m.data[1] * m.data[7] -
        m.data[12] * m.data[3] * m.data[5];

    inv.data[14] = -m.data[0] * m.data[5] * m.data[14] +
        m.data[0] * m.data[6] * m.data[13] +
        m.data[4] * m.data[1] * m.data[14] -
        m.data[4] * m.data[2] * m.data[13] -
        m.data[12] * m.data[1] * m.data[6] +
        m.data[12] * m.data[2] * m.data[5];

    inv.data[3] = -m.data[1] * m.data[6] * m.data[11] +
        m.data[1] * m.data[7] * m.data[10] +
        m.data[5] * m.data[2] * m.data[11] -
        m.data[5] * m.data[3] * m.data[10] -
        m.data[9] * m.data[2] * m.data[7] +
        m.data[9] * m.data[3] * m.data[6];

    inv.data[7] = m.data[0] * m.data[6] * m.data[11] -
        m.data[0] * m.data[7] * m.data[10] -
        m.data[4] * m.data[2] * m.data[11] +
        m.data[4] * m.data[3] * m.data[10] +
        m.data[8] * m.data[2] * m.data[7] -
        m.data[8] * m.data[3] * m.data[6];

    inv.data[11] = -m.data[0] * m.data[5] * m.data[11] +
        m.data[0] * m.data[7] * m.data[9] +
        m.data[4] * m.data[1] * m.data[11] -
        m.data[4] * m.data[3] * m.data[9] -
        m.data[8] * m.data[1] * m.data[7] +
        m.data[8] * m.data[3] * m.data[5];

    inv.data[15] = m.data[0] * m.data[5] * m.data[10] -
        m.data[0] * m.data[6] * m.data[9] -
        m.data[4] * m.data[1] * m.data[10] +
        m.data[4] * m.data[2] * m.data[9] +
        m.data[8] * m.data[1] * m.data[6] -
        m.data[8] * m.data[2] * m.data[5];

    double det = 1 / (m.data[0] * inv.data[0]
        + m.data[1] * inv.data[4]
        + m.data[2] * inv.data[8]
        + m.data[3] * inv.data[12]);

    for (int i = 0; i < 16; i++)
        inv.data[i] *= det;

    return inv;
}

mat alg::translation(const vec& offset)
{
    return mat {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        offset.x, offset.y, offset.z, 1
    };
}

mat alg::rotation(const vec& axis, double angle)
{
    const double& x = axis.x, y = axis.y, z = axis.z;
    double c = cos(angle), s = sin(angle);
    double imc = 1 - c;

    return mat{
        c + x * x * imc,        x * y * imc + z * s,    x * z * imc - y * s,  0,
        x * y * imc - z * s,    c + y * y * imc,        y * z * imc + x * s,  0,
        x * z * imc + y * s,    y * z * imc - x * s,    c + z * z * imc,      0,
        0, 0, 0, 1
    };
}

mat alg::scale(const vec& dims)
{
    return mat {
        dims.x, 0, 0, 0,
        0, dims.y, 0, 0,
        0, 0, dims.z, 0,
        0, 0, 0, 1
    };
}

mat alg::perspective(double fov, double aspect, double near, double far)
{
    double s = 1 / tan(fov / 2);

    return mat {
        s / aspect, 0, 0, 0,
        0, s, 0, 0,
        0, 0, far / (near - far), -1,
        0, 0, near * far / (near - far), 0
    };
}

screen_point alg::vec_project(const vec& v, const mat& prj, viewport viewport)
{
    vec p_v = vec_mult(v, prj);

    return screen_point{
        int(viewport.left + 0.5 * (1 + p_v.x / -p_v.z) * viewport.width),
        int(viewport.top + 0.5 * (1 - p_v.y / -p_v.z) * viewport.height)
    };
}
