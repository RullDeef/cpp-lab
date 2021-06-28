#pragma once

#include <string>
#include "IObjectDirector.hpp"

class IObject;


class FileWireframeModelDirector : public IObjectDirector
{
public:
    explicit FileWireframeModelDirector(const std::string& filename);

    IObject* makeObject() override;

private:
    const std::string filename;
};
