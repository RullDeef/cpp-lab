#pragma once

#include <list>


class OBJFace
{
public:
    explicit OBJFace(const std::list<size_t>& positions = {},
        const std::list<size_t>& normals = {}, const std::list<size_t>& UVCoornds = {});

    const std::list<size_t>& getPositions() const;
    const std::list<size_t>& getNormals() const;
    const std::list<size_t>& getUVCoords() const;

private:
    std::list<size_t> positions;
    std::list<size_t> normals;
    std::list<size_t> UVCoords;
};
