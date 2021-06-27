#include <fstream>
#include "OBJLoader.hpp"
#include "Utils/Logger.hpp"


OBJLoader::OBJLoader(const std::string& filename)
{
    std::ifstream stream(filename);
    std::string line;

    while (!std::getline(stream, line).eof())
    {
        line = "Read line: " + line;
        LOGGER_LOG(line.c_str());
    }
}

const std::list<Vector>& OBJLoader::getPositions() const
{
    return positions;
}

const std::list<Vector>& OBJLoader::getNormals() const
{
    return normals;
}

const std::list<Vector>& OBJLoader::getUVCoords() const
{
    return UVCoords;
}

const std::list<OBJFace>& OBJLoader::getFaces() const
{
    return faces;
}
