#pragma once

#include "basetypes.hpp"

namespace core
{
    constexpr auto view_near = 1.4;
    constexpr auto view_far = 100.0;
    constexpr auto view_fov = 75 * 3.1415 / 180;

    constexpr auto view_z = -10.0;

    struct Model
    {
        unsigned int verts_count;
        unsigned int edges_count;

        vec* verts;
        edge* edges;
    };

    struct ProjectedModel
    {
        unsigned int verts_count;
        unsigned int edges_count;

        screen_point* verts;
        section* edges;
    };

    struct Context
    {
        mat view_mat;
        mat proj_mat;
        viewport viewport;
        Model model;
        ProjectedModel projection;
    };

    enum class ActionType
    {
        Init,       // initializes viewport
        Translate,  // translate model
        Rotate,     // rotate model
        Scale,      // scale model
        Load,       // load model from file
        Save,       // saves model to file
        Destroy     // releases model resources
    };

    struct TranslateAction
    {
        real dx;
        real dy;
    };

    struct RotateAction
    {
        real dx;
        real dy;
    };

    struct ScaleAction
    {
        real factor;
    };

    struct Action
    {
        ActionType type;
        union
        {
            viewport viewport;
            TranslateAction translate;
            RotateAction rotate;
            ScaleAction scale;
            const char* filename;
        };
    };

    // точка входа в прикладном домене
    ErrorCode model_viewer(Context& context, const Action& action);

    // список вызываемых действий
    ErrorCode do_translation(mat& view, const TranslateAction& action);
    ErrorCode do_rotation(mat& view, const RotateAction& action);
    ErrorCode do_scale(mat& view, const ScaleAction& action);

    ErrorCode do_load(Model& model, const char* filename);
    ErrorCode do_save(const Model& model, mat view, const char* filename);

    ErrorCode do_destroy(Context& context);

    ErrorCode init_projection(ProjectedModel& prj, unsigned int verts, unsigned int edges);
    ErrorCode update_projection(Context& context);

    // validation functions
    ErrorCode validate_viewport(viewport viewport);
    ErrorCode validate_model(const Model& model);
    ErrorCode validate_projection(const ProjectedModel& projetion);
    ErrorCode validate_context(const Context& context);

    // ErrorCode validate_action(); // ???
}
