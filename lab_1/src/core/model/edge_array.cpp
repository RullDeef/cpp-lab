#include <cstdlib>
#include <memory>
#include "edge_array.hpp"


edge_array edge_arr_init()
{
    edge_array ea {};

    ea.size = 0;
    ea.data = nullptr;

    return ea;
}

void edge_arr_destroy(VAR edge_array& ea)
{
    ea.size = 0;
    if (ea.data)
    {
        free(ea.data);
        ea.data = nullptr;
    }
}

bool edge_arr_is_valid(IN const edge_array& ea)
{
    return ea.size > 0 && ea.data != nullptr;
}

static void __clone_edge_arr(OUT edge_array& out, IN const edge_array& in)
{
    memcpy(out.data, in.data, sizeof(edge) * in.size);
}

ErrorCode edge_arr_resize(VAR edge_array& ea, IN unsigned int size)
{
    edge* new_data = (edge*)realloc(ea.data, sizeof(edge) * size);
    if (!new_data)
        return ErrorCode::bad_malloc;

    ea.size = size;
    ea.data = new_data;
    return ErrorCode::success;
}

ErrorCode edge_arr_clone(VAR edge_array& out, IN const edge_array& in)
{
    if (!edge_arr_is_valid(in))
        return ErrorCode::invalid_edge_array;

    ErrorCode status = edge_arr_resize(out, in.size);
    if (status != ErrorCode::success)
        return status;

    __clone_edge_arr(out, in);
    return ErrorCode::success;
}

static ErrorCode __read_edge_arr_size(OUT unsigned int& size, IN FILE* file)
{
    if (!file || fscanf(file, "%u", &size) != 1 || size == 0)
        return ErrorCode::invalid_file;
    return ErrorCode::success;
}

static ErrorCode __read_edge(OUT edge& edge, IN FILE* file)
{
    if (!file || fscanf(file, "%u%u", &edge.p1, &edge.p2) != 2 || edge.p1 == edge.p2)
        return ErrorCode::invalid_file;
    return ErrorCode::success;
}

static ErrorCode __read_edge_arr(VAR edge_array& ea, IN FILE* file)
{
    ErrorCode status = ErrorCode::success;
    for (unsigned int i = 0; i < ea.size && status == ErrorCode::success; i++)
        status = __read_edge(ea.data[i], file);
    return status;
}

ErrorCode edge_arr_load(VAR edge_array& ea, IN FILE* file)
{
    edge_array res_arr = edge_arr_init();
    unsigned int size;

    ErrorCode status = __read_edge_arr_size(size, file);
    if (status != ErrorCode::success)
        return status;

    status = edge_arr_resize(res_arr, size);
    if (status != ErrorCode::success)
        return status;

    status = __read_edge_arr(res_arr, file);
    if (status == ErrorCode::success)
        ea = res_arr;
    else
        edge_arr_destroy(res_arr);

    return status;
}

static ErrorCode __write_edge_arr_size(IN unsigned int size, IN FILE* file)
{
    if (!file || fprintf(file, "%u\n", size) <= 0)
        return ErrorCode::invalid_file;
    return ErrorCode::success;
}

static ErrorCode __write_edge(IN const edge& edge, IN FILE* file)
{
    if (!file || fprintf(file, "%u %u\n", edge.p1, edge.p2) <= 0)
        return ErrorCode::invalid_file;
    return ErrorCode::success;
}

static ErrorCode __write_edge_arr(IN const edge_array& ea, IN FILE* file)
{
    ErrorCode status = ErrorCode::success;
    for (unsigned int i = 0; i < ea.size && status == ErrorCode::success; i++)
        status = __write_edge(ea.data[i], file);
    return status;
}

ErrorCode edge_arr_save(IN const edge_array& ea, IN FILE* file)
{
    if (!edge_arr_is_valid(ea))
        return ErrorCode::invalid_edge_array;

    ErrorCode status = __write_edge_arr_size(ea.size, file);
    if (status != ErrorCode::success)
        return status;

    return __write_edge_arr(ea, file);
}
