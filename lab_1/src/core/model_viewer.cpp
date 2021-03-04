#include <cstdio>
#include <cstdlib>
#include "ext_math.hpp"
#include "model_viewer.hpp"

using namespace core;
using namespace core::alg;

static ErrorCode do_smart_load(Context& context, const char* filename)
{
    ErrorCode status;
    if (validate_context(context) == ErrorCode::success)
    {
        Model new_model{ 0, 0, nullptr, nullptr };

        status = do_load(new_model, filename);
        if (status == ErrorCode::success)
        {
            destroy_model(context.model);
            destroy_projection(context.projection);
            context.model = new_model;
            context.view_mat = translation({ 0, 0, view_z });
        }
    }
    else
        status = do_load(context.model, filename);

    if (status == ErrorCode::success)
    {
        status = init_projection(context.projection,
            context.model.verts_count, context.model.edges_count);

        if (status == ErrorCode::success)
            status = update_projection(context);
    }

    return status;
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
        return do_init(context, action.viewport);

    ErrorCode status = validate_viewport(context.viewport);
    if (status != ErrorCode::success)
        return status;

    if (action.type == ActionType::Load)
        return do_smart_load(context, action.filename);

    status = validate_model(context.model);
    if (status != ErrorCode::success)
        return status;
    
    status = validate_projection(context.projection);
    if (status != ErrorCode::success)
        return status;

    if (action.type == ActionType::Save)
        return do_save(context.model, context.view_mat, action.filename);

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
    default:
        return ErrorCode::unknown_action;
    }

    if (status == ErrorCode::success)
        status = update_projection(context);

    return status;
}

ErrorCode core::do_translation(mat& view, const TranslateAction& action)
{
    constexpr auto sensetivity = 60.0;

    double dx = -action.dx / sensetivity;
    double dy =  action.dy / sensetivity;

    vec loc = dir_mult({ dx, dy, 0 }, mat_inv(view));
    view = mat_mult(translation(loc), view);

    return ErrorCode::success;
}

ErrorCode core::do_rotation(mat& view, const RotateAction& action)
{
    constexpr auto sensetivity = 60.0;

    double phi = -action.dx / sensetivity;
    double theta = -action.dy / sensetivity;

    vec x_loc = norm(dir_mult({ 1, 0, 0 }, mat_inv(view)));
    view = mat_mult(rotation(x_loc, theta), view);

    vec y_loc = norm(dir_mult({ 0, 1, 0 }, mat_inv(view)));
    view = mat_mult(rotation(y_loc, phi), view);

    return ErrorCode::success;
}

ErrorCode core::do_scale(mat& view, const ScaleAction& action)
{
    constexpr auto sensetivity = 60.0;

    double f = 1 + action.factor / sensetivity;
    view = mat_mult(scale({ f, f, f }), view);

    return ErrorCode::success;
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
        vec& vert = model.verts[i];
        if (fscanf(file, "%lf%lf%lf", &vert.x, &vert.y, &vert.z) != 3)
        {
            free(model.verts);
            model.verts = nullptr;
            model.verts_count = 0;
            return ErrorCode::invalid_file;
        }
    }

    return ErrorCode::success;
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
        edge& edge = model.edges[i];
        if (fscanf(file, "%u%u", &edge.p1, &edge.p2) != 2 || edge.p1 == edge.p2)
        {
            free(model.edges);
            model.edges = nullptr;
            model.edges_count = 0;
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
            model.verts_count = 0;
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

ErrorCode core::do_init(Context& context, viewport viewport)
{
    ErrorCode status = validate_viewport(viewport);
    if (status == ErrorCode::success)
    {
        context = { 0 };
        context.viewport = viewport;
        double aspect = (double)viewport.width / viewport.height;
        context.proj_mat = perspective(view_fov, aspect, view_near, view_far);
        context.view_mat = translation({ 0, 0, view_z });
    }
    return status;
}

ErrorCode core::do_destroy(Context& context)
{
    destroy_context(context);
    return ErrorCode::success;
}
