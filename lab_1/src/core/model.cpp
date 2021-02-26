#include <string>
#include <sstream>
#include "model.hpp"

using core::ErrorCode;
using core::Model;

inline void model_clear(Model& model)
{
    model.verts.clear();
    model.edges.clear();
}

inline void model_add_vertex(Model& model, const Model::Vertex& vertex)
{
    model.verts.push_back(vertex);
}

inline void model_add_edge(Model& model, const Model::Edge& edge)
{
    model.edges.push_back(edge);
}

inline bool parse_vertex(const std::string& string, Model::Vertex& vertex)
{
    std::stringstream stream(string);
    return (stream >> vertex.x) && (stream >> vertex.y) && (stream >> vertex.z);
}

ErrorCode load_verts(std::ifstream& ifile, Model& model)
{
    unsigned int verts_count = 0;

    while (!ifile.eof())
    {
        std::string strbuf;
        std::getline(ifile, strbuf);

        if (strbuf.empty() || strbuf == "\n")
            break;

        Model::Vertex vertex;
        if (!parse_vertex(strbuf, vertex))
            return ErrorCode::invalid_file;

        model_add_vertex(model, vertex);
        verts_count++;
    }

    return verts_count > 0 ? ErrorCode::success : ErrorCode::invalid_file;
}

inline bool parse_edge(const std::string& string, Model::Edge& edge)
{
    std::stringstream stream(string);
    return (stream >> edge.first) && (stream >> edge.second);
}

ErrorCode load_edges(std::ifstream& ifile, Model& model)
{
    while (!ifile.eof())
    {
        std::string strbuf;
        std::getline(ifile, strbuf);

        if (strbuf.empty() || strbuf == "\n")
            break;

        Model::Edge edge;
        if (!parse_edge(strbuf, edge))
            return ErrorCode::invalid_file;

        model_add_edge(model, edge);
    }

    return ErrorCode::success;
}

ErrorCode core::load_model(const char* filename, Model& model)
{
    if (filename == nullptr)
        return ErrorCode::invalid_file_name;

    std::ifstream ifile(filename, std::ios::in);
    return load_model(ifile, model);
}

ErrorCode core::load_model(std::ifstream& ifile, Model& model)
{
    if (!ifile)
        return ErrorCode::cannot_open_file;

    model_clear(model);

    ErrorCode status = load_verts(ifile, model);
    if (status == ErrorCode::success)
        status = load_edges(ifile, model);

    return status;
}

ErrorCode core::save_model(const char* filename, Model& model);
ErrorCode core::save_model(std::ofstream& ofile, Model& model);
