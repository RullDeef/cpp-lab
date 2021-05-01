#pragma once

#include "../sal.hpp"
#include "../ext_math.hpp"
#include "../error_code.hpp"


struct transform
{
    mat data;
};

transform tf_init();

ErrorCode tf_translate(VAR transform& tf, IN const vec& delta);
ErrorCode tf_rotate(VAR transform& tf, IN const vec& axis, double angle);
ErrorCode tf_scale(VAR transform& tf, IN const vec& dims);
ErrorCode tf_scale(VAR transform& tf, IN double factor);

transform tf_projection(IN const viewport& viewport, IN double fov, IN double near, IN double far);
transform tf_combine(IN const transform& first, IN const transform& second);
transform tf_inverse(IN const transform& tf);

vec tf_apply(IN const transform& tf, IN const vec& point);
vec tf_apply_inverse(IN const transform& tf, IN const vec& point);
