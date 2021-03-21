#pragma once

#include "sal.hpp"
#include "error_code.hpp"
#include "ext_math.hpp"

namespace core
{
    struct View
    {
        viewport viewport;
        mat proj_mat;
        mat view_mat;
    };

    View view_init(IN const viewport& viewport = alg::viewport_init());
    void view_reset(VAR View& view);

    mat view_get_mvp(IN const View& view);

    bool view_is_valid(IN const View& view);

    ErrorCode view_translate(VAR View& view, int dx, int dy);
    ErrorCode view_scale(VAR View& view, double dfactor);
    ErrorCode view_rotate(VAR View& view, int dx, int dy);

    ErrorCode view_project(OUT screen_point& point, IN const View& view, IN vec pos);
    ErrorCode view_apply(OUT vec& out, IN const View& view, IN vec in);
}
