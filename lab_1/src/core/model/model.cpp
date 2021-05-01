#include <cstdlib>
#include "model.hpp"


Model model_init()
{
    Model model {};

    model.verts = vert_arr_init();
    model.edges = edge_arr_init();

    return model;
}

void model_destroy(VAR Model& model)
{
    vert_arr_destroy(model.verts);
    edge_arr_destroy(model.edges);
}

ErrorCode model_clone(OUT Model& copy, IN const Model& model)
{
    if (!model_is_valid(model))
        return ErrorCode::invalid_model;

    ErrorCode status = vert_arr_clone(copy.verts, model.verts);
    if (status != ErrorCode::success)
        return status;

    status = edge_arr_clone(copy.edges, model.edges);
    if (status != ErrorCode::success)
        vert_arr_destroy(copy.verts);

    return status;
}

bool model_is_valid(IN const Model& model)
{
    return vert_arr_is_valid(model.verts) && edge_arr_is_valid(model.edges);
}

ErrorCode model_load(OUT Model& model, IN FILE* file)
{
    if (file == nullptr)
        return ErrorCode::cannot_open_file;

    ErrorCode status = vert_arr_load(model.verts, file);
    if (status == ErrorCode::success)
    {
        status = edge_arr_load(model.edges, file);
        if (status != ErrorCode::success)
            vert_arr_destroy(model.verts);
    }

    return status;
}

ErrorCode model_load(OUT Model& model, IN const char* filename)
{
    if (filename == nullptr)
        return ErrorCode::invalid_file_name;

    FILE* file = fopen(filename, "rt");
    ErrorCode status = model_load(model, file);

    fclose(file);
    return status;
}

ErrorCode model_save(IN const Model& model, IN FILE* file)
{
    if (!model_is_valid(model))
        return ErrorCode::invalid_model;

    ErrorCode status = vert_arr_save(model.verts, file);
    if (status == ErrorCode::success)
        status = edge_arr_save(model.edges, file);

    return status;
}

ErrorCode model_save(IN const Model& model, IN const char* filename)
{
    if (filename == nullptr)
        return ErrorCode::invalid_file_name;

    FILE* file = fopen(filename, "wt");
    ErrorCode status = model_save(model, file);

    fclose(file);
    return status;
}

ErrorCode model_transform(VAR Model& model, IN const transform& tf)
{
    if (!model_is_valid(model))
        return ErrorCode::invalid_model;

    return vert_arr_transform(model.verts, tf);
}
