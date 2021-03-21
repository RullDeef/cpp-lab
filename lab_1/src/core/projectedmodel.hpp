#pragma once

#include "sal.hpp"
#include "error_code.hpp"
#include "ext_math.hpp"
#include "model.hpp"
#include "view.hpp"

namespace core
{
    struct section
    {
        screen_point p1;
        screen_point p2;
    };

    struct ProjectedModel
    {
        unsigned int verts_count;
        unsigned int edges_count;

        screen_point* verts;
        section* edges;
    };

    ProjectedModel projmod_init();
    void projmod_destroy(VAR ProjectedModel& projmod);

    bool projmod_is_valid(IN const ProjectedModel& projmod);

    ErrorCode projmod_project(VAR ProjectedModel& projmod, IN const Model& model, IN const View& view);

    ErrorCode projmod_apply_view(VAR Model& model, IN const View& view);
}
