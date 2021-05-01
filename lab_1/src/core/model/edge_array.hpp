#pragma once

#include <cstdio>
#include "../sal.hpp"
#include "../error_code.hpp"


struct edge
{
    unsigned int p1;
    unsigned int p2;
};

struct edge_array
{
    unsigned int size;
    edge* data;
};

edge_array edge_arr_init();
void edge_arr_destroy(VAR edge_array& ea);

bool edge_arr_is_valid(IN const edge_array& ea);

ErrorCode edge_arr_resize(VAR edge_array& va, IN unsigned int size);

ErrorCode edge_arr_clone(VAR edge_array& out, IN const edge_array& in);

ErrorCode edge_arr_load(VAR edge_array& ea, IN FILE* file);
ErrorCode edge_arr_save(VAR const edge_array& ea, IN FILE* file);
