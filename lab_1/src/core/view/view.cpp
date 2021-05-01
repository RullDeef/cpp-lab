#include "view.hpp"

constexpr auto view_near = 1.4;
constexpr auto view_far = 100.0;
constexpr auto view_fov = 75 * 3.1415 / 180;

constexpr auto view_z = -10.0;

// constexpr auto move_sensetivity = 60.0;
// constexpr auto rotate_sensetivity = 60.0;
// constexpr auto scale_sensetivity = 60.0;


View view_init()
{
    View view {};

    view.viewport = viewport_init();
    view.camera_tf = tf_init();
    view.model_tf = tf_init();

    return view;
}

View view_init(IN const viewport& viewport)
{
    View view {};

    view.viewport = viewport;
    view.model_tf = tf_init();
    view.camera_tf = tf_projection(viewport, view_fov, view_near, view_far);

    vec camera_offset = vec_create(0, 0, view_z);
    tf_translate(view.camera_tf, camera_offset);

    return view;
}

transform view_get_mvp(IN const View& view)
{
    return tf_combine(view.camera_tf, view.model_tf);
}

bool view_is_valid(IN const View& view)
{
    return viewport_is_valid(view.viewport);
}

ErrorCode view_translate(VAR View& view, int dx, int dy)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    vec offset = vec_create(dx, dy, 0);
    offset = tf_apply_inverse(view.model_tf, offset);
    tf_translate(view.model_tf, offset);

    return ErrorCode::success;
}

ErrorCode view_scale(VAR View& view, double dfactor)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    tf_scale(view.model_tf, dfactor);
    return ErrorCode::success;
}

ErrorCode view_rotate(VAR View& view, int dx, int dy)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    vec x_loc = vec_create(1, 0, 0);
    x_loc = tf_apply_inverse(view.model_tf, x_loc);
    tf_rotate(view.model_tf, x_loc, -dy);

    vec y_loc = vec_create(0, 1, 0);
    y_loc = tf_apply_inverse(view.model_tf, y_loc);
    tf_rotate(view.model_tf, y_loc, -dx);

    return ErrorCode::success;
}

ErrorCode view_project(OUT vec& out, IN const View& view, IN const vec& in)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    out = tf_apply(view_get_mvp(view), in);
    return ErrorCode::success;
}

ErrorCode view_project(VAR vert_array& verts, IN const View& view)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    return vert_arr_transform(verts, view_get_mvp(view));
}

ErrorCode view_apply(OUT vec& out, IN const View& view, IN const vec& in)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    out = tf_apply(view.model_tf, in);
    return ErrorCode::success;
}

ErrorCode view_apply(VAR vert_array& verts, IN const View& view)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    return vert_arr_transform(verts, view.model_tf);
}
