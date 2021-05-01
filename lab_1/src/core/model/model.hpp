#pragma once

#include <cstdio>
#include "../sal.hpp"
#include "../error_code.hpp"

#include "vert_array.hpp"
#include "edge_array.hpp"

#include "../transform/transform.hpp"


struct Model
{
    vert_array verts;
    edge_array edges;
};

Model model_init();
void model_destroy(VAR Model& model);

ErrorCode model_clone(OUT Model& copy, IN const Model& model);

bool model_is_valid(IN const Model& model);

ErrorCode model_load(OUT Model& model, IN FILE* file);
ErrorCode model_load(OUT Model& model, IN const char* filename);

ErrorCode model_save(IN const Model& model, IN FILE* file);
ErrorCode model_save(IN const Model& model, IN const char* filename);

ErrorCode model_transform(VAR Model& model, IN const transform& tf);
