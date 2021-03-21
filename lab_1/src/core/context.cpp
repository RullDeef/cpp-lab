
#if 0
#include <memory>
#include "error_code.hpp"
#include "ext_math.hpp"
#include "context.hpp"

using namespace core;
using namespace core::alg;

ErrorCode core::validate_viewport(viewport viewport)
{
    if (viewport.width > 0 && viewport.height > 0)
        return ErrorCode::success;
    else
        return ErrorCode::invalid_viewport;
}

ErrorCode core::validate_model(const Model& model)
{
    return ErrorCode::success;
}

ErrorCode core::validate_projection(const ProjectedModel& projetion)
{
    return ErrorCode::success;
}

ErrorCode core::validate_context(const Context& context)
{
    return ErrorCode::success;
}

void core::destroy_model(Model& model)
{
    if (model.verts)
        free(model.verts);

    if (model.edges)
        free(model.edges);

    memset(&model, 0, sizeof(Model));
}

void core::destroy_projection(ProjectedModel& projection)
{
    if (projection.verts)
        free(projection.verts);

    if (projection.edges)
        free(projection.edges);

    memset(&projection, 0, sizeof(ProjectedModel));
}

void core::destroy_context(Context& context)
{
    destroy_model(context.model);
    destroy_projection(context.projection);

    context.proj_mat = mat_identity();
    context.view_mat = mat_identity();
    context.viewport = viewport { 0, 0, 0, 0 };
}

ErrorCode core::init_projection(ProjectedModel& prj, unsigned int verts, unsigned int edges)
{
    prj.verts_count = verts;
    prj.verts = static_cast<screen_point*>(malloc(verts * sizeof(screen_point)));

    if (prj.verts == nullptr)
    {
        prj.verts_count = 0;
        return ErrorCode::bad_malloc;
    }

    prj.edges_count = edges;
    prj.edges = static_cast<section*>(malloc(edges * sizeof(section)));

    if (prj.edges == nullptr)
    {
        free(prj.verts);
        prj.edges_count = 0;
        prj.verts_count = 0;
        prj.verts = nullptr;
        return ErrorCode::bad_malloc;
    }

    return ErrorCode::success;
}

ErrorCode core::update_projection(Context& context)
{
    mat mvp = mat_mult(context.view_mat, context.proj_mat);

    // project each vertex in model
    for (unsigned int i = 0; i < context.model.verts_count; i++)
    {
        vec v = context.model.verts[i];
        screen_point p = vec_project(context.model.verts[i], mvp, context.viewport);
        context.projection.verts[i] = p;
    }

    // copy projected points based on edges
    for (unsigned int i = 0; i < context.model.edges_count; i++)
    {
        unsigned int p1 = context.model.edges[i].p1;
        unsigned int p2 = context.model.edges[i].p2;

        context.projection.edges[i].p1 = context.projection.verts[p1];
        context.projection.edges[i].p2 = context.projection.verts[p2];
    }

    return ErrorCode::success;
}

#endif
