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

    ErrorCode load_model(const char* filename, Model& model);
    ErrorCode load_model(std::ifstream& ifile, Model& model);

    ErrorCode save_model(const char* filename, Model& model);
    ErrorCode save_model(std::ofstream& ofile, Model& model);
}
