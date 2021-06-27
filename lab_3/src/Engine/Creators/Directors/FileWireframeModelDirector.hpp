#pragma once

#include <string>

class IObject;


class FileWireframeModelDirector
{
public:
    explicit FileWireframeModelDirector(const std::string& filename);

    IObject* makeWireframeModel();

private:
    const std::string filename;
};
