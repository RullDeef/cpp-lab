#include <cstdio>
#include <cstdlib>
#include <memory>
#include "model_viewer.hpp"
#include "alg.hpp"

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

ErrorCode core::model_viewer(Context& context, const Action& action)
{
    //      sequence of conditions:
    // Destroy
    // Init
    // +check viewport
    // |  Load
    // |  +check model & projection
    // |  |  Save
    // \  \  Translate / Rotate / Scale

    if (action.type == ActionType::Destroy)
        return do_destroy(context);

    if (action.type == ActionType::Init)
    {
        ErrorCode status = validate_viewport(action.viewport);
        if (status == ErrorCode::success)
        {
            memset(&context, 0, sizeof(Context));
            context.viewport = action.viewport;
            real aspect = (real)action.viewport.width / action.viewport.height;
            context.proj_mat = perspective(view_fov, aspect, view_near, view_far);
            context.view_mat = translation({ 0, 0, view_z });
        }
        return status;
    }

    ErrorCode status = validate_viewport(context.viewport);
    if (status != ErrorCode::success)
        return status;

    if (action.type == ActionType::Load)
    {
        status = do_load(context.model, action.filename);
        if (status == ErrorCode::success)
        {
            status = init_projection(context.projection,
                context.model.verts_count, context.model.edges_count);

            if (status == ErrorCode::success)
                status = update_projection(context);
        }

        return status;
    }

    status = validate_model(context.model);
    if (status != ErrorCode::success)
        return status;
    
    status = validate_projection(context.projection);
    if (status != ErrorCode::success)
        return status;

    switch (action.type)
    {
    case ActionType::Translate:
        status = do_translation(context.view_mat, action.translate);
        break;
    case ActionType::Scale:
        status = do_scale(context.view_mat, action.scale);
        break;
    case ActionType::Rotate:
        status = do_rotation(context.view_mat, action.rotate);
        break;
    case ActionType::Save:
        return do_save(context.model, context.view_mat, action.filename);
    default:
        return ErrorCode::unknown_action;
    }

    if (status == ErrorCode::success)
        status = update_projection(context);

    return status;
}

ErrorCode core::do_translation(mat& view, const TranslateAction& action)
{
    return ErrorCode::success;
}

ErrorCode core::do_rotation(mat& view, const RotateAction& action)
{
    constexpr auto sensetivity = 60.0;

    real phi = -action.dx / sensetivity;
    real theta = -action.dy / sensetivity;

    vec x_loc = norm(dir_mult({ 1, 0, 0 }, mat_inv(view)));
    view = mat_mult(rotation(x_loc, theta), view);

    vec y_loc = norm(dir_mult({ 0, 1, 0 }, mat_inv(view)));
    view = mat_mult(rotation(y_loc, phi), view);

    return ErrorCode::success;
}

ErrorCode core::do_scale(mat& view, const ScaleAction& action)
{
    constexpr auto sensetivity = 60.0;

    real f = 1 + action.factor / sensetivity;
    view = mat_mult(scale({ f, f, f }), view);

    return ErrorCode::success;
}

// true = success
inline bool read_vertex(FILE* file, vec& vert)
{
    return fscanf(file, "%lf%lf%lf", &vert.x, &vert.y, &vert.z) == 3;
}

// file validated already
static ErrorCode load_verts(FILE* file, Model& model)
{
    if (fscanf(file, "%u", &model.verts_count) != 1 || model.verts_count == 0)
        return ErrorCode::invalid_file;

    model.verts = static_cast<vec*>(malloc(model.verts_count * sizeof(vec)));
    if (model.verts == nullptr)
        return ErrorCode::bad_malloc;

    for (unsigned int i = 0; i < model.verts_count; i++)
    {
        if (!read_vertex(file, model.verts[i]))
        {
            free(model.verts);
            model.verts = nullptr;
            return ErrorCode::invalid_file;
        }
    }

    return ErrorCode::success;
}

// true = success
inline bool read_edge(FILE* file, edge& edge)
{
    return fscanf(file, "%u%u", &edge.p1, &edge.p2) == 2 && edge.p1 != edge.p2;
}

// file validated already
static ErrorCode load_edges(FILE* file, Model& model)
{
    if (fscanf(file, "%u", &model.edges_count) != 1 || model.edges_count == 0)
        return ErrorCode::invalid_file;

    model.edges = static_cast<edge*>(malloc(model.edges_count * sizeof(edge)));
    if (model.edges == nullptr)
        return ErrorCode::bad_malloc;

    for (unsigned int i = 0; i < model.edges_count; i++)
    {
        if (!read_edge(file, model.edges[i]))
        {
            free(model.edges);
            model.edges = nullptr;
            return ErrorCode::invalid_file;
        }
    }

    return ErrorCode::success;
}

// model MUST contain at least two vertecies and one edge
ErrorCode core::do_load(Model& model, const char* filename)
{
    if (filename == nullptr)
        return ErrorCode::invalid_file_name;

    FILE* file = fopen(filename, "rt");
    if (file == nullptr)
        return ErrorCode::cannot_open_file;

    ErrorCode status = load_verts(file, model);
    if (status == ErrorCode::success)
    {
        status = load_edges(file, model);
        if (status != ErrorCode::success)
        {
            free(model.verts);
            model.verts = nullptr;
        }
    }

    fclose(file);
    return status;
}

static ErrorCode save_verts(FILE* file, const Model& model, mat view)
{
    if (fprintf(file, "%u\n", model.verts_count) < 0)
        return ErrorCode::cannot_write_file;

    for (unsigned int i = 0; i < model.verts_count; i++)
    {
        vec v = vec_mult(model.verts[i], view);
        if (fprintf(file, "%lf %lf %lf\n", v.x, v.y, v.z) < 0)
            return ErrorCode::cannot_write_file;
    }

    return ErrorCode::success;
}

static ErrorCode save_edges(FILE* file, const Model& model)
{
    if (fprintf(file, "%u\n", model.edges_count) < 0)
        return ErrorCode::cannot_write_file;

    for (unsigned int i = 0; i < model.edges_count; i++)
    {
        edge e = model.edges[i];
        if (fprintf(file, "%u %u\n", e.p1, e.p2) < 0)
            return ErrorCode::cannot_write_file;
    }

    return ErrorCode::success;
}

ErrorCode core::do_save(const Model& model, mat view, const char* filename)
{
    if (filename == nullptr)
        return ErrorCode::invalid_file_name;

    FILE* file = fopen(filename, "wt");
    if (file == nullptr)
        return ErrorCode::cannot_open_file;

    view = mat_mult(view, translation({ 0, 0, -view_z }));

    ErrorCode status = save_verts(file, model, view);
    if (status == ErrorCode::success)
        status = save_edges(file, model);

    fclose(file);
    return status;
}

static void destroy_model(Model& model)
{
    if (model.verts)
        free(model.verts);

    if (model.edges)
        free(model.edges);

    memset(&model, 0, sizeof(Model));
}

static void destroy_projection(ProjectedModel& projection)
{
    if (projection.verts)
        free(projection.verts);

    if (projection.edges)
        free(projection.edges);

    memset(&projection, 0, sizeof(ProjectedModel));
}

ErrorCode core::do_destroy(Context& context)
{
    destroy_model(context.model);
    destroy_projection(context.projection);

    context.proj_mat = identity();
    context.view_mat = identity();
    context.viewport = viewport { 0, 0, 0, 0 };

    return ErrorCode::success;
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
        index p1 = context.model.edges[i].p1;
        index p2 = context.model.edges[i].p2;

        context.projection.edges[i].p1 = context.projection.verts[p1];
        context.projection.edges[i].p2 = context.projection.verts[p2];
    }

    return ErrorCode::success;
}
