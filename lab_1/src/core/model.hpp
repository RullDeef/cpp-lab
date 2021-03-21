#pragma once

#include <cstdio>
#include "sal.hpp"
#include "error_code.hpp"
#include "ext_math.hpp"

namespace core
{
    struct edge
    {
        unsigned int p1;
        unsigned int p2;
    };

    struct Model
    {
        unsigned int verts_count;
        unsigned int edges_count;

        vec* verts;
        edge* edges;
    };

    Model model_init();
    void model_destroy(VAR Model& model);

    ErrorCode model_clone(OUT Model& copy, IN const Model& model);

    bool model_is_valid(IN const Model& model);
    ErrorCode model_transform(VAR Model& model, IN mat matrix);

    ErrorCode model_load(OUT Model& model, IN const char* filename);
    ErrorCode model_save(IN const Model& model, IN const char* filename);

    ErrorCode model_save_transformed(IN const Model& model, IN const char* filename, IN mat matrix);
}
