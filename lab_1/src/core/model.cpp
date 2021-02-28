#include <string>
#include <sstream>
#include "model.hpp"

using core::ErrorCode;
using core::Model;

void core::model_clear(Model& model)
{
    model.verts.clear();
    model.edges.clear();
}

void core::model_vertex_add(Model& model, const Model::Vertex& vertex)
{
    model.verts.push_back(vertex);
}

void core::model_edge_add(Model& model, const Model::Edge& edge)
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

        model_vertex_add(model, vertex);
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

        model_edge_add(model, edge);
    }

    return ErrorCode::success;
}

ErrorCode core::model_load(const char* filename, Model& model)
{
    if (filename == nullptr)
        return ErrorCode::invalid_file_name;

    std::ifstream ifile(filename);
    return model_load(ifile, model);
}

ErrorCode core::model_load(std::ifstream& ifile, Model& model)
{
    if (!ifile)
        return ErrorCode::cannot_open_file;

    model_clear(model);

    ErrorCode status = load_verts(ifile, model);
    if (status == ErrorCode::success)
        status = load_edges(ifile, model);

    return status;
}

ErrorCode core::model_save(const char* filename, Model& model)
{
    if (filename == nullptr)
        return ErrorCode::invalid_file_name;

    std::ofstream ofile(filename);
    return model_save(ofile, model);
}

ErrorCode core::model_save(std::ofstream& ofile, Model& model)
{
    if (!ofile)
        return ErrorCode::cannot_open_file;

    ErrorCode status = ErrorCode::success;
    for (const auto& vertex : model.verts)
        ofile << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    ofile << "\n";
    for (const auto& edge : model.edges)
        ofile << edge.first << " " << edge.second << "\n";

    ofile.flush();
    return status;
}
