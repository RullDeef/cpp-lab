#include <cstdlib>
#include "projectedmodel.hpp"

using namespace core;

ProjectedModel core::projmod_init()
{
    ProjectedModel projmod {};

    projmod.verts_count = 0;
    projmod.verts = nullptr;

    projmod.edges_count = 0;
    projmod.edges = nullptr;

    return projmod;
}

static void verts_free(OUT unsigned int& verts_count, VAR screen_point*& verts)
{
    if (verts != nullptr)
        free(verts);

    verts = nullptr;
    verts_count = 0;
}

static void edges_free(OUT unsigned int& edges_count, VAR section*& edges)
{
    if (edges != nullptr)
        free(edges);

    edges = nullptr;
    edges_count = 0;
}

void core::projmod_destroy(VAR ProjectedModel& projmod)
{
    verts_free(projmod.verts_count, projmod.verts);
    edges_free(projmod.edges_count, projmod.edges);
}

bool core::projmod_is_valid(IN const ProjectedModel& projmod)
{
    bool verts_valid = projmod.verts_count > 0 && projmod.verts != nullptr;
    bool edges_valid = projmod.edges_count > 0 && projmod.edges != nullptr;

    return verts_valid && edges_valid;
}

static bool projmod_allocate(OUT ProjectedModel& projmod, IN unsigned int verts_count, IN unsigned int edges_count)
{
    projmod.verts_count = verts_count;
    projmod.verts = (screen_point*)malloc(verts_count * sizeof(screen_point));

    projmod.edges_count = edges_count;
    projmod.edges = (section*)malloc(edges_count * sizeof(section));

    bool valid = projmod.verts != nullptr && projmod.edges != nullptr;
    if (!valid)
        projmod_destroy(projmod);

    return valid;
}

static void projmod_update_edges_indices(OUT section* prj_edges, IN const screen_point* points, const edge* edges, unsigned int edges_count)
{
    for (unsigned int i = 0; i < edges_count; i++)
    {
        prj_edges[i].p1 = points[edges[i].p1];
        prj_edges[i].p2 = points[edges[i].p2];
    }
}

ErrorCode core::projmod_project(VAR ProjectedModel& projmod, IN const Model& model, IN const View& view)
{
    if (!model_is_valid(model))
        return ErrorCode::invalid_model;

    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    if (!projmod_is_valid(projmod))
        if (!projmod_allocate(projmod, model.verts_count, model.edges_count))
            return ErrorCode::bad_malloc;

    ErrorCode status = ErrorCode::success;
    for (unsigned int i = 0; i < model.verts_count && status == ErrorCode::success; i++)
        status = view_project(projmod.verts[i], view, model.verts[i]);

    if (status == ErrorCode::success)
        projmod_update_edges_indices(projmod.edges, projmod.verts, model.edges, model.edges_count);

    return status;
}

ErrorCode core::projmod_apply_view(VAR Model& model, IN const View& view)
{
    if (!model_is_valid(model))
        return ErrorCode::invalid_model;

    if (!view_is_valid(view))
        return ErrorCode::invalid_view;

    ErrorCode status = ErrorCode::success;
    for (unsigned int i = 0; i < model.verts_count && status == ErrorCode::success; i++)
        status = view_apply(model.verts[i], view, model.verts[i]);

    return ErrorCode::success;
}
