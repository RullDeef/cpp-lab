#pragma once

#include "error_code.hpp"
#include "ext_math.hpp"

namespace core
{
    constexpr auto view_near = 1.4;
    constexpr auto view_far = 100.0;
    constexpr auto view_fov = 75 * 3.1415 / 180;

    constexpr auto view_z = -10.0;

    struct edge
    {
        unsigned int p1;
        unsigned int p2;
    };

    struct section
    {
        screen_point p1;
        screen_point p2;
    };

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

    // validation functions
    ErrorCode validate_viewport(viewport viewport);
    ErrorCode validate_model(const Model& model);
    ErrorCode validate_projection(const ProjectedModel& projetion);
    ErrorCode validate_context(const Context& context);

    void destroy_model(Model& model);
    void destroy_projection(ProjectedModel& projection);
    void destroy_context(Context& context);

    ErrorCode init_projection(ProjectedModel& prj, unsigned int verts, unsigned int edges);
    ErrorCode update_projection(Context& context);
}