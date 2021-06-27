#pragma once

#include <list>
#include <string>
#include "Core/Math/Vector.hpp"
#include "OBJFace.hpp"


class OBJLoader
{
public:
    OBJLoader(const std::string& filename);

    const std::list<Vector>& getPositions() const;
    const std::list<Vector>& getNormals() const;
    const std::list<Vector>& getUVCoords() const;
    const std::list<OBJFace>& getFaces() const;

private:
    std::list<Vector> positions;
    std::list<Vector> normals;
    std::list<Vector> UVCoords;

    std::list<OBJFace> faces;
};
