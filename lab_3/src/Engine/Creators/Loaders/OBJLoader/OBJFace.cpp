#include "OBJFace.hpp"


OBJFace::OBJFace(const std::list<size_t>& positions, const std::list<size_t>& normals, const std::list<size_t>& UVCoornds)
    : positions(positions), normals(normals), UVCoords(UVCoords)
{
}

const std::list<size_t>& OBJFace::getPositions() const
{
    return positions;
}

const std::list<size_t>& OBJFace::getNormals() const
{
    return normals;
}

const std::list<size_t>& OBJFace::getUVCoords() const
{
    return UVCoords;
}
