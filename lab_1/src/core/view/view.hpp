#pragma once

#include "../sal.hpp"
#include "../error_code.hpp"
#include "../ext_math.hpp"
#include "../model/vert_array.hpp"
#include "../transform/transform.hpp"


struct View
{
    viewport viewport;
    transform model_tf;
    transform camera_tf;
};

View view_init();
View view_init(IN const viewport& viewport);
// void view_reset(VAR View& view);

transform view_get_mvp(IN const View& view);

bool view_is_valid(IN const View& view);

ErrorCode view_translate(VAR View& view, int dx, int dy);
ErrorCode view_scale(VAR View& view, double dfactor);
ErrorCode view_rotate(VAR View& view, int dx, int dy);

ErrorCode view_project(OUT vec& out, IN const View& view, IN const vec& in);
ErrorCode view_project(VAR vert_array& verts, IN const View& view);

ErrorCode view_apply(OUT vec& out, IN const View& view, IN const vec& in);
ErrorCode view_apply(VAR vert_array& verts, IN const View& view);
