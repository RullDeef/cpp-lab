#include <cstdlib>
#include <memory>
#include "vert_array.hpp"


vert_array vert_arr_init()
{
    vert_array va {};

    va.size = 0;
    va.data = nullptr;

    return va;
}

void vert_arr_destroy(VAR vert_array& va)
{
    va.size = 0;
    if (va.data)
    {
        free(va.data);
        va.data = nullptr;
    }
}

bool vert_arr_is_valid(IN const vert_array& va)
{
    return va.size > 0 && va.data != nullptr;
}

static void __clone_vert_arr(OUT vert_array& out, IN const vert_array& in)
{
    memcpy(out.data, in.data, in.size * sizeof(vec));
}

ErrorCode vert_arr_resize(VAR vert_array& va, IN unsigned int size)
{
    vec* new_data = (vec*)realloc(va.data, sizeof(vec) * size);
    if (!new_data)
        return ErrorCode::bad_malloc;

    va.size = size;
    va.data = new_data;
    return ErrorCode::success;
}

ErrorCode vert_arr_clone(VAR vert_array& out, IN const vert_array& in)
{
    if (!vert_arr_is_valid(in))
        return ErrorCode::invalid_vert_array;

    ErrorCode status = vert_arr_resize(out, in.size);
    if (status != ErrorCode::success)
        return status;

    __clone_vert_arr(out, in);
    return ErrorCode::success;
}

static ErrorCode __read_vert_arr_size(OUT unsigned int& size, IN FILE* file)
{
    if (!file || fscanf(file, "%u", &size) != 1 || size == 0)
        return ErrorCode::invalid_file;
    return ErrorCode::success;
}

static ErrorCode __read_vert(OUT vec& vert, IN FILE* file)
{
    if (!file || fscanf(file, "%f%f%f", &vert.x, &vert.y, &vert.z) != 3)
        return ErrorCode::invalid_file;
    return ErrorCode::success;
}

static ErrorCode __read_vert_arr(VAR vert_array& va, IN FILE* file)
{
    ErrorCode status = ErrorCode::success;
    for (unsigned int i = 0; i < va.size && status == ErrorCode::success; i++)
        status = __read_vert(va.data[i], file);
    return status;
}

ErrorCode vert_arr_load(VAR vert_array& va, IN FILE* file)
{
    vert_array res_arr = vert_arr_init();
    unsigned int size;

    ErrorCode status = __read_vert_arr_size(size, file);
    if (status != ErrorCode::success)
        return status;

    status = vert_arr_resize(res_arr, size);
    if (status != ErrorCode::success)
        return status;

    status = __read_vert_arr(res_arr, file);
    if (status == ErrorCode::success)
        va = res_arr;
    else
        vert_arr_destroy(res_arr);

    return status;
}

static ErrorCode __write_vert_arr_size(IN unsigned int size, IN FILE* file)
{
    if (!file || fprintf(file, "%u\n", size) <= 0)
        return ErrorCode::invalid_file;
    return ErrorCode::success;
}

static ErrorCode __write_vert(IN const vec& vert, IN FILE* file)
{
    if (!file || fprintf(file, "%f %f %f\n", vert.x, vert.y, vert.z) <= 0)
        return ErrorCode::invalid_file;
    return ErrorCode::success;
}

static ErrorCode __write_vert_arr(IN const vert_array& va, IN FILE* file)
{
    ErrorCode status = ErrorCode::success;
    for (unsigned int i = 0; i < va.size && status == ErrorCode::success; i++)
        status = __write_vert(va.data[i], file);
    return status;
}

ErrorCode vert_arr_save(IN const vert_array& va, IN FILE* file)
{
    if (!vert_arr_is_valid(va))
        return ErrorCode::invalid_vert_array;

    ErrorCode status = __write_vert_arr_size(va.size, file);
    if (status != ErrorCode::success)
        return status;

    return __write_vert_arr(va, file);
}

static void __transform_vert(VAR vec& vert, IN const transform& tf)
{
    vert = tf_apply(tf, vert);
}

static void __transform_vert_arr(VAR vert_array& va, IN const transform& tf)
{
    for (unsigned int i = 0; i < va.size; i++)
        __transform_vert(va.data[i], tf);
}

ErrorCode vert_arr_transform(VAR vert_array& va, IN const transform& tf)
{
    if (!vert_arr_is_valid(va))
        return ErrorCode::invalid_vert_array;

    __transform_vert_arr(va, tf);
    return ErrorCode::success;
}
