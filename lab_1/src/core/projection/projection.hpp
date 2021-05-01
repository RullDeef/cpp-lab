#pragma once

#include "../sal.hpp"
#include "../error_code.hpp"
#include "../model/model.hpp"
#include "../view/view.hpp"

struct Projection
{
    vert_array verts;
    edge_array edges;
};

Projection proj_init();
void proj_destroy(VAR Projection& proj);

ErrorCode proj_clone(OUT Projection& proj, IN const Model& model);
ErrorCode proj_update(VAR Projection& proj, IN const Model& model, IN const View& view);

bool proj_is_valid(IN const Projection& proj);
