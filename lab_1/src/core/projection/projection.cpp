#include <cstdlib>
#include "projection.hpp"


Projection proj_init()
{
    Projection proj {};

    proj.verts = vert_arr_init();
    proj.edges = edge_arr_init();

    return proj;
}

ErrorCode proj_update(VAR Projection& proj, IN const Model& model, IN const View& view)
{
    Projection res = proj_init();
    ErrorCode status = proj_clone(res, model);

    if (status == ErrorCode::success)
        status = view_apply(res.verts, view);

    if (status != ErrorCode::success)
        proj_destroy(res);
    else
    {
        proj_destroy(proj);
        proj = res;
    }

    return status;
}

ErrorCode proj_clone(OUT Projection& proj, IN const Model& model)
{
    if (!model_is_valid(model))
        return ErrorCode::invalid_model;

    ErrorCode status = vert_arr_clone(proj.verts, model.verts);
    if (status != ErrorCode::success)
        return status;

    status = edge_arr_clone(proj.edges, model.edges);
    if (status != ErrorCode::success)
        vert_arr_destroy(proj.verts);

    return status;
}

void proj_destroy(VAR Projection& proj)
{
    vert_arr_destroy(proj.verts);
    edge_arr_destroy(proj.edges);
}

bool proj_is_valid(IN const Projection& proj)
{
    return vert_arr_is_valid(proj.verts) && edge_arr_is_valid(proj.edges);
}
