#include "view.hpp"

using namespace core;
using namespace alg;

constexpr auto view_near = 1.4;
constexpr auto view_far = 100.0;
constexpr auto view_fov = 75 * 3.1415 / 180;

constexpr auto view_z = -10.0;

View core::view_init(IN const viewport& viewport)
{
    double aspect = (double)viewport.width / viewport.height;
    View view {};

    view.viewport = viewport;
    view.view_mat = mat_identity();

    mat offset = translation(vec_create(0, 0, view_z));
    mat proj = perspective(view_fov, aspect, view_near, view_far);

    view.proj_mat = mat_mult(offset, proj);

    return view;
}

void core::view_reset(VAR View& view)
{
    view.view_mat = mat_identity();
}

mat core::view_get_mvp(IN const View& view)
{
    return mat_mult(view.view_mat, view.proj_mat);
}

bool core::view_is_valid(IN const View& view)
{
    return viewport_is_valid(view.viewport);
}

ErrorCode core::view_translate(VAR View& view, int dx, int dy)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    constexpr auto sensetivity = 60.0;

    double _dx = -dx / sensetivity;
    double _dy = dy / sensetivity;

    vec loc = vec_create(_dx, _dy, 0);
    loc = dir_mult(loc, mat_inv(view.view_mat));
    view.view_mat = mat_mult(translation(loc), view.view_mat);

    return ErrorCode::success;
}

ErrorCode core::view_scale(VAR View& view, double dfactor)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    constexpr auto sensetivity = 60.0;

    double f = 1 + dfactor / sensetivity;

    vec factor = vec_create(f, f, f);
    view.view_mat = mat_mult(scale(factor), view.view_mat);

    return ErrorCode::success;
}

ErrorCode core::view_rotate(VAR View& view, int dx, int dy)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    constexpr auto sensetivity = 60.0;

    double phi = -dx / sensetivity;
    double theta = -dy / sensetivity;

    vec x_loc = vec_create(1, 0, 0);
    x_loc = norm(dir_mult(x_loc, mat_inv(view.view_mat)));
    view.view_mat = mat_mult(rotation(x_loc, theta), view.view_mat);

    vec y_loc = vec_create(0, 1, 0);
    y_loc = norm(dir_mult(y_loc, mat_inv(view.view_mat)));
    view.view_mat = mat_mult(rotation(y_loc, phi), view.view_mat);

    return ErrorCode::success;
}

ErrorCode core::view_project(OUT screen_point& point, IN const View& view, IN vec pos)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    mat mvp = view_get_mvp(view);
    point = vec_project(pos, mvp, view.viewport);

    return ErrorCode::success;
}

ErrorCode core::view_apply(OUT vec& out, IN const View& view, IN vec in)
{
    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    out = vec_mult(in, view.view_mat);
    return ErrorCode::success;
}
