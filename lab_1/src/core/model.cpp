#include <cstdlib>
#include <cstring>
#include "model.hpp"

using namespace core;

Model core::model_init()
{
    Model model {};

    model.verts_count = 0;
    model.verts = nullptr;

    model.edges_count = 0;
    model.edges = nullptr;

    return model;
}

static void verts_free(OUT unsigned int& verts_count, VAR vec*& verts)
{
    if (verts != nullptr)
        free(verts);

    verts = nullptr;
    verts_count = 0;
}

static void edges_free(OUT unsigned int& edges_count, VAR edge*& edges)
{
    if (edges != nullptr)
        free(edges);

    edges = nullptr;
    edges_count = 0;
}

void core::model_destroy(VAR Model& model)
{
    verts_free(model.verts_count, model.verts);
    edges_free(model.edges_count, model.edges);
}

ErrorCode core::model_clone(OUT Model& copy, IN const Model& model)
{
    if (!model_is_valid(model))
        return ErrorCode::invalid_model;

    if (model_is_valid(copy))
        model_destroy(copy);

    vec* verts = (vec*)malloc(model.verts_count * sizeof(vec));
    if (verts == nullptr)
        return ErrorCode::bad_malloc;

    edge* edges = (edge*)malloc(model.edges_count * sizeof(edge));
    if (edges == nullptr)
    {
        free(verts);
        return ErrorCode::bad_malloc;
    }

    copy = model;
    copy.verts = verts;
    copy.edges = edges;

    std::memcpy(copy.verts, model.verts, model.verts_count * sizeof(vec));
    std::memcpy(copy.edges, model.edges, model.edges_count * sizeof(edge));

    return ErrorCode::success;
}

bool core::model_is_valid(IN const Model& model)
{
    return model.verts_count > 0;
}

ErrorCode core::model_transform(VAR Model& model, IN mat matrix)
{
    if (!model_is_valid(model))
        return ErrorCode::invalid_model;

    for (unsigned int i = 0; i < model.verts_count; i++)
        model.verts[i] = alg::vec_mult(model.verts[i], matrix);

    return ErrorCode::success;
}

static bool vert_load(OUT vec& vert, IN FILE* file)
{
    return fscanf(file, "%lf%lf%lf", &vert.x, &vert.y, &vert.z) == 3;
}

static bool edge_load(OUT edge& edge, IN FILE* file)
{
    return fscanf(file, "%u%u", &edge.p1, &edge.p2) == 2 && edge.p1 != edge.p2;
}

static ErrorCode verts_load(OUT vec*& verts, OUT unsigned int& verts_count, IN FILE* file)
{
    if (fscanf(file, "%u", &verts_count) != 1 || verts_count == 0)
        return ErrorCode::invalid_file;

    verts = (vec*)malloc(verts_count * sizeof(vec));
    if (verts == nullptr)
        return ErrorCode::bad_malloc;

    bool file_valid = true;
    for (unsigned int i = 0; i < verts_count && file_valid; i++)
        file_valid = vert_load(verts[i], file);

    if (!file_valid)
        verts_free(verts_count, verts);

    return file_valid ? ErrorCode::success : ErrorCode::invalid_file;
}

static ErrorCode edges_load(OUT edge*& edges, OUT unsigned int& edges_count, IN FILE* file)
{
    if (fscanf(file, "%u", &edges_count) != 1 || edges_count == 0)
        return ErrorCode::invalid_file;

    edges = (edge*)malloc(edges_count * sizeof(edge));
    if (edges == nullptr)
        return ErrorCode::bad_malloc;

    bool file_valid = true;
    for (unsigned int i = 0; i < edges_count && file_valid; i++)
        file_valid = edge_load(edges[i], file);

    if (!file_valid)
        edges_free(edges_count, edges);

    return file_valid ? ErrorCode::success : ErrorCode::invalid_file;
}

static ErrorCode model_load_file(OUT Model& model, IN FILE* file)
{
    ErrorCode status = verts_load(model.verts, model.verts_count, file);
    if (status == ErrorCode::success)
    {
        status = edges_load(model.edges, model.edges_count, file);
        if (status != ErrorCode::success)
            verts_free(model.verts_count, model.verts);
    }

    return status;
}

ErrorCode core::model_load(OUT Model& model, IN const char* filename)
{
    if (filename == nullptr)
        return ErrorCode::invalid_file_name;

    FILE* file = fopen(filename, "rt");
    if (file == nullptr)
        return ErrorCode::cannot_open_file;

    ErrorCode status = model_load_file(model, file);

    fclose(file);
    return status;
}

static bool vert_save(IN vec vert, IN FILE* file)
{
    return fprintf(file, "%lf %lf %lf\n", vert.x, vert.y, vert.z) < 0;
}

static bool edge_save(IN edge edge, IN FILE* file)
{
    return fprintf(file, "%u %u\n", edge.p1, edge.p2) < 0;
}

static ErrorCode verts_save(IN const vec* verts, IN unsigned int verts_count, IN FILE* file)
{
    bool bad_file = fprintf(file, "%u\n", verts_count) < 0;

    for (unsigned int i = 0; i < verts_count && !bad_file; i++)
        bad_file = vert_save(verts[i], file);

    return bad_file ? ErrorCode::cannot_write_file : ErrorCode::success;
}

static ErrorCode edges_save(IN const edge* edges, IN unsigned int edges_count, IN FILE* file)
{
    bool bad_write = fprintf(file, "%u\n", edges_count) < 0;

    for (unsigned int i = 0; i < edges_count && !bad_write; i++)
        bad_write = edge_save(edges[i], file);

    return bad_write ? ErrorCode::cannot_write_file : ErrorCode::success;
}

static ErrorCode model_save_file(IN const Model& model, IN FILE* file)
{
    ErrorCode status = verts_save(model.verts, model.verts_count, file);
    if (status == ErrorCode::success)
        status = edges_save(model.edges, model.edges_count, file);

    return status;
}

ErrorCode core::model_save(IN const Model& model, IN const char* filename)
{
    if (filename == nullptr)
        return ErrorCode::invalid_file_name;

    FILE* file = fopen(filename, "wt");
    if (file == nullptr)
        return ErrorCode::cannot_open_file;

    ErrorCode status = model_save_file(model, file);

    fclose(file);
    return status;
}

ErrorCode core::model_save_transformed(IN const Model& model, IN const char* filename, IN mat matrix)
{
    Model copy = model_init();

    ErrorCode status = model_clone(copy, model);
    if (status != ErrorCode::success)
        return status;

    status = model_transform(copy, matrix);
    if (status == ErrorCode::success)
        status = model_save(copy, filename);

    model_destroy(copy);
    return status;
}
