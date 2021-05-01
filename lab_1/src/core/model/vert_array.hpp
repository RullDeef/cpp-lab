#pragma once

#include <cstdio>
#include "../sal.hpp"
#include "../error_code.hpp"
#include "../ext_math.hpp"

#include "../transform/transform.hpp"


struct vert_array
{
    vec* data;
    unsigned int size;
};

vert_array vert_arr_init();
void vert_arr_destroy(VAR vert_array& va);

bool vert_arr_is_valid(IN const vert_array& va);

ErrorCode vert_arr_resize(VAR vert_array& va, IN unsigned int size);

ErrorCode vert_arr_clone(VAR vert_array& out, IN const vert_array& in);

ErrorCode vert_arr_load(VAR vert_array& va, IN FILE* file);
ErrorCode vert_arr_save(IN const vert_array& va, IN FILE* file);

ErrorCode vert_arr_transform(VAR vert_array& va, IN const transform& tf);
