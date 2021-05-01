#include "transform.hpp"


transform tf_init()
{
    transform tf {};

    tf.data = mat_identity();

    return tf;
}

ErrorCode tf_translate(VAR transform& tf, IN const vec& delta)
{
    mat translation = mat_translation(delta);
    tf.data = mat_mult(translation, tf.data);

    return ErrorCode::success;
}

ErrorCode tf_rotate(VAR transform& tf, IN const vec& axis, double angle)
{
    if (vec_length(axis) < 1e-6)
        return ErrorCode::invalid_rotation_axis;

    mat rotation = mat_rotation(axis, angle);
    tf.data = mat_mult(rotation, tf.data);

    return ErrorCode::success;
}

ErrorCode tf_scale(VAR transform& tf, IN const vec& dims)
{
    mat scale = mat_scale(dims);
    tf.data = mat_mult(scale, tf.data);

    return ErrorCode::success;
}

ErrorCode tf_scale(VAR transform& tf, IN double factor)
{
    if (factor < 1e-3)
        return ErrorCode::invalid_scale_factor;

    return tf_scale(tf, vec_create(factor, factor, factor));
}

transform tf_projection(IN const viewport& viewport, IN double fov, IN double near, IN double far)
{
    transform tf = tf_init();

    double aspect = double(viewport.width) / viewport.height;
    tf.data = mat_perspective(fov, aspect, near, far);

    return tf;
}

transform tf_combine(IN const transform& first, IN const transform& second)
{
    transform res = tf_init();

    res.data = mat_mult(first.data, second.data);

    return res;
}

transform tf_inverse(IN const transform& tf)
{
    transform res{};

    res.data = mat_inv(tf.data);

    return res;
}

vec tf_apply(IN const transform& tf, IN const vec& point)
{
    return vec_mult(point, tf.data);
}

vec tf_apply_inverse(IN const transform& tf, IN const vec& point)
{
    return vec_mult(point, tf_inverse(tf).data);
}
