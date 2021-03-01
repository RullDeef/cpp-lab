#pragma once

#include <fstream>
#include <vector>

namespace core
{
    enum class ErrorCode
    {
        success,
        invalid_file_name,
        cannot_open_file,
        invalid_file
    };

    struct Model
    {
        struct Vertex
        {
            double x;
            double y;
            double z;
        };

        using Edge = std::pair<unsigned int, unsigned int>;

        std::vector<Vertex> verts;
        std::vector<Edge> edges;
    };

    // одна точка входа.
    // свои модули для математики.
    // "слишком умный интерфейс".
    // не использовать STL.
    // только перенос/поворот/масштабирование.

    void model_clear(Model& model);

    void model_vertex_add(Model& model, const Model::Vertex& vertex);
    void model_edge_add(Model& model, const Model::Edge& edge);
    
    ErrorCode model_load(const char* filename, Model& model);
    ErrorCode model_load(std::ifstream& ifile, Model& model);

    ErrorCode model_save(const char* filename, Model& model);
    ErrorCode model_save(std::ofstream& ofile, Model& model);

    Model default_cube(double side);
}
